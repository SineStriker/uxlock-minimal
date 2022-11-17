#include "Processor.h"

#include "Thread.h"

Processor::Processor() {
    cycles = 0;
}

Processor::~Processor() {
}

void Processor::forwardCycle() {
    for (auto it = threads.begin(); it != threads.end(); ++it) {
        auto &t = it.value();
        t->forward();
    }
    cycles++;
}
