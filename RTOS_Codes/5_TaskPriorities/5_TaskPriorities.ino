/*---------------------------------------------------------------
 *  Author :  Dr. Jignesh Patoliya
 *  Purpose:  Task Priorities
 *  E-mail:   jigs.science@gmail.com
 *  Version:  01 
 *  ---------------------------------------------------------------
 */
#define BLUE 2
#define RED  23

void setup()
{
  //xTaskCreate(redLedControllerTask,"RED LED Task",4096,NULL,1,NULL);
  //xTaskCreate(blueLedControllerTask,"BLUE LED Task", 4096, NULL,3,NULL);
  xTaskCreatePinnedToCore(redLedControllerTask,"RED LED Task",4096,NULL,1,NULL);
  xTaskCreatePinnedToCore(blueLedControllerTask,"BLUE LED Task", 4096, NULL,3,NULL);
}


void redLedControllerTask(void *pvParameters)
{
  pinMode(RED,OUTPUT);
  while(1)
  {
   digitalWrite(RED,digitalRead(RED)^1); 
   for(volatile long i = 0; i < 5000000; i++);
  }
}

void blueLedControllerTask(void *pvParameters)
{
  pinMode(BLUE,OUTPUT);
  while(1)
  {
   digitalWrite(BLUE,digitalRead(BLUE)^1); 
   for(volatile long i = 0; i < 5000000; i++);
  }
}


void loop(){}

/*DIY-0: Only one LED will blink instead of two as per theory. Why? */

/*DIY-1: use delay(1000); instead of for(volatile long i = 0; i < 5000000; i++); and observe behavior. */

/*DIY-2: Try same code in Arduino UNO and observe output. */

/*DIY-3: As per theory delay generation using delay(); API or using loop based approach is blocking in nature why this is not applicable for ESP32. */

/*DIY-4: Create task with xTaskCreatePinnedToCore API instead of xTaskCreate and observe behavior? */

/*DIY-5: How to demonstrate starvation scenarion with the help of ESP32 */

/*DIY-6: Try delay(1000); instead of for loop once starvation happen in the code and observe output.
         replace delay(1000) with vTaskDelay(pdMS_TO_TICKS(1000)); and observe output.
         What is your observation in case of ESP32 */

/*DIY-6: Why lower priority task runs even when higher priority exists? */





