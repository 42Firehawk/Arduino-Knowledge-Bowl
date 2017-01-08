#include "LedControl.h" 
LedControl lc=LedControl(5,7,6,1);

void setup() {                
lc.shutdown(0,false);
lc.setIntensity(0,8);
lc.clearDisplay(0);
}


void myDISP(int num) {
  int d1 = int(num / 1000 );
  int d2 = int((num - (1000 * d1)) / 100);
  int d3 = int((num - ((1000 * d1)+(100 * d2)))/10);
  int d4 = int((num - ((1000 * d1)+(100 * d2)+(10*d3)))); 
  lc.setDigit(0,0,d1,0);
  lc.setDigit(0,1,d2,0);
  lc.setDigit(0,2,d3,0);
  lc.setDigit(0,3,d4,0);
}
void loop() {

for (int num = 3000; num > -1; num--)
  {
  myDISP(num);
  delay(1000);
  }
}
