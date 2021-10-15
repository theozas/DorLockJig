/*Door lock testing jig firmvare v0.1
**Made by Paulius Miliunas
**for Chameleon Colour Systems use
**********************************
**Test jig test 5 locks in 2h by default
**5 led will iluminate when lock fails
**
*/


#include <Arduino.h>


//activation pin (will activate 5 relays by duing this will activate 5 locks)
int activator = 2;    //pin assigned to activation proces
int countOfCycles = 0;      //will count cucles during test
int testCycles = 200;       //set test cycle amoint
int doorLockActive = 40000; //time of lock activation per cycle (ms)
int doorLockRest = 5000;    //time when lock is in rest

//10 read pins it will read lock switch states 2x switches on one lock
int sensAray1[5] = {4,6,8,10,12};  //pins assigned to lock side switch
int sensAray2[5] = {3,5,7,9,11}; //pins assigned to solenoid side switch
boolean sensArayRead1[5]= {true,true,true,true,true};               //arrai to store lock side switch states
boolean sensArayRead2[5]= {true,true,true,true,true};;               //arai to store solenoid side switch states
  
//5x output pins to drive 5x LED do displai failed lock(later will be swaped with i shake screen)
int ledLockAray[5] = {A0,A1,A2,A3,A4};
int ledStates[5] = {0,0,0,0,0};
//function activates lock
void activateLocks(){
  //Serial.print("lock activated " );
  digitalWrite(activator,1);
}
//function deactivates lock
void deactivateLocks(){
  //Serial.println("lock deactivated " );
  digitalWrite(activator,0);
}
//function reads switches
void readDoorSwitches(){
  //Serial.println("Reading door sensors****" );
    for (unsigned int i = 0 ; i < 5; i++ ){
      if(digitalRead(sensAray1[i]) == LOW){
        //Serial.print("reading door swich 1 " );
        //Serial.print(sensArayRead1[i] );
        //Serial.print(" " );

        //Serial.println(i);
        sensArayRead1[i] = false;
      }
      if(digitalRead(sensAray2[i]) == LOW){
        //Serial.print("reading door swich 2 " );
        //Serial.print(sensArayRead2[i] );
        //Serial.println(" " );
        sensArayRead2[i] = false;
      }
      
    }
}
//function checks for fault
void checkDoorFaultActive(){
  for (unsigned int i = 0 ; i < 5 ; i++){
    if ( (sensArayRead1[i] == false) || (sensArayRead2[i] == false )){
      ledStates[i] = 1;
      digitalWrite(ledLockAray[i],1);
    }
  }
}

void setup() {
  Serial.begin(9300);

  pinMode(activator,OUTPUT);

  for (unsigned int i = 0 ; i < 5; i++ ){
    pinMode(sensAray1[i],INPUT);
    pinMode(sensAray2[i],INPUT);
  }
  
  for (unsigned int i = 0 ; i < 5; i++ ){
    pinMode(ledLockAray[i],OUTPUT);
    digitalWrite(ledLockAray[i],0);
  }

 
}

void loop() {
  
  Serial.println("Door lock test starting...");
  while(countOfCycles < testCycles){
    activateLocks();
    delay(500);                    //w8 for 5s
    readDoorSwitches();             //reading door switches
    checkDoorFaultActive();         //checking fault
    delay(500); 
    deactivateLocks();
    delay(1000);
    activateLocks();
    delay(3000);
    readDoorSwitches();             //reading door switches
    checkDoorFaultActive();         //checking fault
    delay(doorLockActive - 10000);  //w8 for set seconds minus 10000s
    readDoorSwitches();             //reading door switches
    checkDoorFaultActive();         //checking fault
    delay(5000);                    //w8 for 5s
    deactivateLocks();              //reading door switches
    delay(doorLockRest);            //w8 for 5s
    countOfCycles++;
    Serial.println("cycle");
  }
}