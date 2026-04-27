/*---------------------------------------------------------------
 *  Author :  Dr. Jignesh Patoliya
 *  Purpose:  Demonstrate task instance name.
 *  E-mail:   jigs.science@gmail.com
 *  Version:  01 
 *  ---------------------------------------------------------------
 */

#define   RED     23
#define   BLUE    22
#define   YELLOW  2


void setup()
{
  xTaskCreate(ledControllerTask,"RED LED Task",4096,(void *)RED ,1,NULL);
  xTaskCreate(ledControllerTask, "BLUE LED Task", 4096,(void *)BLUE,1,NULL);
  xTaskCreate(ledControllerTask,"YELLOW LED Task", 4096, (void *)YELLOW,1,NULL);
  
}

void ledControllerTask(void *pvParameters)
{ 
  
  uint16_t pin = (uint32_t)pvParameters;
  pinMode(pin, OUTPUT);
 
  while(1)
  {
    digitalWrite(pin,digitalRead(pin)^1);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void loop(){}

/*DIY 0: What is difference between delay and vTaskDelay? Which is obvious choice to generate delay? Why? */

/*DIY 1: How does vTaskDelay generate 1 second delay? */

/*
DIY 2: Design a system where:

Multiple zones (Room1, Room2, Room3) are monitored
Each zone has:
Sensor input (simulated or real)
LED indicator
Same task is reused for all zones

Demonstrates:

Single task function → multiple task instances
*/











































/*
FreeRTOS uses ticks as time unit. The expression 1000 / portTICK_PERIOD_MS converts milliseconds into ticks based on system tick rate. 
The scheduler then blocks the task for that number of ticks, resulting in a 1-second delay.

FreeRTOS works in ticks, not ms
portTICK_PERIOD_MS = ms per tick
Convert ms → ticks
Scheduler handles delay
*/






/*

#define ZONE1_LED 23
#define ZONE2_LED 22
#define ZONE3_LED 2

// Structure for task parameter
typedef struct {
  uint8_t ledPin;
  uint16_t threshold;
  const char* zoneName;
} ZoneConfig;

// Task function (REUSABLE)
void zoneMonitorTask(void *pvParameters)
{
  ZoneConfig *config = (ZoneConfig *)pvParameters;

  pinMode(config->ledPin, OUTPUT);

  while (1)
  {
    // Simulated sensor value
    int sensorValue = random(20, 100);

    Serial.print(config->zoneName);
    Serial.print(" Temp: ");
    Serial.println(sensorValue);

    // Decision logic
    if (sensorValue > config->threshold)
    {
      digitalWrite(config->ledPin, HIGH);
    }
    else
    {
      digitalWrite(config->ledPin, LOW);
    }

    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

// Define configurations
ZoneConfig zone1 = {ZONE1_LED, 50, "Zone 1"};
ZoneConfig zone2 = {ZONE2_LED, 60, "Zone 2"};
ZoneConfig zone3 = {ZONE3_LED, 70, "Zone 3"};

void setup()
{
  Serial.begin(115200);

  // Create multiple instances of SAME task
  xTaskCreate(zoneMonitorTask, "Zone1 Task", 2048, &zone1, 1, NULL);
  xTaskCreate(zoneMonitorTask, "Zone2 Task", 2048, &zone2, 1, NULL);
  xTaskCreate(zoneMonitorTask, "Zone3 Task", 2048, &zone3, 1, NULL);
}

void loop() {}
*/
