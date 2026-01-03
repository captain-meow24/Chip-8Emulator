//
// Created by kanishka on 30/12/25.
//

#include "display.h"
#include <thread>
#include <chrono>

void display:: draw(Tigr* window, uint8_t* screen) {
        tigrClear(window, tigrRGB(244, 194, 194));

        for (int y = 0; y < 32; y++)
        {
            for (int x = 0; x < 64; x++)
            {
                if (screen[x + y * 64])
                {
                    tigrPlot(window, x, y, tigrRGB(255, 255, 255));
                }
            }
        }

        tigrUpdate(window);
    std::this_thread::sleep_for(std::chrono::milliseconds(16));
}