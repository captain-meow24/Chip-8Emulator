//
// Created by kanishka on 30/12/25.
//

#ifndef DISPLAY_H
#define DISPLAY_H

#include "tigr.h"
#include<cstdint>


class display {
public:
    Tigr* window;
    display(){
    window = tigrWindow(64, 32, "Chip-8",0);
        tigrClear(window, tigrRGB(244, 194, 194));
        tigrUpdate(window);

        }
    void draw(Tigr* window, uint8_t* screen);
    ~display() {
        tigrFree(window);
    }

};


#endif //DISPLAY_H
