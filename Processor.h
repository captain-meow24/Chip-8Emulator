//
// Created by kanishka on 26/11/25.
//
#include<cstdint>
#ifndef PROCESSOR_H
#define PROCESSOR_H



class Processor {
    std::uint8_t registers[16]{};
    std::uint8_t memory[4096]{};
    std::uint16_t pc;
    std::uint16_t stack[16]{};
    std::uint8_t sp{};
    std::uint8_t delayTimer{};
    std::uint8_t soundTimer{};
    std::uint8_t keypad[16]{};

};



#endif //PROCESSOR_H
