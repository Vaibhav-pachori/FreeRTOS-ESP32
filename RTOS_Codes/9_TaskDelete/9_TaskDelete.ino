/*---------------------------------------------------------------
 *  Author :  Dr. Jignesh Patoliya
 *  Purpose:  Task delete Demonstration.
 *  E-mail:   jigs.science@gmail.com
 *  Version:  01 
 *  ---------------------------------------------------------------
 */

 /*
 INDUSTRY PROBLEM STATEMENT

Build a priority-based real-time temperature monitoring system using FreeRTOS that dynamically manages tasks based on system conditions.

System Requirements

Task A: Temperature Monitoring
Reads temperature every 1 second
Shares data globally

Task B: Fan Control
Turns ON fan (LED) if temperature > 30°C
Suspended during emergency
Resumed when system normalizes

Task C: Emergency Handler (Critical Task)
If temperature > 35°C:
Increases its priority to highest
Suspends Fan Control task
If temperature normal:
Restores priority
Resumes Fan Control task

Task D: Logging Task
Prints system status every 2 seconds
If temperature < 29°C continuously for some time:
Deletes itself (simulating optimization)

Idle Task (Hook Function)
Runs when no task is ready
Prints system idle message (for demonstration)

RTOS Concepts Covered

Task creation
Priority & preemption
Suspend / Resume
Task deletion
Idle task
System optimization
*/


#define LED 2

// Global variables
float temperature = 0.0;
bool fanStatus = false;

// Task handles
TaskHandle_t xHandleTempMonitor;
TaskHandle_t xHandleFanControl;
TaskHandle_t xHandleEmergency;
TaskHandle_t xHandleLogger;

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

//  Task C: Emergency Handler
void TaskEmergency(void *pvParameters) {
  bool isSuspended = false;

  for (;;) {
    if (temperature > 35.0) {

      vTaskPrioritySet(NULL, 4);

      Serial.println("!!! EMERGENCY: HIGH TEMP !!!");

      if (!isSuspended) {
        vTaskSuspend(xHandleFanControl);
        Serial.println("Fan Task SUSPENDED");
        isSuspended = true;
      }

    } else {

      vTaskPrioritySet(NULL, 1);

      if (isSuspended) {
        vTaskResume(xHandleFanControl);
        Serial.println("Fan Task RESUMED");
        isSuspended = false;
      }
    }

    vTaskDelay(pdMS_TO_TICKS(300));
  }
}

//  Task D: Logger (Self-delete)
void TaskLogger(void *pvParameters) {
  int lowTempCounter = 0;

  for (;;) {

    Serial.print("LOG -> Temp: ");
    Serial.print(temperature);
    Serial.print(" | Fan: ");
    Serial.println(fanStatus ? "ON" : "OFF");

    if (temperature < 29.0) {
      lowTempCounter++;
    } else {
      lowTempCounter = 0;
    }

    //  Delete itself after stable low temp
    if (lowTempCounter >= 2) {
      Serial.println("Logger Task DELETING ITSELF...");
      Serial.println("Logger Task DELETING ITSELF...");
      Serial.println("Logger Task DELETING ITSELF...");
      Serial.println("Logger Task DELETING ITSELF...");
      Serial.println("Logger Task DELETING ITSELF...");

      vTaskDelete(NULL);
    }

    vTaskDelay(pdMS_TO_TICKS(2000));
  }
}

//  Idle Hook (runs when CPU is free)
void vApplicationIdleHook(void) {
  // Keep very light (no delay!)
  static int counter = 0;

  counter++;
  if (counter > 100000) {
    Serial.println("Idle Task Running...");
    counter = 0;
  }
}

void setup() {
  Serial.begin(115200);
  randomSeed(analogRead(0));

  xTaskCreate(TaskTemperatureMonitor, "TempMonitor", 2048, NULL, 2, &xHandleTempMonitor);
  xTaskCreate(TaskFanControl, "FanControl", 2048, NULL, 2, &xHandleFanControl);
  xTaskCreate(TaskEmergency, "Emergency", 2048, NULL, 1, &xHandleEmergency);
  xTaskCreate(TaskLogger, "Logger", 2048, NULL, 1, &xHandleLogger);
}

void loop() {}

// DIY: Keep an eye on Serial console and observe "Logger Task DELETING ITSELF..." appears or nor. If you never see, why? 

/*
What does “Task Delete” mean in Real System?

It means:
  A task is no longer required → free CPU + free memory

Real Industry Scenarios for Task Deletion

1. One-Time Initialization Task (Very Common)
Scenario

System boots → initializes sensors, peripherals, communication → then task is no longer needed.

Why Delete?
Initialization runs only once
Keeping task = waste of memory

Example
WiFi setup
Sensor calibration
Memory initialization

“After system setup is complete, the initialization task deletes itself to free resources.”

2. Firmware Update Task (OTA)

Scenario

Device downloads firmware → installs → task not needed anymore.

Why Delete?
Update is one-time operation
Keep system clean
Example
IoT OTA update system.

3. Fault Handling / Emergency Task
Scenario

Emergency occurs → special task handles it → once resolved → task removed.

Why Delete?
Emergency task not needed in normal operation

Example
Over-temperature handler
Fault recovery logic

4. Mode-Based Systems (Very Important)
Scenario

Device works in different modes:

Setup mode
Normal mode
Maintenance mode

Tasks differ per mode

Why Delete?
Tasks of previous mode are no longer required
Example

Smart devices
Automotive ECU modes

5. Resource Optimization (Embedded Systems)
Scenario

System has limited RAM → dynamically create/delete tasks based on need.

Why Delete?
Free heap memory
Avoid fragmentation
Example
Battery-powered IoT
Low-memory MCU

6. Timeout-Based Task (Very Practical)
Scenario

Task waits for event (like user input).
If not received within time → terminate task.

Why Delete?
Avoid idle/wasted tasks
Example
Login/session timeout
Communication timeout

7. Logging / Debug Task (Your Current Example)
Scenario

Logging enabled only during debug or initial phase.

Why Delete?
Reduce CPU usage in production
Example
Serial logging
Debug monitoring
Best Scenario for Your Workshop (Recommended)
Final Story You Can Tell

“System starts in DEBUG mode where logging task prints data. After system stabilizes, logging task deletes itself to save CPU and memory.”


When to Delete Task?
Task completed its purpose
No longer required
Want to free resources

When NOT to Delete?
Periodic task
Critical system task
Task needed again later (use suspend instead)

Interview Questions
Difference: Suspend vs Delete?

Suspend	          Delete
Temporary stop	  Permanent removal
Can resume	      Cannot resume
Keeps memory	    Frees memory

Can deleted task be restarted?

Answer:

No, it must be created again using xTaskCreate.

Final Takeaway
Task Delete = Resource Optimization + Lifecycle Completion
*/