#include "Scheduler.h"

Scheduler::Scheduler() {
}

Scheduler::~Scheduler() {
}

void Scheduler::setup(int nr_cpus) {
    Q_UNUSED(nr_cpus);
}

void Scheduler::lock(Thread *t) {
    Q_UNUSED(t)
}

void Scheduler::waitLock(Thread *t) {
    Q_UNUSED(t)
}

void Scheduler::unlock() {
}

bool Scheduler::isLocked(Thread *t) {
    Q_UNUSED(t)
    return false;
}
