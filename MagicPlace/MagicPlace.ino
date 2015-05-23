int startButton = 7; // Button to start the program
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
  
  int startState= digitalRead(startButton); // read the state of start
  int stopState = digitalRead(stopButton); // read the state of stopbutton
  
  Serial.print("Start state ");
  Serial.println(startState); // print the startstate in the seriele monitor
  Serial.print("Stop state ");
  Serial.println(stopState); // print the buttonstate in the seriele monitor
  
  /*A if statment to check if the startButton or the StopButton is pressed.
    When the startButton is pressed the motor will start moveing and if the
    stopbutton is pressed the motor will stop.*/
  if(startState == HIGH){
    startMotor();
    delay(3000); // the stopbutton is still pressed thats why we need a delay so the motor can move along the stopbutton
  }else if(stopState == HIGH){
    stopMotor(); 
  }
}

void startMotor(){
  digitalWrite(relay, LOW); // start the motor
}

void stopMotor(){
  digitalWrite(relay, HIGH); // stop the motor
}

