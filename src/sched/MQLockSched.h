#ifndef MQLOCKSCHED_H
#define MQLOCKSCHED_H

#include "core/Scheduler.h"

#include <QMap>
#include <QVector>

#include <list>

class MQLockSched : public Scheduler {
public:
    MQLockSched();
    ~MQLockSched();

    void setup(int nr_cpus) override;

    void lock(Thread *t) override;
    void waitLock(Thread *t) override;
    void unlock() override;
    bool isLocked(Thread *t) override;

    struct ThreadInfo {
        Thread *t;
        int active_slice;
        int sleep_slice;
    };

    struct ThreadQueue {
        int cur;
        QMap<int, ThreadInfo> threads;
    };

    Thread *lock_owner;
    ThreadQueue active_queue;
    QVector<ThreadQueue> secondary_queue;

    int keyMax;
    QMap<Thread *, int> candidate_map;
};

#endif // MQLOCKSCHED_H
