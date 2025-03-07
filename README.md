# Philosophers 42

## 🏛️ Introduction
The **Dining Philosophers** problem is a classic concurrency challenge that tests synchronization mechanisms. This project aims to simulate philosophers who alternate between eating, thinking, and sleeping while avoiding deadlocks and starvation.

## 📜 Project Rules
- Each philosopher must **pick up two forks (mutexes/semaphores) to eat**.
- Philosophers **must not die** from starvation.
- There should be **no deadlocks**.
- A **supervisor thread** should monitor philosopher states.

## 🚀 Installation & Compilation
1. Clone the repository:
   ```bash
   git clone https://github.com/your-repo/philosophers.git
   cd philosophers
   ```
2. Compile the project:
   ```bash
   make
   ```
3. Run the program:
   ```bash
   ./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
   ```

## 📌 Implementation Details
### **1. Fork Management (Using Mutexes)**
- Each fork is a **mutex** (`pthread_mutex_t`).
- A philosopher must **lock** the left fork, then the right fork before eating.

### **2. Deadlock Prevention (Odd-Even Strategy)**
- **Even-indexed** philosophers take the **right fork first**.
- **Odd-indexed** philosophers take the **left fork first**.
- This prevents a circular deadlock where all philosophers hold one fork and wait indefinitely.

### **3. Printing Synchronization**
- A global **print mutex** prevents mixed-up outputs.

### **4. Death Monitoring (Supervisor Thread)**
- A separate thread monitors if a philosopher has exceeded `time_to_die` without eating.
- If a philosopher dies, the simulation stops.

## 🔄 Example Execution
```bash
./philo 5 800 200 200
```
- 5 philosophers
- 800ms before dying without eating
- 200ms to eat
- 200ms to sleep

## 🛠️ Authors
- **Hamza Almuhisen**
- **Alaa Almuhisen**

## 📜 License
This project follows the **42 School rules** and is for educational purposes only.