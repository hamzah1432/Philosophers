# Dining Philosophers Problem - Advanced Synchronization Implementation

## Overview | نظرة عامة
This project implements the **Dining Philosophers Problem** with robust synchronization mechanisms using mutexes and semaphores to prevent deadlocks and ensure fair resource allocation.

يُنفذ هذا المشروع **مشكلة الفلاسفة المتناولين للطعام** باستخدام آليات تزامن قوية مثل mutexes و semaphores لمنع التوقف التام وضمان التوزيع العادل للموارد.

## Components | المكونات
The system is divided into multiple programs, each handling a specific task:

تم تقسيم النظام إلى عدة برامج، حيث يتولى كل منها مهمة محددة:

### 1️⃣ Philosopher Program 🧠 | برنامج الفيلسوف
- Represents each philosopher as an independent process.
- Can **think**, **attempt to eat**, and **eat**.
- Requests forks when needed and releases them after eating.

- يُمثل كل فيلسوف كعملية مستقلة.
- يمكنه **التفكير**، **محاولة الأكل**، و **الأكل**.
- يطلب الشوكات عند الحاجة ويعيدها بعد الانتهاء.

### 2️⃣ Waiter Program 🍽️ | برنامج النادل
- Manages access to the forks to prevent **deadlock**.
- Receives eating requests from philosophers and grants permission if forks are available.
- Ensures fair distribution of eating opportunities.

- يتحكم في الوصول إلى الشوكات لمنع **التوقف التام (Deadlock)**.
- يستقبل طلبات الأكل من الفلاسفة ويمنح الإذن عند توفر الشوكات.
- يضمن توزيع الفرص بشكلٍ عادل.

### 3️⃣ Fork Manager 🍴 | برنامج إدارة الشوكات
- Keeps track of each fork's availability (in use or free).
- Ensures that no two neighboring philosophers use the same fork simultaneously.
- Works in coordination with the Waiter Program.

- يتابع حالة كل شوكة (متاحة أم مشغولة).
- يضمن عدم استخدام نفس الشوكة من قبل فيلسوفين متجاورين في نفس الوقت.
- يعمل بالتنسيق مع برنامج النادل.

### 4️⃣ Monitor & Logger 📊 | برنامج المراقبة والتسجيل
- Logs all actions, including when a philosopher starts or finishes eating.
- Detects and reports potential issues like **deadlock** or **starvation**.
- Helps in analyzing system performance and debugging.

- يسجل جميع الأحداث، مثل متى بدأ الفيلسوف الأكل أو انتهى منه.
- يكتشف ويبلغ عن المشكلات المحتملة مثل **التوقف التام** أو **التجويع**.
- يساعد في تحليل أداء النظام وتصحيح الأخطاء.

### 5️⃣ Simulation & UI 🎮 | برنامج المحاكاة والواجهة البصرية
- Provides a **graphical interface** or **console output** to visualize the system in action.
- Displays philosophers' states (thinking, waiting, eating) in real-time.
- Helps in understanding system behavior through visual representation.

- يوفر **واجهة رسومية** أو **إخراجًا نصيًا** لعرض النظام أثناء العمل.
- يعرض حالات الفلاسفة (التفكير، الانتظار، الأكل) في الوقت الفعلي.
- يساعد في فهم سلوك النظام من خلال التمثيل البصري.

## Synchronization Mechanisms | آليات التزامن

### 1️⃣ Mutex Locks 🔒
- Each fork is protected by a mutex
- Ensures atomic access to shared resources
- Prevents race conditions during fork acquisition
```c
pthread_mutex_t fork_mutexes[N_PHILOSOPHERS];
```

### 2️⃣ Death Detection Lock 💀
- Dedicated mutex for checking philosopher's status
- Prevents race conditions in death detection
- Ensures accurate timing of last meal
```c
pthread_mutex_t death_mutex;
```

### 3️⃣ Print Lock 📝
- Serializes output to prevent garbled messages
- Ensures clean console output for monitoring
```c
pthread_mutex_t print_mutex;
```

## Resource Management | إدارة الموارد

### Fork Acquisition Strategy 🍴
1. **Even-Odd Ordering**
   - Even-numbered philosophers grab right fork first
   - Odd-numbered philosophers grab left fork first
   - Prevents circular waiting
```c
if (philo_id % 2 == 0) {
    grab_right_fork();
    grab_left_fork();
} else {
    grab_left_fork();
    grab_right_fork();
}
```

### Deadlock Prevention ⚡
1. **Resource Hierarchy**
   - Forks are numbered
   - Always acquire lower-numbered fork first
   - Mathematically prevents circular wait

2. **Timeout Mechanism**
   - Maximum waiting time for forks
   - Philosophers release resources if timeout occurs
   - Prevents indefinite blocking

### Starvation Prevention 🍽️
- **Fair Access Timer**
  - Tracks last meal time for each philosopher
  - Prioritizes philosophers who haven't eaten recently
  - Ensures everyone gets a chance to eat

## State Management | إدارة الحالة

