
int inPinA = 7;
int inPinB = 6;   
int inPinC = 5;
int ledPinA1 = 22;
int ledPinB1 = 24;
int ledPinC1 = 26;
int ledPinA2 = 28;
int ledPinB2 = 32;
int ledPinC2 = 34;
int ledPinA3 = 36;
int ledPinB3 = 38;
int ledPinC3 = 42;
bool expression = true;

void setup() {
  digitalWrite(ledPinA1, LOW);
  digitalWrite(ledPinB1, LOW);
  digitalWrite(ledPinC1, LOW);
    digitalWrite(ledPinA2, LOW);
    digitalWrite(ledPinB2, LOW);
    digitalWrite(ledPinC2, LOW);
      digitalWrite(ledPinA3, LOW);
      digitalWrite(ledPinB3, LOW);
      digitalWrite(ledPinC3, LOW);
      
 

  pinMode(inPinA, INPUT); 
  pinMode(inPinB, INPUT);        
  pinMode(inPinC, INPUT);
  
  pinMode(ledPinA1, OUTPUT);      
  pinMode(ledPinB1, OUTPUT);
  pinMode(ledPinC1, OUTPUT);
  
  pinMode(ledPinA2, OUTPUT);      
  pinMode(ledPinB2, OUTPUT);    
  pinMode(ledPinC2, OUTPUT);
        
  pinMode(ledPinA3, OUTPUT);      
  pinMode(ledPinB3, OUTPUT);      
  pinMode(ledPinC3, OUTPUT); 
   
  }


void loop() {
  if (digitalRead(inPinA) == HIGH)
   {
    digitalWrite(ledPinA1, HIGH);
    while(expression) {
      if (digitalRead(inPinB) == HIGH)
       {
        digitalWrite(ledPinB2, HIGH); 
         while(expression) {
          if (digitalRead(inPinC) == HIGH)
           {
            digitalWrite(ledPinC3, HIGH);
           } 
        }
       }
    }
      if (digitalRead(inPinC) == HIGH)
       {
        digitalWrite(ledPinC2, HIGH);
        while(expression) {
          if (digitalRead(inPinB) == HIGH)
           {
            digitalWrite(ledPinB3, HIGH);
           } 
        }
       } 
      }
  
   
  if (digitalRead(inPinB) == HIGH)
   {
    digitalWrite(ledPinB1, HIGH); 
    while(expression) {
      if (digitalRead(inPinA) == HIGH)
       {
        digitalWrite(ledPinA2, HIGH); 
        while(expression) {
          if (digitalRead(inPinC) == HIGH)
           {
            digitalWrite(ledPinC3, HIGH);
           } 
        }
       }
      if (digitalRead(inPinC) == HIGH)
       {
        digitalWrite(ledPinC2, HIGH);
        while(expression) {
          if (digitalRead(inPinA) == HIGH)
           {
            digitalWrite(ledPinA3, HIGH);
           } 
        }
       } 
      }
   }
   
  if (digitalRead(inPinC) == HIGH)
   {
    digitalWrite(ledPinC1, HIGH);
    while(expression) {
      if (digitalRead(inPinB) == HIGH)
       {
        digitalWrite(ledPinB2, HIGH); 
        while(expression) {
          if (digitalRead(inPinA) == HIGH)
           {
            digitalWrite(ledPinA3, HIGH);
           } 
        }
       }
      if (digitalRead(inPinA) == HIGH)
       {
        digitalWrite(ledPinA2, HIGH);
        while(expression) {
          if (digitalRead(inPinB) == HIGH)
           {
            digitalWrite(ledPinB3, HIGH);
           } 
        }
       }
      } 
      
   } 
  }

  
