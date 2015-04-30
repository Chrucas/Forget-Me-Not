int start = 7; // om programma te starten
int stopButton = 2; // om de motor te stoppen
int relay = 4; // om de motor te laten draaien HIGH is uit LOW is aan
//static int x ;

void setup() {
  
  Serial.begin(9600);
  pinMode(start, INPUT);
  pinMode(stopButton, INPUT);
  pinMode(relay, OUTPUT);
  digitalWrite(relay, HIGH);
}

void loop() {
  
  int startState= digitalRead(start);
  int buttonState = digitalRead(stopButton);
  
  Serial.print("start state ");
  Serial.println(startState);
  Serial.print("button state ");
  Serial.println(buttonState);
  
  if(startState == HIGH){
    startMotor();
  }else if(buttonState == HIGH){
    stopMotor(); 
  }
}

void startMotor(){
  digitalWrite(relay, LOW);
}

void stopMotor(){
  digitalWrite(relay, HIGH);
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
