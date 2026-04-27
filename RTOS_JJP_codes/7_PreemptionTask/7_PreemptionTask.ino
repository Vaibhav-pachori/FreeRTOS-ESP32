/*---------------------------------------------------------------
 *  Author :  Dr. Jignesh Patoliya
 *  Purpose:  Real time task management with preemption
 *  E-mail:   jigs.science@gmail.com
 *  Version:  01 
 * 
 *  ---------------------------------------------------------------
 */

/* 
Problem Statement:

Build a priority-based real-time system for an Arduino that:

Task A (Temperature Monitoring): Continuously reads temperature every 1 second.

Task B (Fan Control): Checks the temperature and turns on a fan (represented by LED) if temperature > 30°C.

Task C (Emergency Task): If temperature exceeds 35°C, an emergency task preempts all others and increases its priority to the highest to alert the system.

Once the temperature normalizes, the emergency task lowers its priority back.
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
  return random(28, 38); // Between 28°C and 38°C
}

// Task A: Temperature Monitor
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

// Task C: Emergency Handler with dynamic priority
void TaskEmergency(void *pvParameters) {
  for (;;) {
    if (temperature > 35.0) {
      // Raise priority to highest
      vTaskPrioritySet(NULL, 4);
      Serial.println("!!! EMERGENCY: HIGH TEMP DETECTED !!!");
    } else {
      // Lower priority when normal
      vTaskPrioritySet(NULL, 1);
    }
    vTaskDelay(pdMS_TO_TICKS(300));
  }
}

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));

  // Create tasks with initial priorities
  xTaskCreate(TaskTemperatureMonitor, "TempMonitor", 4096, NULL, 2, &xHandleTempMonitor);
  xTaskCreate(TaskFanControl, "FanControl", 4096, NULL, 2, &xHandleFanControl);
  xTaskCreate(TaskEmergency, "Emergency", 4096, NULL, 1, &xHandleEmergency);
}

void loop() {
  // Empty – handled by FreeRTOS
}

/*DIY: Convert emergency task into sporadic task */