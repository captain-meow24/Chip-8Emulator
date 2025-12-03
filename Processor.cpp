//
// Created by kanishka on 26/11/25.
//
#include<cstdint>
#include "Processor.h"

void Processor::fetch() {
    uint16_t current_instruction = memory[pc] << 8;
    current_instruction = current_instruction | memory[pc+1];
    decode(current_instruction);
}

void Processor::decode(uint16_t current_instruction){
    uint16_t first_nibble = current_instruction >> 12;
    switch (first_nibble) {
        case 0x0:
            switch (current_instruction){
            case 0x00E0:
                    //clear the display
                    break;
            case 0x00EE:
                    pc = stack[sp];
                    sp=sp-1;
                    //returns from a function
                    break;
                 }
        case 1:
            //jump to address nnn
        {
            uint16_t address = current_instruction & 0x0FFF;
            pc = address;
            break;
        }
        case 2:
            //calls a function, increments the stack pointer, puts the PC on the top of the stack, PC isset to nnn.
            call_function(current_instruction);
            break;
        case 3:
            //compare and skip
            compare_skip(current_instruction);
                break;
        case 4:
            //compare and skip if Vx isn't equal to nn
            skip_compare(current_instruction);
            break;
        case 5:
            //compare registers and if they're equal, skip next instructions
            skip_reg_equal(current_instruction);
            break;
        case 6:
            //sets value of a register
            set_reg_val(current_instruction);
            break;
        case 7:
            add_to_reg(current_instruction);
            break;
    }
}

void Processor::call_function(uint16_t current_instruction) {
    uint16_t address = current_instruction & 0x0FFF;
    sp++;
    stack[sp] = pc;
    pc=address;
}

void Processor::compare_skip(uint16_t current_instruction) {
    uint16_t reg = current_instruction & 0x0F00;
    uint16_t value= current_instruction & 0x00FF;
    if (registers[reg]==value) {
        pc=pc+2;
    }
}
    void Processor::skip_compare(uint16_t current_instruction){
        uint16_t reg = current_instruction & 0x0F00;
        uint16_t value= current_instruction & 0x00FF;
        if (registers[reg]!=value) {
            pc=pc+2;
    }
}
void Processor::skip_reg_equal(uint16_t current_instruction) {
    uint16_t reg1 = current_instruction & 0x0F00;
    uint16_t reg2 = current_instruction & 0x00F0;
    if (registers[reg1] == registers[reg2]) {
        pc=pc+2;
    }

}
void Processor::set_reg_val(uint16_t current_instruction) {
    uint16_t reg = current_instruction & 0x0F00;
    uint16_t val = current_instruction & 0x00FF;
   registers[reg] = val;
}
void Processor::add_to_reg(uint16_t current_instruction) {
    uint16_t reg = current_instruction & 0x0F00;
    uint16_t val = current_instruction & 0x00FF;
    registers[reg] = registers[reg] + val;
}
void Processor::set_reg_x_as_y(uint16_t current_instruction) {
    //Stores the value of register Vy in register Vx
    uint16_t reg1 = current_instruction & 0x0F00;
    uint16_t reg2 = current_instruction & 0x00F0;
    registers[reg1] = registers[reg2];
}
void Processor::or_register(uint16_t current_instruction) {
    //Performs a bitwise OR on the values of Vx and Vy, then stores the result in Vx.
    uint16_t reg1 = current_instruction & 0x0F00;
    uint16_t reg2 = current_instruction & 0x00F0;
    registers[reg1] = registers[reg1] | registers[reg2];
}
void Processor::and_reg(uint16_t current_instruction) {
    //Performs a bitwise AND on the values of Vx and Vy, then stores the result in Vx
    uint16_t reg1 = current_instruction & 0x0F00;
    uint16_t reg2 = current_instruction & 0x00F0;
    registers[reg1] = registers[reg1] & registers[reg2];
}
void Processor::xor_reg(uint16_t current_instruction) {
    uint16_t reg1 = current_instruction & 0x0F00;
    uint16_t reg2 = current_instruction & 0x00F0;
    registers[reg1] = registers[reg1] ^ registers[reg2];
}



