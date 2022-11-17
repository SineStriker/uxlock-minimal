#ifndef THREAD_H
#define THREAD_H

#include <QList>
#include <QSharedPointer>

class Processor;
class Scheduler;

class Thread {
public:
     Thread();
    ~Thread();

    void forward();

    /* Progress */
    int index;
    int last_cycle;
    QList<int> waits;
    int lock_times;

    /* Properties */
    QSharedPointer<Processor> cpu;
    QSharedPointer<Scheduler> sche;
    int id;
    int delay;
    int critical_section;
};



#endif // THREAD_H
