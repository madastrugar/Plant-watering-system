const int moisturePin = A0;
const int ledPin = 12;
const int pumpPin = 4;
const int buttonPin = 2; 

const int dry_threshold = 750;
const int humid_threshold = 500;

const int sensorMin = 0;
const int sensorMax = 1023;
const int percentMin = 0;
const int percentMax = 100;

int moistureValue;
int buttonState = 0; 
int ledState = 0;
int pumpState = 0;

int percentValue=0;;


void setup() {
  // put your setup code here, to run once:
  pinMode(moisturePin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(pumpPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  digitalWrite(ledPin, LOW);
  digitalWrite(pumpPin, HIGH);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  moistureValue = analogRead(moisturePin);
  buttonState = digitalRead(buttonPin);
  ledState = digitalRead(ledPin);
  percentValue = (100 - map(moistureValue, sensorMin, sensorMax, percentMin, percentMax));

  if(moistureValue >= 1000) {
     Serial.println("Sensor is not in the soil or it is disconnected! : ");
     Serial.print("Moisture level:");
     Serial.print(percentValue);
     Serial.println("%");
     digitalWrite(pumpPin, HIGH);
     digitalWrite(ledPin,LOW);
  }

  if(moistureValue < 1000 && moistureValue >= dry_threshold) { 
     Serial.println("Your plant needs water! :( : ");
     Serial.print("Moisture level:");
     Serial.print(percentValue);
     Serial.println("%");
     digitalWrite(ledPin,HIGH);
     if (buttonState == HIGH) {
        digitalWrite(pumpPin, LOW);
        delay(5000);
        digitalWrite(pumpPin, HIGH);
        digitalWrite(ledPin,LOW);
    } else {
        digitalWrite(pumpPin, HIGH);
    }
  }

  if(moistureValue < dry_threshold && moistureValue >= humid_threshold) {
    Serial.println("Your plant has enough water :D : "); 
    Serial.print("Moisture level:");
    Serial.print(percentValue);
    Serial.println("%");
    digitalWrite(pumpPin, HIGH);
    digitalWrite(ledPin,LOW);
  }

  if(moistureValue < humid_threshold) {
    Serial.println("Sensor in water or your plant has too much water! : ");
    Serial.print("Moisture level:");
    Serial.print(percentValue);
    Serial.println("%");
    digitalWrite(pumpPin, HIGH);
    digitalWrite(ledPin,LOW);
  }  
  Serial.println("---------------------------------------------------------------------------------------"); 
  delay(3000);
}


