#include <EEPROM.h>
const long interval = 5000; //ennyit kesleltet (ms)
//const long interval = 900000; //ennyit kesleltet (ms)
//onst long interval = 30000; //ennyit kesleltet (ms)

#define LIGHTSENSORPIN A0


const int ledPin = LED_BUILTIN;// the number of the LED pin
const int lightOffOut = 10;
const int ajtoOut = 11;
const int mozgasOut = 12;

const int ajtoIn = 5; // the number of the LED pin
const int mozgasIn = 6; // the number of the LED pin

const long interval2 = 1000;
unsigned long previousMillis = 0; 
unsigned long previousMillis2 = 0;        

unsigned int data = 0;
bool outputFlag = false;
bool input1Last = false;
bool input2Last = false;
bool vilagosVan = true;

bool valtasFlag1 = false;
bool valtasFlag2 = false;
int kapcsolasiSzint = 0;
int hiszterezis=10;

int smooth(){
  int i;
  int value = 0;
  int numReadings = 20;

  for (i = 0; i < numReadings; i++){
    // Read light sensor data.
    value = value + analogRead(LIGHTSENSORPIN);

    // 1ms pause adds more stability between reads.
    delay(1);
  }

  // Take an average of all the readings.
  value = value / numReadings;

  return value;
}

void writeUnsignedIntIntoEEPROM(int address, unsigned int number)
{
	EEPROM.write(address, number >> 8);
	EEPROM.write(address + 1, number & 0xFF);
}

unsigned int readUnsignedIntFromEEPROM(int address)
{
	return (EEPROM.read(address) << 8) + EEPROM.read(address + 1);
}


void setup() {
	Serial.begin(9600);
	// set the digital pin as output:
	pinMode(ledPin, OUTPUT);
	pinMode(lightOffOut, OUTPUT);
	pinMode(ajtoOut, OUTPUT);
	pinMode(mozgasOut, OUTPUT);
	pinMode(ajtoIn, INPUT_PULLUP);
	pinMode(mozgasIn, INPUT_PULLUP);
	pinMode(LIGHTSENSORPIN,  INPUT);  

	kapcsolasiSzint = readUnsignedIntFromEEPROM(0);
	Serial.print("Az uj kapcsolasi hatarertek: ");
	Serial.println(kapcsolasiSzint);

}

