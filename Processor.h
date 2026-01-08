//
// Created by kanishka on 26/11/25.
//

#ifndef PROCESSOR_H
#define PROCESSOR_H
#include <map>
#include<cstdint>
#include <X11/Xlib.h>

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

    void fetch();
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
    void fx15();
    void fx18();
    void fx1e();
    void fx29();
    void fx33();
    void fx55();
    void fx65();

    Processor() {
        pc = 0x200;

        uint8_t fontset[80] = {
            0xF0,0x90,0x90,0x90,0xF0, // 0
            0x20,0x60,0x20,0x20,0x70, // 1
            0xF0,0x10,0xF0,0x80,0xF0, // 2
            0xF0,0x10,0xF0,0x10,0xF0, // 3
            0x90,0x90,0xF0,0x10,0x10, // 4
            0xF0,0x80,0xF0,0x10,0xF0, // 5
            0xF0,0x80,0xF0,0x90,0xF0, // 6
            0xF0,0x10,0x20,0x40,0x40, // 7
            0xF0,0x90,0xF0,0x90,0xF0, // 8
            0xF0,0x90,0xF0,0x10,0xF0, // 9
            0xF0,0x90,0xF0,0x90,0x90, // A
            0xE0,0x90,0xE0,0x90,0xE0, // B
            0xF0,0x80,0x80,0x80,0xF0, // C
            0xE0,0x90,0x90,0x90,0xE0, // D
            0xF0,0x80,0xF0,0x80,0xF0, // E
            0xF0,0x80,0xF0,0x80,0x80  // F
        };

        for (int i = 0; i < 80; i++) {
            memory[i] = fontset[i];
        }
        // ===== PROGRAM @ 0x200 =====
        memory[0x200] = 0x00; memory[0x201] = 0xE0; // CLS

        memory[0x202] = 0xA2; memory[0x203] = 0x2A; // I = 0x22A
        memory[0x204] = 0x60; memory[0x205] = 0x08; // V0 = 8  (X)
        memory[0x206] = 0x61; memory[0x207] = 0x08; // V1 = 8  (Y)
        memory[0x208] = 0xD0; memory[0x209] = 0x1F; // draw I (15 bytes)

        memory[0x20A] = 0x70; memory[0x20B] = 0x10; // V0 += 16

        memory[0x20C] = 0xA2; memory[0x20D] = 0x39; // I = 0x239
        memory[0x20E] = 0xD0; memory[0x20F] = 0x1F; // draw B

        memory[0x210] = 0x70; memory[0x211] = 0x10; // V0 += 16

        memory[0x212] = 0xA2; memory[0x213] = 0x48; // I = 0x248
        memory[0x214] = 0xD0; memory[0x215] = 0x1F; // draw M

        memory[0x216] = 0x12; memory[0x217] = 0x16; // jump to itself (halt)

        uint8_t I_sprite[15] = {
            0xFF,
            0x18,
            0x18,
            0x18,
            0x18,
            0x18,
            0x18,
            0x18,
            0x18,
            0x18,
            0x18,
            0x18,
            0x18,
            0x18,
            0xFF
        };

        for (int i = 0; i < 15; i++)
            memory[0x22A + i] = I_sprite[i];

        uint8_t B_sprite[15] = {
            0xFE,
            0x63,
            0x63,
            0x63,
            0x7E,
            0x63,
            0x63,
            0x63,
            0x63,
            0x63,
            0x63,
            0x63,
            0x63,
            0x63,
            0xFE
        };

        for (int i = 0; i < 15; i++)
            memory[0x239 + i] = B_sprite[i];

        uint8_t M_sprite[15] = {
            0xC3,
            0xE7,
            0xFF,
            0xDB,
            0xC3,
            0xC3,
            0xC3,
            0xC3,
            0xC3,
            0xC3,
            0xC3,
            0xC3,
            0xC3,
            0xC3,
            0xC3
        };

        for (int i = 0; i < 15; i++)
            memory[0x248 + i] = M_sprite[i];





        pc = 0x200;
    }



};

#endif //PROCESSOR_H