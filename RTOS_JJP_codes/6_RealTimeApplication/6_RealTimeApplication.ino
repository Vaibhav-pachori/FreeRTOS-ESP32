/*---------------------------------------------------------------
 *  Author :  Dr. Jignesh Patoliya
 *  Purpose:  Real time task management.
 *  E-mail:   jigs.science@gmail.com
 *  Version:  01 
 * 
 *  ---------------------------------------------------------------
 */
/* 
Problem Statement: 

Design a real-time Embedded application using FreeRTOS to simulate a temperature monitoring system where:

Task 1 reads a simulated temperature sensor every 1 second.

Task 2 controls an LED: it turns ON if temperature > 30°C and OFF otherwise.

Task 3 prints the system status (temperature and LED state) every 2 seconds.
*/  

#define LED 2
// Global variables
float temperature = 0.0;
bool ledStatus = false;

// Task handles (optional)
TaskHandle_t TaskReadTemp;
TaskHandle_t TaskControlLED;
TaskHandle_t TaskStatusPrint;

// Simulated temperature function
float getSimulatedTemperature() {
  return random(25, 36); // Random temperature between 25°C and 35°C
}

// Task 1: Read Temperature
void TaskReadTemperature(void *pvParameters) {
  (void) pvParameters;
  for (;;) {
    temperature = getSimulatedTemperature();
    vTaskDelay(pdMS_TO_TICKS(1000)); // Delay 1s
  }
}

// Task 2: Control LED based on temperature
void TaskControlLED(void *pvParameters) {
  (void) pvParameters;
  pinMode(LED, OUTPUT);
  for (;;) {
    if (temperature > 30.0) {
      digitalWrite(LED, HIGH);
      ledStatus = true;
    } else {
      digitalWrite(LED, LOW);
      ledStatus = false;
    }
    vTaskDelay(pdMS_TO_TICKS(500)); // Check every 0.5s
  }
}

// Task 3: Print System Status
void TaskStatusPrint(void *pvParameters) {
  (void) pvParameters;
  for (;;) {
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" °C | LED: ");
    Serial.println(ledStatus ? "ON" : "OFF");
    vTaskDelay(pdMS_TO_TICKS(2000)); // Print every 2s
  }
}

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));

  // Create tasks
  xTaskCreate(TaskReadTemperature, "ReadTemp", 128, NULL, 2, &TaskReadTemp);
  xTaskCreate(TaskControlLED, "LEDControl", 128, NULL, 2, &TaskControlLED);
  xTaskCreate(TaskStatusPrint, "StatusPrint", 128, NULL, 1, &TaskStatusPrint);
}

void loop() {
  // Empty - all logic handled in FreeRTOS tasks
}

// DIY-0: Why compilation error in this code?

// DIY-1: What are common mistakes in FreeRTOS task creation?





































































































/*
#define LED 2
// Global variables
float temperature = 0.0;
bool ledStatus = false;

// Task handles
TaskHandle_t xTaskReadTemp;
TaskHandle_t xTaskControlLED;
TaskHandle_t xTaskStatusPrint;

// Simulated temperature function
float getSimulatedTemperature() {
  return random(25, 36);
}

//  Task 1
void vTaskReadTemperature(void *pvParameters) {
  for (;;) {
    temperature = getSimulatedTemperature();
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

//  Task 2
void vTaskControlLED(void *pvParameters) {
  pinMode(LED, OUTPUT);

  for (;;) {
    if (temperature > 30.0) {
      digitalWrite(LED, HIGH);
      ledStatus = true;
    } else {
      digitalWrite(LED, LOW);
      ledStatus = false;
    }
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

//  Task 3
void vTaskStatusPrint(void *pvParameters) {
  for (;;) {
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" °C | LED: ");
    Serial.println(ledStatus ? "ON" : "OFF");

    vTaskDelay(pdMS_TO_TICKS(2000));
  }
}

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));

  xTaskCreate(vTaskReadTemperature, "ReadTemp", 4096, NULL, 2, &xTaskReadTemp);
  xTaskCreate(vTaskControlLED, "LEDControl", 4096, NULL, 2, &xTaskControlLED);
  xTaskCreate(vTaskStatusPrint, "StatusPrint", 4096, NULL, 1, &xTaskStatusPrint);
}

void loop() {}
*/