void loop() {
	//Serial.println(millis());
	//delay(1000);
int sensorValue= smooth();
unsigned long currentMillis = millis();
unsigned long currentMillis2 = millis();

if (currentMillis2 - previousMillis2 >= interval2){
	previousMillis2 = currentMillis2;
  	Serial.print("Mert fenyero: ");
  	Serial.println(sensorValue);

	Serial.print("A beallitott hatarartek: ");
  	Serial.println(kapcsolasiSzint);

	if(vilagosVan){
		Serial.println("Vilagos van");
	}
	else
	{
		Serial.println("Sotet van");
	}
	Serial.println("");
}

	if(Serial.available() > 0){
		data = Serial.parseInt();
		if (0 < data && data < 1024) {
			writeUnsignedIntIntoEEPROM(0, data);
			kapcsolasiSzint = readUnsignedIntFromEEPROM(0);
			Serial.print("Az uj kapcsolasi hatarertek: ");
			Serial.println(kapcsolasiSzint);
		}
		else
		{
			Serial.println("Ervenytelen adat");
		}
	}
	

	

	



//Ha vilagos van nem tovabbitjuk az ajto es a mozgas jelet, es lekapcsoljuk a villanyt
	if(sensorValue>(kapcsolasiSzint+hiszterezis) && vilagosVan==false){
		vilagosVan=true;
		digitalWrite(ledPin, HIGH);
			digitalWrite(lightOffOut, HIGH);
			delay(1000);
			digitalWrite(ledPin, LOW);
			digitalWrite(lightOffOut, LOW);
			outputFlag = true;
		
	}
	else if(sensorValue<(kapcsolasiSzint-hiszterezis) && vilagosVan==true ){
		vilagosVan=false;
		
	}

//Ha sotet van es van mozgas, mukodtetjuk a vilagitast- Egeszen addig vilagit, mig mozgas van. + 15 perc
	if(!vilagosVan){	
	
			//Az ajto es a mozgas kimeneteket a bemenetekkel megegyezo szintre allitjuk
		if (!digitalRead(ajtoIn)) {
			digitalWrite(ajtoOut, HIGH);
		}
		else
		{
			digitalWrite(ajtoOut, LOW);
		}

		if (!digitalRead(mozgasIn)) {
			digitalWrite(mozgasOut, HIGH);
		}
		else {
			digitalWrite(mozgasOut, LOW);
		}
		
		//ajto valtozas figyeles
		if (digitalRead(ajtoIn) != input1Last) {
			input1Last = digitalRead(ajtoIn);
			valtasFlag1 = true;
		}
		else {
			valtasFlag1 = false;
		}
		//mozgas figyeles
		if (digitalRead(mozgasIn) != input2Last) {
			input2Last = digitalRead(mozgasIn);
			valtasFlag2 = true;
		}
		else {
			valtasFlag2 = false;
		}

		//Ha mozgas vagy ajtonyitas van, nullazzuk az idozitot
		if (valtasFlag1 || !digitalRead(mozgasIn)) {
			previousMillis = currentMillis;
			outputFlag = false;
		}
		//Ha letelt az idozites, lekapcsoljuk a vilagitast
		if ((currentMillis - previousMillis >= interval) && !outputFlag) {		
			digitalWrite(ledPin, HIGH);
			digitalWrite(lightOffOut, HIGH);
			delay(1000);
			digitalWrite(ledPin, LOW);
			digitalWrite(lightOffOut, LOW);
			outputFlag = true;
		}
	}
	else
	{
		//ajto valtozas figyeles
		if (digitalRead(ajtoIn) != input1Last) {
			input1Last = digitalRead(ajtoIn);
			valtasFlag1 = true;
		}
		else {
			valtasFlag1 = false;
		}
		//mozgas figyeles
		if (digitalRead(mozgasIn) != input2Last) {
			input2Last = digitalRead(mozgasIn);
			valtasFlag2 = true;
		}
		else {
			valtasFlag2 = false;
		}

		//Ha mozgas vagy ajtonyitas van, nullazzuk az idozitot
		if (valtasFlag1 || !digitalRead(mozgasIn)) {
			previousMillis = currentMillis;
			outputFlag = false;
		}
		//Ha letelt az idozites, lekapcsoljuk a vilagitast
		if ((currentMillis - previousMillis >= interval) && !outputFlag) {
			digitalWrite(ledPin, HIGH);
			digitalWrite(lightOffOut, HIGH);
			delay(1000);
			digitalWrite(ledPin, LOW);
			digitalWrite(lightOffOut, LOW);
			outputFlag = true;
		}
	}
	
	
}

