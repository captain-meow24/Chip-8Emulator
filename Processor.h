//
// Created by kanishka on 26/11/25.
//

#ifndef PROCESSOR_H
#define PROCESSOR_H
#include <map>
#include<cstdint>
#include "display.h"

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
    //CHIP-8        Keyboard
    //1 2 3 C       1 2 3 4
    //4 5 6 D   →   Q W E R
    //7 8 9 E       A S D F
    //A 0 B F       Z X C V

    std::map<char, uint8_t> keymap = {
        {'1', 0x1}, {'2', 0x2}, {'3', 0x3}, {'4', 0xC},
        {'q', 0x4}, {'w', 0x5}, {'e', 0x6}, {'r', 0xD},
        {'a', 0x7}, {'s', 0x8}, {'d', 0x9}, {'f', 0xE},
        {'z', 0xA}, {'x', 0x0}, {'c', 0xB}, {'v', 0xF}
    };


    std::uint16_t opcode{};
    //std::uint32_t video[64*32]{};
    std::uint16_t index{}; //stores the current address of the sprite
    std:: uint8_t screen[64*32]{};
    std::uint16_t current_instruction;
    display disp;

    uint16_t fetch();
    void decode();
    void call_function();
    void compare_skip();
    void skip_compare();
    void skip_reg_equal();
    void set_reg_val();
    void add_to_reg();
    void set_reg_x_as_y();
    void or_register();
    void and_reg();
    void xor_reg();
    void add_reg_carry();
    void i_8xy5();
    void i_8xy6();
    void i_8xy7();
    void i_8xyE();
    void i_9xy0();
    void Annn();
    void Bnnn();
    void cxkk();
    //void display(uint8_t screen[]);
    void dxyn();
    void ex9e();
    void exa1();
    void fx07();
    void fx0a();

};

#endif //PROCESSOR_H