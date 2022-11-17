#include "PThreadSched.h"

#include "core/Processor.h"
#include "core/Thread.h"

#include <QRandomGenerator>

PThreadSched::PThreadSched() {
    lock_owner = nullptr;
}

PThreadSched::~PThreadSched() {
}

void PThreadSched::lock(Thread *t) {
    if (!lock_owner) {
        lock_owner = t;
        return;
    }

    candidates.append(t);
    candidate_set.insert(t);

    // Add extra time to all cpus' cycles
    // ...
}

void PThreadSched::waitLock(Thread *t) {
    Q_UNUSED(t);
}

void PThreadSched::unlock() {
    // Previous lock release lock
    if (candidate_set.isEmpty()) {
        lock_owner = nullptr;
        return;
    }

    // Acquire lock randomly
    int idx = QRandomGenerator::global()->bounded(0, candidates.size());
    lock_owner = candidates.at(idx);

    candidates.removeAt(idx);
    candidate_set.remove(lock_owner);

    // Add extra time to all cpus' cycles
    // ...
}

bool PThreadSched::isLocked(Thread *t) {
    return candidate_set.contains(t);
}
