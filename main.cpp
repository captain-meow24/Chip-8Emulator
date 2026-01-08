#include <cstdint>
#include <cstdlib>
#include<ctime>
#include "Processor.h"
#include "tigr.h"
#include "display.h"

int main() {
    std::srand(std::time(nullptr));
    Processor processor;
    while (true) {
        processor.fetch();
        processor.decode();
    }
    return 0;
}