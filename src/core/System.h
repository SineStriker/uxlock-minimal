#ifndef SYSTEM_H
#define SYSTEM_H

class System {
public:
    System();
    ~System();

    int nr_cpus;
    int nr_threads;
    int cs_len;
    int delay;
    int tot;
    int sched_id;

    void run();
};

#endif //SYSTEM_H
