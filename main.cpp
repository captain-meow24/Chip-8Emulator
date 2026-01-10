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

    while (true) {
        processor.fetch();
        processor.decode();
    }
    return 0;
}