/*#include <EEPROM.h>

//const long interval = 900000; //ennyit kesleltet (ms)
#define LIGHTSENSORPIN A0


const int ledPin = LED_BUILTIN;// the number of the LED pin
const int lightOffOut = 10;
const int ajtoOut = 11;
const int mozgasOut = 12;

const int ajtoIn = 5; // the number of the LED pin
const int mozgasIn = 6; // the number of the LED pin


const long interval2 = 1000;
unsigned long previousMillis = 0; 
unsigned long previousMillis2 = 0;       

unsigned int data = 0;
bool outputFlag = false;
bool input1Last = false;
bool input2Last = false;
bool vilagosVan = true;

bool valtasFlag1 = false;
bool valtasFlag2 = false;
int kapcsolasiSzint = 0;
int hiszterezis=10;

int smooth(){
  int i;
  int value = 0;
  int numReadings = 10;

  for (i = 0; i < numReadings; i++){
    // Read light sensor data.
    value = value + analogRead(LIGHTSENSORPIN);

    // 1ms pause adds more stability between reads.
    delay(1);
  }

  // Take an average of all the readings.
  value = value / numReadings;

  return value;
}

void writeUnsignedIntIntoEEPROM(int address, unsigned int number)
{
  EEPROM.write(address, number >> 8);
  EEPROM.write(address + 1, number & 0xFF);
}

unsigned int readUnsignedIntFromEEPROM(int address)
{
  return (EEPROM.read(address) << 8) + EEPROM.read(address + 1);
}


void setup() {
  Serial.begin(9600);
  // set the digital pin as output:
  pinMode(ledPin, OUTPUT);
  pinMode(lightOffOut, OUTPUT);
  pinMode(ajtoOut, OUTPUT);
  pinMode(mozgasOut, OUTPUT);
  pinMode(ajtoIn, INPUT_PULLUP);
  pinMode(mozgasIn, INPUT_PULLUP);
  pinMode(LIGHTSENSORPIN,  INPUT);  

  kapcsolasiSzint = readUnsignedIntFromEEPROM(0);
  Serial.print("Az uj kapcsolasi hatarertek: ");
  Serial.println(kapcsolasiSzint);

}

void loop() {
  //Serial.println(millis());
  //delay(1000);
  int sensorValue= smooth();
  


  if(Serial.available() > 0){
    data = Serial.parseInt();
    if (0 < data && data < 1024) {
      writeUnsignedIntIntoEEPROM(0, data);
      kapcsolasiSzint = readUnsignedIntFromEEPROM(0);
      Serial.print("Az uj kapcsolasi hatarertek: ");
      Serial.println(kapcsolasiSzint);
    }
    else
    {
      Serial.println("Ervenytelen adat");
    }
  }
  

  unsigned long currentMillis = millis();
  unsigned long currentMillis2 = millis();
  //int value = digitalRead(ajtoIn);
if (currentMillis2 - previousMillis2 >= interval2){
  previousMillis2 = currentMillis2;
  Serial.print("fenyero: ");
  Serial.println(sensorValue);
}

  



//Ha vilagos van nem tovabbitjuk az ajto es a mozgas jelet, es lekapcsoljuk a villanyt
  if(sensorValue>(kapcsolasiSzint+hiszterezis) && vilagosVan==false && outputFlag==true){
    vilagosVan=true;
    
  }
  else if(sensorValue<(kapcsolasiSzint-hiszterezis) && vilagosVan==true && outputFlag==true){
    vilagosVan=false;
    
  }

//Ha sotet van es van mozgas, mukodtetjuk a vilagitast- Egeszen addig vilagit, mig mozgas van. + 15 perc
  if(!vilagosVan){  
  
      //Az ajto es a mozgas kimeneteket a bemenetekkel megegyezo szintre allitjuk
    if (!digitalRead(ajtoIn)) {
      digitalWrite(ajtoOut, HIGH);
    }
    else
    {
      digitalWrite(ajtoOut, LOW);
    }

    if (!digitalRead(mozgasIn)) {
      digitalWrite(mozgasOut, HIGH);
    }
    else {
      digitalWrite(mozgasOut, LOW);
    }
    
    //ajto valtozas figyeles
    if (digitalRead(ajtoIn) != input1Last) {
      input1Last = digitalRead(ajtoIn);
      valtasFlag1 = true;
    }
    else {
      valtasFlag1 = false;
    }
    //mozgas figyeles
    if (digitalRead(mozgasIn) != input2Last) {
      input2Last = digitalRead(mozgasIn);
      valtasFlag2 = true;
    }
    else {
      valtasFlag2 = false;
    }

    //Ha mozgas vagy ajtonyitas van, nullazzuk az idozitot
    if (valtasFlag1 || !digitalRead(mozgasIn)) {
      previousMillis = currentMillis;
      outputFlag = false;
    }
    //Ha letelt az idozites, lekapcsoljuk a vilagitast
    if ((currentMillis - previousMillis >= interval) && !outputFlag) {    
      digitalWrite(ledPin, HIGH);
      digitalWrite(lightOffOut, HIGH);
      delay(1000);
      digitalWrite(ledPin, LOW);
      digitalWrite(lightOffOut, LOW);
      outputFlag = true;
    }
  }
  
  
}
*/
