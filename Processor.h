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
    std::uint32_t video[64*32]{};
    std::uint16_t index{}; // used to store the current address of the sprite

    Processor() {
        memory[513] = 0x66;
        memory[514] = 0x12;
    }

    void fetch();
    void decode(uint16_t current_instruction);
    void call_function(uint16_t current_instruction);
    void compare_skip(uint16_t current_instruction);
    void skip_compare(uint16_t current_instruction);
    void skip_reg_equal(uint16_t current_instruction);
    void set_reg_val(uint16_t current_instruction);
    void add_to_reg(uint16_t current_instruction);
    void set_reg_x_as_y(uint16_t current_instruction);
    void or_register(uint16_t current_instruction);
    void and_reg(uint16_t current_instruction);
    void xor_reg(uint16_t current_instruction);
    void add_reg_carry(uint16_t current_instruction);

};



#endif //PROCESSOR_H
