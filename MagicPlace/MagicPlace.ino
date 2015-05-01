int start = 7; // Button to start the program
int stopButton = 2; // Button to stop the program when it made one round
int relay = 4; // relay to control the motor 


void setup() {
  // sets the data rate in bits per second for serial data transmission
  Serial.begin(9600); 
  pinMode(start, INPUT); // set start to input
  pinMode(stopButton, INPUT); // set stopButton to input
  pinMode(relay, OUTPUT); // set relay to output
  digitalWrite(relay, HIGH); // put the motor off
  
}

void loop() {
  
  int startState= digitalRead(start); // read the state of start
  int buttonState = digitalRead(stopButton); // read the state of stopbutton
  
  Serial.print("start state ");
  Serial.println(startState); // print the startstate in the seriele monitor
  Serial.print("button state ");
  Serial.println(buttonState); // print the buttonstate in the seriele monitor
  
  if(startState == HIGH){
    startMotor();
  }else if(buttonState == HIGH){
    stopMotor(); 
  }
}

void startMotor(){
  digitalWrite(relay, LOW); // start the motor
}

void stopMotor(){
  digitalWrite(relay, HIGH); // stop the motor
}











//else if(x = 0){
//    digitalWrite(relay, HIGH);
//  }
//    
//  Serial.print("x = ");
//  Serial.println(x);
//  
//  if(x == 1){
//    digitalWrite(relay, LOW);
//    
//    if(buttonState == HIGH){
//      digitalWrite(relay, HIGH);
//      x=0;
//    }
//  }
