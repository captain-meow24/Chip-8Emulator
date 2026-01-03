//
// Created by kanishka on 26/11/25.
//

#ifndef PROCESSOR_H
#define PROCESSOR_H

#include<cstdint>

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
    //std::uint32_t video[64*32]{};
    std::uint16_t index{}; //stores the current address of the sprite
    std:: uint8_t screen[64*32]{};
    std::uint16_t current_instruction;

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
    void dyxn();


};

#endif //PROCESSOR_H