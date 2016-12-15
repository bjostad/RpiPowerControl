const int switchPin = 2;           // pin the SNES power switch is connected to
const int powerLedPin = 8;        // pin the SNES power LED is connected to
const int mainPowerRelayPin = 6;   // pin for the 5V relay that provides power to the Rpi
const int piStatusPin = 7;         // pin for telling the pi when it is time to shutdown (shutdown = 1, run = 0)

int switchState = 0;         // SNES power switch state
int switchStatePrevious = 0; // Previous state of power switch

void setup() {
  pinMode(switchPin, INPUT); // initialize the SNES power switch pin
  pinMode(powerLedPin, OUTPUT);   // initialize the SNES power LED
  pinMode(mainPowerRelayPin, OUTPUT); //initialize Relay pin
  digitalWrite(mainPowerRelayPin, HIGH); //Set relay to High as it triggers low
  pinMode(piStatusPin, OUTPUT); //initialize Pi status pin
  Serial.begin(9600);        // initialize serial
}


void loop() {
  switchState = digitalRead(switchPin); // check the state of the SNES power switch

  //Check to see if the state of the power switch has changed
  if (switchState == switchStatePrevious) {
    Serial.print("-");    
  } 
  
  //If the Power switch state has changed  and the new state is HIGH, start the power on procedure
  else if ( switchState != switchStatePrevious && switchState == HIGH){
    powerOn();  
  } 
  
  //If the Power switch state has change and the new state is LOW, start the power off procedure
  else if ( switchState != switchStatePrevious && switchState == LOW){
    powerOff();
  }
  
  switchStatePrevious = switchState;
  delay(1000);
}

//Power On
//Turn on power LED
//Switch on power relay to provide power to Rpi and logic converter (Relay triggers at Low)
void powerOn(){
  pinHigh(powerLedPin);
  pinHigh(piStatusPin);
  pinLow(mainPowerRelayPin);
    
}

//Shutdown function
//Turn off power LED
//Wait 30 seconds for Rpi to shutdown and then switch of Relay
//TODO: replace delay with confirmation of shutdown from Rpi using Serial
void powerOff(){
  pinLow(powerLedPin);
  pinLow(piStatusPin);
  delay(10000); //TODO: change from test time of 10sec to a reasonable time
  pinHigh(mainPowerRelayPin);  
}

//Move a pin to high and output that change to serial
void pinHigh( int pin){
  digitalWrite(pin, HIGH);
  Serial.print(pin);
  Serial.println(" switched to HIGH");
}

//Move a pin to low and output that change to serial
void pinLow( int pin){
  digitalWrite(pin, LOW);
  Serial.print(pin);
  Serial.println(" switched to LOW");
}
