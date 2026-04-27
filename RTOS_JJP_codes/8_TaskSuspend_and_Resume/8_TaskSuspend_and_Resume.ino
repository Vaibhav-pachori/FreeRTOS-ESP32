/*---------------------------------------------------------------
 *  Author :  Dr. Jignesh Patoliya
 *  Purpose:  Task suspend and resume demonstration.
 *  E-mail:   jigs.science@gmail.com
 *  Version:  01 
 *  ---------------------------------------------------------------
 */

/*
Build a priority-based real-time temperature monitoring system using FreeRTOS where system behavior dynamically adapts based on critical conditions.

Requirements
Task A: Temperature Monitoring
Reads temperature every 1 second
Shares data with other tasks

Task B: Fan Control
Turns ON fan (LED) if temperature > 30°C
Turns OFF otherwise
Runs periodically

Task C: Emergency Handler (Critical Task)
If temperature > 35°C:
Preempts all tasks (highest priority)
Prints emergency alert
Suspends Fan Control task
When temperature returns to normal:
Restores priority
Resumes Fan Control task

RTOS Concepts Covered

Task creation
Task priority & preemption
Dynamic priority change
Task suspend / resume
Inter-task dependency
Periodic tasks
*/


#define LED 2

// Global variables
float temperature = 0.0;
bool fanStatus = false;

// Task handles
TaskHandle_t xHandleTempMonitor;
TaskHandle_t xHandleFanControl;
TaskHandle_t xHandleEmergency;

// Simulated temperature
float getSimulatedTemperature() {
  return random(28, 38);
}

//  Task A: Temperature Monitor
void TaskTemperatureMonitor(void *pvParameters) {
  for (;;) {
    temperature = getSimulatedTemperature();

    Serial.print("Temperature: ");
    Serial.println(temperature);

    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

// Task B: Fan Control
void TaskFanControl(void *pvParameters) {
  pinMode(LED, OUTPUT);

  for (;;) {
    if (temperature > 30.0) {
      digitalWrite(LED, HIGH);
      fanStatus = true;
    } else {
      digitalWrite(LED, LOW);
      fanStatus = false;
    }

    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

// Task C: Emergency Handler
void TaskEmergency(void *pvParameters) {
  bool isSuspended = false;

  for (;;) {
    if (temperature > 35.0) {
      
      //  Raise priority to highest
      vTaskPrioritySet(NULL, 4);

      Serial.println("!!! EMERGENCY: HIGH TEMP DETECTED !!!");

      //  Suspend Fan Control task (only once)
      if (!isSuspended) {
        vTaskSuspend(xHandleFanControl);
        Serial.println("Fan Control Task SUSPENDED");
        isSuspended = true;
      }

    } else {

      //  Restore priority
      vTaskPrioritySet(NULL, 1);

      //  Resume Fan Control task
      if (isSuspended) {
        vTaskResume(xHandleFanControl);
        Serial.println("Fan Control Task RESUMED");
        isSuspended = false;
      }
    }

    vTaskDelay(pdMS_TO_TICKS(300));
  }
}

void setup() {
  Serial.begin(115200);
  randomSeed(analogRead(0));

  xTaskCreate(TaskTemperatureMonitor, "TempMonitor", 2048, NULL, 2, &xHandleTempMonitor);
  xTaskCreate(TaskFanControl, "FanControl", 2048, NULL, 2, &xHandleFanControl);
  xTaskCreate(TaskEmergency, "Emergency", 2048, NULL, 1, &xHandleEmergency);
}

void loop() {}