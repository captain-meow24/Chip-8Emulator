#include <cstdint>
#include <cstdlib>
#include<ctime>
#include "Processor.h"
#include "tigr.h"
#include "display.h"

int main() {
    std::srand(std::time(nullptr));

    Tigr* display = tigrWindow(64, 32, "Chip-8",0);
    while (!tigrClosed(display)) {

        draw(display, screen);

    }

    tigrFree(display);
    return 0;
}