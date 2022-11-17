#include "System.h"

#include "Scheduler.h"
#include "Thread.h"

#include <QDebug>
#include <QSharedPointer>

#include "Processor.h"
#include "Thread.h"
#include "sched/MQLockSched.h"
#include "sched/PThreadSched.h"

System::System() {
}

System::~System() {
}

void System::run() {
    qDebug() << "CPU Cores:" << nr_cpus;
    qDebug() << "Threads:" << nr_threads;
    qDebug() << "Critical Section:" << cs_len;
    qDebug() << "Delay:" << delay;
    qDebug() << "Total cycles:" << tot;
    qDebug() << "Scheduler:" << sched_id;

    // Create scheduler
    QSharedPointer<Scheduler> sche;
    if (sched_id == 0) {
        sche = QSharedPointer<PThreadSched>::create();
    } else {
        sche = QSharedPointer<MQLockSched>::create();
    }
    sche->setup(nr_cpus);

    // Create cpus
    QVector<QSharedPointer<Processor>> cpus;
    for (int i = 0; i < nr_cpus; ++i) {
        auto cpu = QSharedPointer<Processor>::create();
        cpu->id = i;
        cpus.append(cpu);
    }

    // Create threads
    QVector<QSharedPointer<Thread>> threads;
    for (int i = 0; i < nr_threads; ++i) {
        auto t = QSharedPointer<Thread>::create();
        auto cpu = cpus.at(i % nr_cpus);
        t->cpu = cpu;
        t->sche = sche;
        t->id = i;
        t->delay = delay;
        t->critical_section = cs_len;
        cpu->threads.insert(i, t);
        threads.append(t);
    }

    // Execute
    for (int i = 0; i < tot; ++i) {
        for (int j = 0; j < nr_cpus; ++j) {
            cpus.at(j)->forwardCycle();
        }
    }
}
