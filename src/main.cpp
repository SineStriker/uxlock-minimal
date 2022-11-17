#include <QCoreApplication>

#include <QCommandLineOption>
#include <QCommandLineParser>

#include "core/System.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    a.setApplicationName("locksim");
    a.setApplicationVersion("0.0.1");

    // Parse commands
    QCommandLineParser parser;
    parser.setApplicationDescription("Test helper");
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption cpuOption("cpu", "Number of cpu cores");
    QCommandLineOption threadOption("n", "Number of cpu threads");
    QCommandLineOption csOption("cs", "Critical section length");
    QCommandLineOption delayOption(QStringList{"delay", "d"}, "Delay");
    QCommandLineOption totalOption(QStringList{"total", "t"}, "Total cycles");
    QCommandLineOption schedOption(QStringList{"sched", "s"}, "Schedule strategy id");

    parser.addOption(cpuOption);
    parser.addOption(threadOption);
    parser.addOption(csOption);
    parser.addOption(delayOption);
    parser.addOption(totalOption);
    parser.addOption(schedOption);

    parser.process(a);

    // Main codes
    System sys;
    sys.nr_cpus = parser.isSet(cpuOption) ? parser.value("cpu").toInt() : 8;
    sys.nr_threads = parser.isSet(threadOption) ? parser.value("n").toInt() : 16;
    sys.cs_len = parser.isSet(csOption) ? parser.value("cs").toInt() : 128;
    sys.delay = parser.isSet(delayOption) ? parser.value("d").toInt() : 100;
    sys.tot = parser.isSet(totalOption) ? parser.value("t").toInt() : 6000;
    sys.sched_id = parser.isSet(delayOption) ? parser.value("s").toInt() : 1;

    sys.run();

    return 0;
}
