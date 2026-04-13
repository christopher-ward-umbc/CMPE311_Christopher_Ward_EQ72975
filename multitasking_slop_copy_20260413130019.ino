// constants won't change. Used here to
// set pin numbers:
const int ledPin1 = 13;  // the number of the LED pin
const int ledPin2 = 11;
const int inputPin = 2;
const int outputPin = 3;

int fanstate = 0;

bool buttonCooldown = false;

// Variables will change:
int ledState1 = LOW;  // ledState used to set the LED
int ledState2 = LOW;
long previousMillis1 = 0;  // will store last time LED was updated
long previousMillis2 = 0;

// the follow variables is a long because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long interval1 = 1000;  // interval at which to blink (milliseconds)
long interval2 = 700;
bool userAsk = false;
bool userSpeed = false;
int ledSelect = -1;
int ledSpeed = 0;

bool skip = false;

unsigned long currentMillis1 = millis();
unsigned long currentMillis2 = millis();



int fn0() {
  Serial.print("\n");
  Serial.print(userAsk);
  Serial.print("\n");
  Serial.print("Select which LED you want to change\n");
  userAsk = true;
  delay(1);
  return 0;
}

int fn1() {
  ledSelect = Serial.parseInt();
  if (ledSelect == 1 || ledSelect == 2) {
    Serial.print("How fast do you want it to blink (ms)");
    userSpeed = true;
    delay(1);
  } else if (ledSelect != 10) {
    Serial.print("Invalid input, must be 1 or 2, input again\n");
    delay(1);
  }
  return 0;
}

int fn2() {
  ledSpeed = Serial.parseInt();
  if (ledSelect == 1 && ledSpeed > -1) {
    interval1 = ledSpeed;
    userSpeed = false;
    userAsk = false;
  } else if (ledSelect == 2 && ledSpeed > -1) {
    interval2 = ledSpeed;
    userSpeed = false;
    userAsk = false;
  }
  return 0;
}

int fn3() {
  // save the last time you blinked the LED
  previousMillis1 = currentMillis1;

  // if the LED is off turn it on and vice-versa:
  if (ledState1 == LOW)
    ledState1 = HIGH;
  else
    ledState1 = LOW;

  // set the LED with the ledState of the variable:
  digitalWrite(ledPin1, ledState1);
  return 0;
}

int fn4() {
  // save the last time you blinked the LED
  previousMillis2 = currentMillis2;

  // if the LED is off turn it on and vice-versa:
  if (ledState2 == LOW)
    ledState2 = HIGH;
  else
    ledState2 = LOW;

  // set the LED with the ledState of the variable:
  digitalWrite(ledPin2, ledState2);
  return 0;
}

int fn5(){
  switch (fanstate){
    case(0):
      fanstate = 1;
    case(1):
      fanstate = 2;
    case(2):
      fanstate = 3;
    case(3):
      fanstate = 0;
      break;
  }
  buttonCooldown = true;
  delay(1);
  return 0;
}

int fn6(){
  buttonCooldown = false;
  delay(1);
  return 0;
}

int fn7(){
  int temp = 255/4;
  analogWrite(outputPin,temp*fanstate);
  delay(1);
}

int (*fnptr[8])() = {fn0,fn1,fn2,fn3,fn4,fn5,fn6,fn7};
/*
fnptr[0] = &fn0;
fnptr[1] = &fn1;
fnptr[2] = &fn2;
fnptr[3] = &fn3;
fnptr[4] = &fn4;
*/

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(5000);
  // set the digital pin as output:
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  currentMillis1 = millis();
  currentMillis2 = millis();
}




void loop() {
  Serial.print(fanstate);
  delay(50);
  // here is where you'd put code that needs to be running all the time.
  // check to see if it's time to blink the LED; that is, if the
  // difference between the current time and last time you blinked
  // the LED is bigger than the interval at which you want to
  // blink the LED.
  if(digitalRead(inputPin) == 1 && !buttonCooldown){
    Serial.print("Got here");
    if(fanstate==0){
      fanstate = 1;
    }
    else if(fanstate==1){
      fanstate = 2;
    }
    else if(fanstate == 2){
      fanstate = 3;
    }
    else{
      fanstate = 0;
    }

    buttonCooldown = true;
    analogWrite(outputPin,fanstate*(255/3));
    Serial.print(fanstate*(255/3));
    delay(1);
  
  }

  if(digitalRead(inputPin) == 0 && buttonCooldown){
    Serial.print("TURN OFF");
    buttonCooldown = false;
    delay(1);
    //fnptr[6]();
  }
  
  

  


}