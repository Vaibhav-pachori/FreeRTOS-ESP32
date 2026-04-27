# FreeRTOS-ESP32 🚀

A structured, hands-on collection of **FreeRTOS programs** written for the **ESP32** using the Arduino framework, simulated in **PicsimLab**. These examples cover the complete task management layer of FreeRTOS — from bare-metal blink to race condition analysis — built progressively from scratch.

> 🎓 Learned under the guidance of **Jignesh Patolia**, Renowned Embedded Systems Engineer at **eInfochips (An Arrow Company)**, during a hands-on FreeRTOS workshop.

---

## 📁 Repository Structure

```
FreeRTOS-ESP32/
└── RTOS_Codes/
    ├── 0_blink/                      # Bare-metal LED blink (no RTOS)
    ├── 1_blink_RTOS/                 # First FreeRTOS task with xTaskCreate
    ├── 2_TaskProfiler/               # Multiple tasks + stack/CPU profiling
    ├── 3_TaskInstance/               # Task instances using pvParameters
    ├── 4_vTaskDelay_and_DelayUntil/  # vTaskDelay vs vTaskDelayUntil
    ├── 5_TaskPriorities/             # Priority levels + starvation demo
    ├── 6_RealTimeApplication/        # Real-time LED control application
    ├── 7_PreemptionTask/             # Preemption + vTaskPrioritySet
    ├── 8_TaskSuspend_and_Resume/     # vTaskSuspend / vTaskResume
    ├── 9_TaskDelete/                 # vTaskDelete + idle hook
    └── 10_RaceCondition/             # Race condition on shared variable demo
```

---

## 📌 Concepts Covered

| # | Folder | FreeRTOS Concept |
|---|--------|-----------------|
| 0 | `0_blink` | Bare-metal baseline — no RTOS, standard Arduino loop |
| 1 | `1_blink_RTOS` | `xTaskCreate`, task function structure, scheduler start |
| 2 | `2_TaskProfiler` | Multiple concurrent tasks, stack high watermark profiling |
| 3 | `3_TaskInstance` | Single function → multiple task instances via `pvParameters` |
| 4 | `4_vTaskDelay_and_DelayUntil` | `vTaskDelay` (relative) vs `vTaskDelayUntil` (absolute, drift-free) |
| 5 | `5_TaskPriorities` | Priority assignment, preemption, CPU starvation observation |
| 6 | `6_RealTimeApplication` | Real-time design: LED control with strict periodic timing |
| 7 | `7_PreemptionTask` | Dynamic priority change with `vTaskPrioritySet` |
| 8 | `8_TaskSuspend_and_Resume` | `vTaskSuspend` / `vTaskResume` — runtime task lifecycle control |
| 9 | `9_TaskDelete` | `vTaskDelete`, idle task hook (`vApplicationIdleHook`) |
| 10 | `10_RaceCondition` | Race condition on shared global — problem identification & root cause |

---

## 🛠 Tools & Platform

| Tool | Details |
|------|---------|
| **Board** | ESP32 (Dual-core, 240 MHz) |
| **Simulator** | PicsimLab |
| **IDE** | Arduino IDE |
| **RTOS** | FreeRTOS (built-in ESP32 Arduino core) |
| **Language** | Embedded C / Arduino framework |

---

## 🧠 Key FreeRTOS APIs Used

```c
xTaskCreate()           // Create a new task
vTaskDelete()           // Delete a task
vTaskDelay()            // Relative delay (ms)
vTaskDelayUntil()       // Absolute periodic delay (drift-free)
vTaskPrioritySet()      // Change task priority at runtime
vTaskSuspend()          // Suspend a task
vTaskResume()           // Resume a suspended task
vTaskGetInfo()          // Get task stack & state info
vApplicationIdleHook()  // Hook into idle task
```

---

## ⚡ Learning Path

```
Bare-metal blink
      ↓
First RTOS task (xTaskCreate)
      ↓
Multiple tasks + profiling
      ↓
Task instances (pvParameters)
      ↓
Periodic timing (DelayUntil)
      ↓
Priorities + preemption
      ↓
Real-time application design
      ↓
Dynamic priority (vTaskPrioritySet)
      ↓
Suspend / Resume
      ↓
Task Delete + Idle Hook
      ↓
Race Condition (shared data problem identified)
```

---

## 🔬 How to Run

1. Open any `.ino` file in **Arduino IDE**
2. Select board: `ESP32 Dev Module`
3. Open **Arduino IDE** → load ESP32 board
4. Compile & upload via Arduino IDE
5. Observe output on **Serial Monitor** at `115200` baud

---

## 🎯 What's Next

These examples cover the **task management** layer of FreeRTOS. The next step is **inter-task communication & synchronization**:

- [ ] Queue (`xQueueCreate`, `xQueueSend`, `xQueueReceive`)
- [ ] Mutex (`xSemaphoreCreateMutex`) — fix the race condition from `10_RaceCondition`
- [ ] Binary Semaphore — ISR to task signalling
- [ ] Counting Semaphore
- [ ] Event Groups
- [ ] Software Timers

---

## 👨‍🏫 Workshop Credit

These programs were built as part of a structured **FreeRTOS workshop** conducted by:

**Jignesh Patolia**
Renowned Embedded Systems Engineer
**eInfochips — An Arrow Company**, Ahmedabad, India

eInfochips is one of India's leading embedded systems and semiconductor companies, working with global clients across automotive, medical, and industrial IoT domains.

---

## 👤 Author

**Vaibhav Pachori**
Embedded Systems Enthusiast | ESP32 | FreeRTOS | IoT
[GitHub](https://github.com/Vaibhav-pachori)

---

## 📄 License

This repository is for educational purposes. Feel free to use and reference with attribution.
