#include <iostream>
#include <sys/resource.h>
#include <fstream>
#include <iomanip>
using namespace std;
// Ausgabe der Ressourcennutzung
void printUsage(const string& titel) {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    cout << "--- " << titel << " ---" << endl;
    cout << "User-Zeit: "
         << usage.ru_utime.tv_sec << "." << setw(6) << setfill('0') << usage.ru_utime.tv_usec << " Sekunden" << endl;
    cout << "System-Zeit: "
         << usage.ru_stime.tv_sec << "." << setw(6) << setfill('0') << usage.ru_stime.tv_usec << " Sekunden" << endl;
    cout << "Maximale Speicherbelegung (RSS): " << usage.ru_maxrss << " KB" << endl << endl;
}


// Funktion zur dynamischen Speicherzuweisung
void funcMem(int n) {
    int* arr = new int[n];
 ofstream file("gnuMem.txt");
   struct rusage usage;
for (int i = 0; i < n; i++) {
        arr[i] = i;
        if (i % 1000 == 0) {
            getrusage(RUSAGE_SELF, &usage);
            file << i << " "
                 << usage.ru_utime.tv_sec * 1000 + usage.ru_utime.tv_usec / 1000 << " "
                 << usage.ru_stime.tv_sec * 1000 + usage.ru_stime.tv_usec / 1000 << "\n";
        }
    }

    file.close();
    printUsage("Nach funcMem");
    delete[] arr;
}

// Rekursive Funktion
void funcRec(int tiefe, int aktuell = 0) {

 static ofstream file("gnuRec.txt");

    if (aktuell % 100 == 0) {
        struct rusage usage;
        getrusage(RUSAGE_SELF, &usage);
        file << aktuell << " "
             << usage.ru_utime.tv_sec * 1000 + usage.ru_utime.tv_usec / 1000 << " "
             << usage.ru_stime.tv_sec * 1000 + usage.ru_stime.tv_usec / 1000 << "\n";
        file << aktuell  << std::setw(2) << std::setfill('0') << usage.ru_utime.tv_sec << "." << std::setw(6) << std::setfill('0') << usage.ru_utime.tv_usec << "  | "
             << std::setw(2) << std::setfill('0') << usage.ru_stime.tv_sec << "." << std::setw(6) << std::setfill('0') << usage.ru_stime.tv_usec
             << std::endl;

    }

    if (aktuell >= tiefe) {
        printUsage("Bei Rekursionstiefe " + to_string(aktuell));
        file.close();
        return;
}
    funcRec(tiefe, aktuell + 1);
}
// Automatischer Heap-Experiment
void heapExperiment() {
    int* arr = nullptr;
    int n = 10000000;
    while (true) {
        try {
            arr = new int[n];
            for (int i = 0; i < 1000; ++i) arr[i] = i;
            delete[] arr;
            cout << "funcMem(" << n << ") erfolgreich" << endl;
            n += 10000000;
        } catch (bad_alloc& e) {
            cout << "Fehler bei funcMem(" << n << "): Speicher erschöpft." << endl;
            break;
        }
    }
    printUsage("Nach automatischem Heap-Test");
}

// Automatischer Stack-Experiment
int maxTiefe = 0;
void testStack(int tiefe = 1) {
    int dummy[100]; // Belastung des Stacks
    dummy[0] = tiefe;
    maxTiefe = tiefe;
    testStack(tiefe + 1);
}

void stackExperiment() {
    try {
        testStack();
    } catch (...) {
        cout << "Maximale Rekursionstiefe erreicht: " << maxTiefe << endl;
    }
    printUsage("Nach automatischem Stack-Test");
}
// Ausgabe der Systemgrenzen (Limits)
void printLimits() {
    struct rlimit lim;
    getrlimit(RLIMIT_STACK, &lim);
    cout << "Stack-Grenze: " << lim.rlim_cur / 1024 << " KB" << endl;
    getrlimit(RLIMIT_DATA, &lim);
    cout << "Heap-Grenze: " << lim.rlim_cur / 1024 << " KB" << endl << endl;
}

int main() {
    printLimits();             // Zeigt aktuelle Systemgrenzen
    funcMem(10000000);         // Versucht 10 Millionen Elemente (40 MB)
    funcRec(1000);             // Versucht 1000 Rekursionsebenen
 // Automatischer Test
    heapExperiment();
    stackExperiment();
   return 0;
}

