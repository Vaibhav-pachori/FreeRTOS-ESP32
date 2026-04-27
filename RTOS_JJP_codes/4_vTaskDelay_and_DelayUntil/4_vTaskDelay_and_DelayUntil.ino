/*---------------------------------------------------------------
 *  Author :  Dr. Jignesh Patoliya
 *  Purpose:  Demostration of vTaskDelay and vTaskDelayUntil
 *  E-mail:   jigs.science@gmail.com
 *  Version:  01 
 *  ---------------------------------------------------------------
 */
void TaskDelay(void *pvParameters);
void TaskDelayUntil(void *pvParameters);

void setup() {
  Serial.begin(115200);

  // Task using vTaskDelay (will show drift)
  xTaskCreate(TaskDelay, "Delay Task", 2048, NULL, 1, NULL);

  // Task using vTaskDelayUntil (accurate periodic)
  xTaskCreate(TaskDelayUntil, "DelayUntil Task", 2048, NULL, 1, NULL);
}

void loop() {}

//  Task with vTaskDelay (drift happens)
void TaskDelay(void *pvParameters)
{
  while(1)
  {
    Serial.print("vTaskDelay Time: ");
    Serial.println(millis());
    //  Artificial workload
    for(int i = 0; i < 500000; i++) {
      asm volatile("nop");
    }
    vTaskDelay(pdMS_TO_TICKS(1000));  // 1 second delay
  }
}

//  Task with vTaskDelayUntil (no drift)
void TaskDelayUntil(void *pvParameters)
{
  TickType_t xLastWakeTime = xTaskGetTickCount();

  while(1)
  {
    Serial.print("vTaskDelayUntil Time: ");
    Serial.println(millis());
    //  Artificial workload
    for(int i = 0; i < 500000; i++) {
      asm volatile("nop");
    }
    vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(1000)); // precise 1 sec
  }
}

/*DIY 0: Difference between periodic, aperiodic, sporadic? */

/*
Aperiodic → event happens anytime
Sporadic → event happens anytime BUT we control how often we respond

Sporadic = Aperiodic + Safety limit (minimum gap)

Scenario 1: Emergency Button

Aperiodic Behavior :: User presses emergency button, System reacts immediately every time

Problem:

If user presses button 10 times quickly,   System gets overloaded

Sporadic Behavior, First press → handled, Next press within 2 sec → ignored

Why?

To avoid system overload
To ensure stability

Scenario 2: Automotive

Airbag System, Crash sensor triggers event , You must NOT trigger airbag multiple times

First trigger → deploy airbag, Next triggers (within short time) → ignored --> This is sporadic control

Scenario 3: Server / Networking

Server receives requests

Handle all requests --> Which behaviour ???

Max 1 request per 100 ms --> Which behaviour ???

Sporadic task = controlled reaction to unpredictable events

Not periodic
Not fully free like aperiodic
Balanced approach for real systems

*/