#include <cstdint>
#include <cstdlib>
#include<ctime>
#include "Processor.h"
#include "tigr.h"
#include "display.h"
#include "File_handling.h"

int main() {
    std::srand(std::time(nullptr));
    File_handling fh;
    Processor processor;
    fh.reads("../example/ibm_logo", &processor );
    std::ofstream log("../example/output", std::ios::out | std::ios::trunc);
   // std::ofstream file("../example/output", std::ios::app);
    log<< "Program counter              Registers \n";
    log.close();
    while (true) {
        processor.fetch();
        processor.decode();
        fh.writes("../example/output", &processor);
    }
    return 0;
}