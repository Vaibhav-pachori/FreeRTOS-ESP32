/*---------------------------------------------------------------
 *  Author :  Dr. Jignesh Patoliya
 *  Purpose:  Blink LED every 1 second using RTOS
 *  E-mail:   jigs.science@gmail.com
 *  Version:  01 
 *  ---------------------------------------------------------------
 */

#define BLUE 2

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  xTaskCreate(blueLedControllerTask,"BlueLEDTask", 4096, NULL, 1,NULL);
}

void  blueLedControllerTask(void *pvParameters)
{
 pinMode(BLUE,OUTPUT);

  while(1)
  {
    digitalWrite(BLUE,digitalRead(BLUE)^1);
    delay(1000);
  }
}

/*DIY-0 : Comment Serial.begin(9600); and observe output */

/*DIY-1 : Does Serial.begin(); mandatory in FreeRTOS program? 
          If yes, why? if no, then provide possible soultion */

/*DIY-2 : Why we don’t call vTaskStartScheduler() in ESP32? */

/*DIY-3 : What happens if scheduler is not started? */

/*DIY-4 : Develop RTOS code to blink 2 LEDs at every 2 seconds */














/*
Boot → FreeRTOS scheduler starts
        ↓
     setup() (task)
        ↓
     loop() (task)
        ↓
   your tasks run
*/   