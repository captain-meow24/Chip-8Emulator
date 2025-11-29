//
// Created by kanishka on 26/11/25.
//
#include<cstdint>
#ifndef PROCESSOR_H
#define PROCESSOR_H



class Processor {
public:
    std::uint8_t registers[16]{};
    std::uint8_t memory[4096]{};
    std::uint16_t pc{};
    std::uint16_t stack[16]{};
    std::uint8_t sp{};
    std::uint8_t delayTimer{};
    std::uint8_t soundTimer{};
    std::uint8_t keypad[16]{};
    std::uint16_t opcode{};
    std::uint32_t video[64*32]{};
    std::uint16_t index{}; // used to store the current address of the sprite
    Processor() {
        memory[513] = 0x66;
        memory[514] = 0x12;
    }



    void fetch();
    void Join_instruction();
    void execute();
};



#endif //PROCESSOR_H
