#include "Thread.h"

#include "Processor.h"
#include "Scheduler.h"

Thread::Thread() {
    index = 0;
    last_cycle = -1;
    lock_times = 0;
}

Thread::~Thread() {
}

void Thread::forward() {
    if (!sche->isLocked(this)) {
        if (index == delay) {
            // Enter critical section
            sche->lock(this);
            lock_times++;

            // Record wait begin
            last_cycle = cpu->cycles;
        } else if (index == delay + critical_section) {
            // Exit critical section
            sche->unlock();
        } else if (index > delay) {
            // Execute critical section
            if (last_cycle >= 0) {
                // Record wait end
                waits.append(cpu->cycles - last_cycle);

                last_cycle = -1;
            }

            // Do critical section
        } else {
            // Do plain section
        }

        // Move forward
        index = (index + 1) % (delay + critical_section + 1);
    } else {
        // Wait
        sche->waitLock(this);
    }
}
