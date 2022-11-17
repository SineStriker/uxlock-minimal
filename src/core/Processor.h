#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <QMap>
#include <QSharedPointer>

class Thread;

class Processor {
public:
    Processor();
    ~Processor();

    void forwardCycle();

    /* Progress */
    int cycles;

    /* Properties */
    int id;
    QMap<int, QSharedPointer<Thread>> threads;
};


#endif // PROCESSOR_H
