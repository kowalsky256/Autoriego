
int sensor1Pin = A0;    // select the input pin for the humidity sensor 1
int sensor2Pin = A1;    // select the input pin for the humidity sensor 2
int sensor3Pin = A2;    // select the input pin for the humidity sensor 3

int relay1Pin = 2;      // select the pin for the relay 1
int relay2Pin = 3;      // select the pin for the relay 2
int relay3Pin = 4;      // select the pin for the relay 3

int pump1Pin = 12;      // sepect the pin for the pump
int sensorValue;  // variable to store the value coming from the sensor
int secco; // variable to store the value coming from the mapping of sensorValue
int input;
bool regando;
const int buttonPin=6;
int buttonState=0;
bool botton_ON=true;


int LIMITE_HUMEDO=55;
int LIMITE_SECO=75;


void setup() {
  Serial.begin(9600);
  // declare the relay1Pin as an OUTPUT:
  pinMode(relay1Pin, OUTPUT);
  pinMode(relay2Pin, OUTPUT);
  pinMode(relay3Pin, OUTPUT);
  pinMode(buttonPin, INPUT);
  
  pinMode(pump1Pin, OUTPUT);

  //InitialState
  digitalWrite(relay1Pin, LOW);
  digitalWrite(relay2Pin, LOW);
  digitalWrite(relay3Pin, LOW);
  
  digitalWrite(pump1Pin, LOW);
  regando=false;
  
}

void loop() {
  // FOR TEST
  /*regando=false;
  for (input=100; input >= 0; input=input-1){
    doTest(input, relay1Pin, pump1Pin);
    delay(1000);   
  }

  regando=true;
  input=0;
  for (input=0; input <= 100; input=input+1){
    doTest(input, relay1Pin, pump1Pin);
    delay(1000);   
  }*/

 
    if (!botton_ON){
  
     doTestCapacitador(A2, relay2Pin, pump1Pin, 2);
     doTestCapacitador(A1, relay1Pin, pump1Pin, 1);
     //doTask(sensor1Pin, relay1Pin, pump1Pin);
     //doTask(sensor2Pin, relay2Pin, pump1Pin);
     //doTask(sensor3Pin, relay3Pin, pump1Pin);
     delay(3000);        // delay in between reads for stability
  }
  else{
    digitalWrite(relay1Pin, HIGH);
    digitalWrite(relay2Pin, HIGH);
    digitalWrite(relay3Pin, HIGH);
  }
}



void doTestCapacitador (int sensor, int relay, int pumpIn, int number) {
  sensorValue = analogRead(sensor);
  //Serial.println(sensorValue);

  secco = map( sensorValue, 15,650, 0,100);
  Serial.println(String(number) + ": " + String(secco) );

  /*if(regando){
    Serial.println("regando");
  }else{
    Serial.println("NO regando");
  }
  Serial.println(secco);

  if (secco >= LIMITE_SECO && !regando){ 
     digitalWrite(relay, HIGH);    //to activate the solenoid valve relay
     digitalWrite(pumpIn, HIGH);     //to activate the pump relay
     regando=true;
     
   }
   else if (secco <= LIMITE_HUMEDO && regando){
     digitalWrite(relay, LOW);
     digitalWrite(pumpIn, LOW);
     regando=false;
     
   }*/
}


void doTask (int sensor, int relay, int pumpIn) {
  sensorValue = analogRead(sensor);
  secco = map( sensorValue, 200,500, 0,100);

  if(regando){
    Serial.println("regando");
  }else{
    Serial.println("NO regando");
  }
  Serial.println(secco);

  if (secco >= LIMITE_SECO && !regando){ 
     digitalWrite(relay, HIGH);    //to activate the solenoid valve relay
     digitalWrite(pumpIn, HIGH);     //to activate the pump relay
     regando=true;
     
   }
   else if (secco <= LIMITE_HUMEDO && regando){
     digitalWrite(relay, LOW);
     digitalWrite(pumpIn, LOW);
     regando=false;
     
   }
}




void doTest (int sensor, int relay, int pumpIn) {
  secco=sensor;
  if(regando){
    Serial.println("regando");
  }else{
    Serial.println("NO regando");
  }
  Serial.println(secco);

  if (secco >= LIMITE_SECO && !regando){ 
     digitalWrite(relay, HIGH);    //to activate the solenoid valve relay
     digitalWrite(pumpIn, HIGH);     //to activate the pump relay
     regando=true;
     
   }
   else if (secco <= LIMITE_HUMEDO && regando){
     digitalWrite(relay, LOW);
     digitalWrite(pumpIn, LOW);
     regando=false;
     
   }
}
