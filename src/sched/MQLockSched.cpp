#include "MQLockSched.h"

#include "core/Processor.h"
#include "core/Thread.h"

MQLockSched::MQLockSched() {
    keyMax = 0;
    lock_owner = nullptr;
    active_queue.cur = 0;
}

MQLockSched::~MQLockSched() {
}

void MQLockSched::setup(int nr_cpus) {
    secondary_queue.reserve(nr_cpus);
    for (int i = 0; i < nr_cpus; ++i) {
        secondary_queue.append(ThreadQueue{0, {}});
    }
}

void MQLockSched::lock(Thread *t) {
    if (!lock_owner) {
        lock_owner = t;
        return;
    }

    auto &queue = secondary_queue[t->cpu->id];
    int key = ++keyMax;
    if (queue.cur > 0) {
        // Another waiting thread on same cpu
        queue.threads.insert(key, {t, 0, 3000});
    } else {
        // Wait in active queue
        queue.cur = key;
        active_queue.threads.insert(key, {t, 3000, 0});
    }

    candidate_map.insert(t, key);

    // Add extra time to all cpus' cycles
    // ...
}

void MQLockSched::waitLock(Thread *t) {
    int key = candidate_map.value(t);

    auto &queue = secondary_queue[t->cpu->id];
    if (active_queue.threads.contains(key)) {
        auto &info = active_queue.threads[key];
        info.active_slice--;
        if (info.active_slice == 0) {
            // Fall asleep
            info.sleep_slice = 3000;
            queue.threads.insert(key, info);
            active_queue.threads.remove(key);

            // Reset queue active flag
            if (queue.cur == key) {
                queue.cur = 0;
            }
            return;
        }
    } else if (queue.threads.contains(key)) {
        auto &info = queue.threads[key];
        info.sleep_slice--;
        if (info.sleep_slice == 0) {
            int active_slice_expected = 3000; // Calculated by priority

            // Check cpu's active thread
            if (queue.cur == 0 ||
                active_queue.threads.value(queue.cur).active_slice < active_slice_expected) {
                // Self awake
                active_queue.threads.insert(key, info);
                queue.threads.remove(key);

                // Change queue active flag
                queue.cur = key;
            } else {
                // Sleep again
            }
        }
    }

    // Add extra time to all cpus' cycles
    // ...
}

void MQLockSched::unlock() {
    // Previous lock release lock
    if (candidate_map.isEmpty()) {
        lock_owner = nullptr;
        return;
    }

    if (active_queue.threads.isEmpty()) {
        int j = -1;
        for (int i = 0; i < secondary_queue.size(); ++i) {
            if (!secondary_queue.at(i).threads.isEmpty()) {
                j = i;
            }
        }

        assert(j >= 0);

        auto &queue = secondary_queue[j];

        // Pass lock to the first cpu's first thread in secondary queue
        int key = *queue.threads.keyBegin();
        auto &info = *queue.threads.begin();

        lock_owner = info.t;

        // Maybe the next thread of current owner's cpu can be awaked
        // ...

        queue.threads.remove(key);

        return;
    } else {
        // Pass lock to next thread in active queue
        int key = *active_queue.threads.keyBegin();
        auto &info = *active_queue.threads.begin();

        auto &queue = secondary_queue[info.t->cpu->id];
        queue.cur = 0;
        lock_owner = info.t;

        // Maybe the next thread of current owner's cpu can be awaked
        // ...

        active_queue.threads.remove(key);
    }
    candidate_map.remove(lock_owner);

    // Add extra time to all cpus' cycles
    // ...
}

bool MQLockSched::isLocked(Thread *t) {
    return candidate_map.contains(t);
}
