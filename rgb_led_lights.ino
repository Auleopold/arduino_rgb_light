int analogPin = 0; // read from multiplexer using analog input 0
int strobePin = 2; // strobe is attached to digital pin 2
int resetPin = 3; // reset is attached to digital pin 3

int redPin = 11;
int greenPin = 10;
int bluePin = 9;

int filter = 80; //filter out the noise
int spectrumValue[7]; // to hold a2d values

void setup() 
{
  Serial.begin(9600);
  pinMode(analogPin, INPUT);
  pinMode(strobePin, OUTPUT);
  pinMode(resetPin, OUTPUT);
  
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  
  analogReference(DEFAULT);

  digitalWrite(resetPin, LOW);
  digitalWrite(strobePin, HIGH);
}

void loop() 
{
  digitalWrite(resetPin, HIGH);
  digitalWrite(resetPin, LOW);

  for (int i = 0; i < 7; i++){
    digitalWrite(strobePin, LOW);
    delay(15); // set delay for output
    spectrumValue[i] = analogRead(analogPin);
    spectrumValue[i] = constrain(spectrumValue[i], filter, 1023);
    spectrumValue[i] = map(spectrumValue[i],filter, 1023, 0, 255);
    Serial.print(spectrumValue[i]);
    Serial.print(" ");

    digitalWrite(strobePin, HIGH);
  }
  Serial.println();
   analogWrite(redPin, spectrumValue[2]); //set red value
   analogWrite(greenPin, spectrumValue[4]);  //set green value
   analogWrite(bluePin, spectrumValue[6]);  //set blue value
  
}