### Philosopher States | حالات الفيلسوف
```c
typedef enum {
    THINKING,    // Philosopher is thinking
    HUNGRY,      // Trying to acquire forks
    EATING,      // Currently eating
    SLEEPING     // Sleeping after eating
} PhiloState;
```

### Critical Section Protection | حماية القسم الحرج
```c
void safe_print_status(int id, char *status) {
    pthread_mutex_lock(&print_mutex);
    printf("%lld %d %s\n", get_time(), id, status);
    pthread_mutex_unlock(&print_mutex);
}
```

## Performance Optimization | تحسين الأداء

### 1️⃣ Lock Granularity
- Fine-grained locking for better concurrency
- Separate mutexes for different resources
- Minimal critical section duration

### 2️⃣ Memory Ordering
- Proper memory barriers
- Volatile variables for status flags
- Prevents compiler optimization issues

### 3️⃣ Cache Alignment
- Structured data to prevent false sharing
- Aligned mutex arrays
- Improved cache utilization

## Monitoring & Safety | المراقبة والسلامة

### Death Detection | اكتشاف الموت
```c
bool check_philosopher_death(t_philo *philo) {
    pthread_mutex_lock(&death_mutex);
    if (get_time() - philo->last_meal > philo->time_to_die) {
        set_simulation_stop();
        pthread_mutex_unlock(&death_mutex);
        return true;
    }
    pthread_mutex_unlock(&death_mutex);
    return false;
}
```

### Resource Cleanup | تنظيف الموارد
- Proper mutex destruction
- Memory deallocation
- Thread joining

## Workflow | سير العمل
1. Philosophers begin by **thinking** and waiting for forks.
2. A philosopher who wants to eat **sends a request to the Waiter**.
3. The Waiter checks **fork availability** via the Fork Manager.
4. If forks are available, the **Waiter grants permission**, and the philosopher starts eating.
5. Once done, the philosopher **returns the forks**, and the cycle repeats.
6. All actions are **logged** and **monitored**.
7. A **simulation interface** can be used to track real-time activities.

1. يبدأ الفلاسفة بـ **التفكير** والانتظار للحصول على الشوكات.
2. عندما يريد فيلسوف الأكل، **يرسل طلبًا إلى النادل**.
3. يتحقق النادل من **توفر الشوكات** عبر مدير الشوكات.
4. إذا كانت الشوكات متاحة، **يمنح النادل الإذن** ويبدأ الفيلسوف بالأكل.
5. بعد الانتهاء، **يعيد الفيلسوف الشوكات**، وتتكرر الدورة.
6. يتم **تسجيل جميع الأحداث ومراقبتها**.
7. يمكن استخدام **واجهة المحاكاة** لمتابعة الأنشطة في الوقت الفعلي.

## Benefits of Modular Approach | فوائد النهج المُقسَّم
✅ **Prevents Deadlock** – The Waiter Program ensures that philosophers don’t hold forks indefinitely.
✅ **Avoids Starvation** – Every philosopher gets a fair chance to eat.
✅ **Scalability** – More philosophers can be added without major changes.
✅ **Better Debugging** – Logs help in identifying performance issues.
✅ **Flexibility** – The system can be extended with alternative scheduling strategies.

✅ **يمنع التوقف التام** – يضمن برنامج النادل عدم احتفاظ الفلاسفة بالشوكات لفترة غير محدودة.
✅ **يتجنب التجويع** – يحصل كل فيلسوف على فرصة عادلة للأكل.
✅ **قابلية التوسع** – يمكن إضافة المزيد من الفلاسفة دون تغييرات كبيرة.
✅ **تحسين تصحيح الأخطاء** – تساعد السجلات في تحديد مشاكل الأداء.
✅ **مرونة أكبر** – يمكن توسيع النظام ليشمل استراتيجيات جدولة بديلة.

## How to Run | كيفية التشغيل
1. Start the **Waiter Program**.
2. Launch the **Fork Manager**.
3. Run multiple instances of the **Philosopher Program**.
4. Optionally, start the **Monitor & Logger** and **Simulation & UI**.
5. Observe how the system operates and adjust parameters as needed.

1. تشغيل **برنامج النادل**.
2. تشغيل **برنامج إدارة الشوكات**.
3. تشغيل عدة نسخ من **برنامج الفيلسوف**.
4. اختياريًا، تشغيل **برنامج المراقبة والتسجيل** و**برنامج المحاكاة والواجهة البصرية**.
5. مراقبة كيفية عمل النظام وتعديل الإعدادات حسب الحاجة.

## Usage Example | مثال الاستخدام
```bash
./philo 5 800 200 200 7
```
Arguments:
1. Number of philosophers
2. Time to die (ms)
3. Time to eat (ms)
4. Time to sleep (ms)
5. [Optional] Number of times each philosopher must eat

---
📌 *This implementation ensures thread-safety, prevents deadlocks, and maintains fair resource distribution through careful synchronization.* 🔄

📌 *يضمن هذا التنفيذ سلامة المواضيع، ويمنع التوقف التام، ويحافظ على التوزيع العادل للموارد من خلال التزامن الدقيق.* 🔄

