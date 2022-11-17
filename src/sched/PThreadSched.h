#ifndef PTHREADSCHED_H
#define PTHREADSCHED_H

#include "core/Scheduler.h"

#include <QList>
#include <QSet>

class PThreadSched : public Scheduler {
public:
    PThreadSched();
    ~PThreadSched();

    void lock(Thread *t) override;
    void waitLock(Thread *t) override;
    void unlock() override;
    bool isLocked(Thread *t) override;

    Thread *lock_owner;
    QList<Thread *> candidates;
    QSet<Thread *> candidate_set;
};

#endif // PTHREADSCHED_H
