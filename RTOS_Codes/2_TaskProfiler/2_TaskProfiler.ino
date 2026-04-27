/*---------------------------------------------------------------
 *  Author :  Dr. Jignesh Patoliya
 *  Purpose:  3 LEDs blink code.
 *  E-mail:   jigs.science@gmail.com
 *  Version:  01 
 *  ---------------------------------------------------------------
 */


#define RED    22
#define YELLOW 23
#define BLUE   2

typedef int TaskProfiler;

TaskProfiler  RedLEDProfiler;
TaskProfiler  YellowLEDProfiler;
TaskProfiler  BlueLEDProfiler;

void setup()
{
  Serial.begin(9600);
  xTaskCreate(redLedControllerTask,
              "Red LED Task",
              100,
              NULL,
              1,
              NULL
              );
 xTaskCreate(blueLedControllerTask,
             "Blue LED Task",
             100,
             NULL,
             1,
             NULL);
 xTaskCreate(yellowLedControllerTask,
             "Yellow LED Task",
             100,
             NULL,
             1,
             NULL
             );
}

void redLedControllerTask(void *pvParameters)
{
  pinMode(RED,OUTPUT);

  while(1)
  {
   // Serial.println("This is RED");
  }
}

void blueLedControllerTask(void *pvParameters)
{
    pinMode(BLUE,OUTPUT);
    while(1)
    {
    //  Serial.print("This is BLUE");
    }
}

void yellowLedControllerTask(void *pvParameters)
{
   pinMode(YELLOW,OUTPUT);
  while(1)
  {
  //  Serial.println("This is YELLOW");
  }
}

void loop()
{}

/*DIY: Complete this code to blink three LEDs and observe output*/