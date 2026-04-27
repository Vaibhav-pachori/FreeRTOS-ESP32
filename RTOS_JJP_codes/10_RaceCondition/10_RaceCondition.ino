/*---------------------------------------------------------------
 *  Author :  Dr. Jignesh Patoliya
 *  Purpose:  Race condition demonstrate.
 *  E-mail:   jigs.science@gmail.com
 *  Version:  01 
 * 
 *  ---------------------------------------------------------------
 */


/*
Design a FreeRTOS system where multiple tasks share common data (temperature and LED status). 
ue to lack of synchronization, the system should sometimes print incorrect or inconsistent values, demonstrating a race condition.

Expectation: Temperature and LED status should match
Temperature = 28°C but LED = ON ---> Wrong behaviour
Temperature = 33°C but LED = OFF ----> Wrong behaviour
*/


struct SystemState {
  float temperature;
  bool ledStatus;
};

SystemState state;

// Simulated temperature
float getTemp() {
  return random(25, 36);
}

//  Task 1: Update system state (Creates race condition)
void vTaskUpdate(void *pvParameters)
{
  for(;;)
  {
    float temp = getTemp();

    // Step 1: Update temperature
    state.temperature = temp;

    //  Artificial delay (creates race condition)
    vTaskDelay(pdMS_TO_TICKS(10));

    // Step 2: Update LED status
    if(temp > 30)
      state.ledStatus = true;
    else
      state.ledStatus = false;

    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

//  Task 2: Read system state
void vTaskRead(void *pvParameters)
{
  for(;;)
  {
    Serial.print("Temp: ");
    Serial.print(state.temperature);

    Serial.print(" | LED: ");
    Serial.println(state.ledStatus ? "ON" : "OFF");

    vTaskDelay(pdMS_TO_TICKS(100)); // Fast read
  }
}

void setup()
{
  Serial.begin(115200);
  randomSeed(analogRead(0));

  xTaskCreate(vTaskUpdate, "UpdateTask", 2048, NULL, 2, NULL);
  xTaskCreate(vTaskRead, "ReadTask", 2048, NULL, 1, NULL);
}

void loop() {}


/*
Display message whne mismatch happen to see race condition clearly

// Shared structure
struct SystemState {
  float temperature;
  bool ledStatus;
};

SystemState state;

// Simulated temperature
float getTemp() {
  return random(25, 36);
}

//  Task 1: Update state (Creates race condition)
void vTaskUpdate(void *pvParameters)
{
  for(;;)
  {
    float temp = getTemp();

    // Step 1: Update temperature
    state.temperature = temp;

    //  Artificial delay to create race window
    vTaskDelay(pdMS_TO_TICKS(50));

    // Step 2: Update LED status
    if(temp > 30)
      state.ledStatus = true;
    else
      state.ledStatus = false;

    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

//  Task 2: Read state (Detect mismatch)
void vTaskRead(void *pvParameters)
{
  for(;;)
  {
    bool expected = (state.temperature > 30);

    //  Print ONLY when mismatch happens
    if(expected != state.ledStatus)
    {
      Serial.print(" MISMATCH -> Temp: ");
      Serial.print(state.temperature);
      Serial.print(" | LED: ");
      Serial.println(state.ledStatus ? "ON" : "OFF");
    }

    vTaskDelay(pdMS_TO_TICKS(200)); // Slow enough to observe
  }
}

void setup()
{
  Serial.begin(115200);
  randomSeed(analogRead(0));

  xTaskCreate(vTaskUpdate, "UpdateTask", 2048, NULL, 2, NULL);
  xTaskCreate(vTaskRead, "ReadTask", 2048, NULL, 1, NULL);
}

void loop() {}

*/
