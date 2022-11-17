#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <QString>

class Thread;

class Scheduler {
public:
    Scheduler();
    ~Scheduler();

    virtual void setup(int nr_cpus);

    /* Call by Thread */
    virtual void lock(Thread* t);
    virtual void waitLock(Thread* t);
    virtual void unlock();
    virtual bool isLocked(Thread* t);
};



#endif // SCHEDULER_H
