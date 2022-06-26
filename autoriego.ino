int sensor1Pin = A0;    // select the input pin for the humidity sensor 1
int sensor2Pin = A1;    // select the input pin for the humidity sensor 2
int sensor3Pin = A2;    // select the input pin for the humidity sensor 3
int sensor4Pin = A3;    // select the input pin for the humidity sensor 4


int relay1Pin = 2;      // select the pin for the relay 1  ---> Activar Relay
int relay2Pin = 3;      // select the pin for the relay 2
int relay3Pin = 4;      // select the pin for the relay 3
int relay4Pin = 5;      // select the pin for the relay 4


int sensorValue;  // variable to store the value coming from the sensor
int secco; // variable to store the value coming from the mapping of sensorValue
int input;

const int buttonPin=6;
int buttonState=0;
bool botton_ON=false;


int LIMITE_HUMEDO[4] = {-44, -40,-15, -10};
int LIMITE_SECO[4] = {-42,-37,-11, -4};
int NUM_SENSOR[4] = {1,2,3,4};


bool isWatering[4] = {false, false, false, false};

bool IS_TEST=true;


void setup() {
  Serial.begin(9600);
  // declare the relay1Pin as an OUTPUT:
  pinMode(relay1Pin, OUTPUT);
  pinMode(relay2Pin, OUTPUT);
  pinMode(relay3Pin, OUTPUT);
  pinMode(relay4Pin, OUTPUT);
  pinMode(buttonPin, INPUT);
 
 

  //Disable relays (HIGH)
  digitalWrite(relay1Pin, HIGH);
  digitalWrite(relay2Pin, HIGH);
  digitalWrite(relay3Pin, HIGH);
  digitalWrite(relay4Pin, HIGH);
 

  IS_TEST=true;
 
}

void loop() {
 
  //CHECK MESURES: FOR TEST
  //doCheckMesure();

  //MAIN CONTROL
  doTask();
 

  delay(5000); // delay in between reads for stability
}



void doTask(){
  task(sensor1Pin, relay1Pin, 1);
  task(sensor2Pin, relay2Pin, 2);
  task(sensor3Pin, relay3Pin, 3);
  task(sensor4Pin, relay4Pin, 4);
  if(IS_TEST){
     Serial.println();
     Serial.println("*******************");
  }
 
}


void task (int sensor, int relay, int numSensor) {
 
  int limiteSeco=LIMITE_SECO[numSensor-1];
  int limiteHumedo=LIMITE_HUMEDO[numSensor-1];
  bool regando = isWatering[numSensor-1];
 
  sensorValue = analogRead(sensor);
  secco = map( sensorValue, 200,500, 0,100);
 
 
  if (secco >= limiteSeco && !regando){
     digitalWrite(relay, LOW);    //to activate the solenoid valve relay
     isWatering[numSensor-1]=true;
     
   }
   else if (secco <= limiteHumedo && regando){
     digitalWrite(relay, HIGH);
     isWatering[numSensor-1]=false;
     
   }

   if(IS_TEST){
     printResult(numSensor, regando, secco, limiteSeco, limiteHumedo );
   }
}

void printResult(int numSensor, bool regando, int secco, int limiteSeco, int limiteHumedo){
  String estaRegando = "NO regando";
  if(regando){
      estaRegando = "Regando";
  }
  Serial.print("Sensor ");
  Serial.print(numSensor);
  Serial.print(": ");
  Serial.print(secco);
  Serial.print(";  Limite seco: ");
  Serial.print(limiteSeco);
  Serial.print(";  Limite Humedo: ");
  Serial.print(limiteHumedo);
  Serial.print("--> ");
  Serial.println(estaRegando);
}

void doCheckMesure(){
 
  checkMesure(sensor1Pin, NUM_SENSOR[0]);
  checkMesure(sensor2Pin, NUM_SENSOR[1]);
  checkMesure(sensor3Pin, NUM_SENSOR[2]);
  checkMesure(sensor4Pin, NUM_SENSOR[3]);
  Serial.println();
  Serial.println("*******************");
 
}

void checkMesure(int sensor, int numSensor){
  sensorValue = analogRead(sensor);
  secco = map( sensorValue, 200,500, 0,100);
 
  Serial.print("Sensor ");
  Serial.print(numSensor);
  Serial.print(": ");
  Serial.println(secco);
}
