/*---------------------------------------------------------------
 *  Author :  Dr. Jignesh Patoliya
 *  Purpose:  Blink LED every 1 second without RTOS
 *  E-mail:   jigs.science@gmail.com
 *  Version:  01 
 *  ---------------------------------------------------------------
 */
#define RED  23

#define BLUE 2

void setup() {
  // put your setup code here, to run once:
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  digitalWrite(RED, 1);
  digitalWrite(BLUE, 1);
  delay(1000);
  digitalWrite(RED, 0);
  digitalWrite(BLUE, 0);
  delay(1000);
  
  
}

/* DIY: Can you optimize this code with same objective ? if yes, develop code. */
