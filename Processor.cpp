//
// Created by kanishka on 26/11/25.
//
#include<cstdint>
#include<cstdlib>
#include<ctime>
#include "Processor.h"

uint16_t Processor::fetch() {
    current_instruction = memory[pc] << 8;
    current_instruction = current_instruction | memory[pc+1];
    pc+=2;
    return current_instruction;
}

void Processor::decode(){
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
        case 0x1:
            //jump to address nnn
        {
            uint16_t address = current_instruction & 0x0FFF;
            pc = address;
            break;
        }
        case 0x2:
            //calls a function, increments the stack pointer, puts the PC on the top of the stack, PC isset to nnn.
            call_function();
            break;
        case 0x3:
            //compare and skip
            compare_skip();
                break;
        case 0x4:
            //compare and skip if Vx isn't equal to nn
            skip_compare();
            break;
        case 0x5:
            //compare registers and if they're equal, skip next instructions
            skip_reg_equal();
            break;
        case 0x6:
            //sets value of a register
            set_reg_val();
            break;
        case 0x7:
            add_to_reg();
            break;
        case 0x8: {
            uint8_t last_nibble = current_instruction & 0x000F;
            switch (last_nibble) {
                case 0x0:
                    set_reg_x_as_y();
                    break;
                case 0x1:
                    or_register();
                    break;
                case 0x2:
                    and_reg();
                    break;
                case 0x3:
                    xor_reg();
                    break;
                case 0x4:
                    add_reg_carry();
                    break;
                case 0x5:
                    i_8xy5();
                    break;
                case 0x6:
                    i_8xy6();
                    break;
                case 0x7:
                    i_8xy7();
                    break;
                case 0xE:
                    i_8xyE();
                    break;
            }
        }
            break;
        case 0x9:
            i_9xy0();
            break;
        case 0xA:
            Annn();
            break;
        case 0xB:
            Bnnn();
            break;
        case 0xC:
            cxkk();
            break;
        case 0xD:
            dxyn();
            break;
        case 0xE: {
            uint16_t last_two = current_instruction & 0x00FF;
            switch (last_two) {
                case 0x9E:
                    ex9e();
                    break;
                case 0xA1:
                    break;
            }
        }
            break;
        case 0xF:
            uint16_t last_two = current_instruction & 0x00FF;
            switch (last_two) {
                case 0x07:
                    break;
                case 0x0A:
                    break;
                case 0x15:
                    break;
                case 0x18:
                    break;
                case 0x1E:
                    break;
                case 0x29:
                    break;
                case 0x33:
                    break;
                case 0x55:
                    break;
                case 0x65:
                    break;
            }

            break;

    }
}

void Processor::call_function() {
    uint16_t address = current_instruction & 0x0FFF;
    sp++;
    stack[sp] = pc;
    pc=address;
}
void Processor::compare_skip() {
    uint8_t reg = (current_instruction & 0x0F00) >> 8;
    uint8_t value= current_instruction & 0x00FF;
    if (registers[reg]==value) {
        pc=pc+2;
    }
}
    void Processor::skip_compare(){
        uint8_t reg = (current_instruction & 0x0F00) >> 8;
        uint8_t value= current_instruction & 0x00FF;
        if (registers[reg]!=value) {
            pc=pc+2;
    }
}
void Processor::skip_reg_equal() {
    uint8_t reg1 = (current_instruction & 0x0F00) >> 8;
    uint8_t reg2 = (current_instruction & 0x00F0) >> 4;
    if (registers[reg1] == registers[reg2]) {
        pc=pc+2;
    }
}
void Processor::set_reg_val() {
    uint8_t reg = (current_instruction & 0x0F00) >> 4;
    uint8_t val = current_instruction & 0x00FF;
   registers[reg] = val;
}
void Processor::add_to_reg() {
    uint8_t reg = (current_instruction & 0x0F00) >> 8;
    uint8_t val = current_instruction & 0x00FF;
    registers[reg] = registers[reg] + val;
}
void Processor::set_reg_x_as_y() {
    //Stores the value of register Vy in register Vx
    uint8_t reg1 = (current_instruction & 0x0F00) >> 8;
    uint8_t reg2 = (current_instruction & 0x00F0) >> 4;
    registers[reg1] = registers[reg2];
}
void Processor::or_register() {
    //Performs a bitwise OR on the values of Vx and Vy, then stores the result in Vx.
    uint8_t reg1 = (current_instruction & 0x0F00) >> 8;
    uint8_t reg2 = (current_instruction & 0x00F0) >> 4;
    registers[reg1] = registers[reg1] | registers[reg2];
}
void Processor::and_reg() {
    //Performs a bitwise AND on the values of Vx and Vy, then stores the result in Vx
    uint8_t reg1 = (current_instruction & 0x0F00) >> 8;
    uint8_t reg2 = (current_instruction & 0x00F0) >> 4;
    registers[reg1] = registers[reg1] & registers[reg2];
}
void Processor::xor_reg() {
    uint8_t reg1 = (current_instruction & 0x0F00) >> 8;
    uint8_t reg2 = (current_instruction & 0x00F0) >> 4;
    registers[reg1] = registers[reg1] ^ registers[reg2];
}
void Processor::add_reg_carry() {
    //The values of Vx and Vy are added together. If the result is greater than 8 bits (i.e., > 255,) VF is set to 1
    uint8_t reg1 = (current_instruction & 0x0F00) >> 8;
    uint8_t reg2 = (current_instruction & 0x00F0) >> 4;
    if ( (registers[reg1] + registers[reg2]) >255) {
        registers[0xF] = 1;
    }
    else {
        registers[0xF] = 0;
    }
    registers[reg1]= registers[reg1] + registers[reg2];
}
void Processor::i_8xy5() {
    uint8_t reg1 = (current_instruction & 0x0F00) >> 8;
    uint8_t reg2 = (current_instruction & 0x00F0) >> 4;
    if (registers[reg1] > registers[reg2]) {
        registers[0xF] = 1;
    }
    else {
        registers[0xF] = 0;
    }
    registers[reg1] = registers[reg1] - registers[reg2];
}
void Processor::i_8xy6() {
    uint8_t reg1 = (current_instruction & 0x0F00) >> 8;
    registers[0xF] = registers[reg1] & 0x1;
    registers[reg1] = registers[reg1] >> 1;
}
void Processor::i_8xy7() {
    uint8_t reg1 = (current_instruction & 0x0F00) >> 8;
    uint8_t reg2 = (current_instruction & 0x00F0) >> 4;
    if (registers[reg1] < registers[reg2]) {
        registers[0xF] = 1;
    }
    else {
        registers[0xF] = 0;
    }
    registers[reg1] = registers[reg2] - registers[reg1];
}
void Processor::i_8xyE() {
    uint8_t reg1 = (current_instruction & 0x0F00) >> 8;
    registers[0xF] = (registers[reg1] & 0b10000000) >> 7;
    registers[reg1] = registers[reg1] << 0x1;
}
void Processor::i_9xy0() {
    uint8_t reg1 = (current_instruction & 0x0F00) >> 8;
    uint8_t reg2 = (current_instruction & 0x00F0) >> 4;
    if (registers[reg1] != registers[reg2]) {
        pc=pc+2;
    }
}
void Processor::Annn() {
    index = current_instruction & 0x0FFF;
}
void Processor::Bnnn() {
    pc = (current_instruction & 0x0FFF) + registers[0x0];
}
void Processor::cxkk() {
    uint8_t randomb = std::rand() % 256;
    uint8_t val = current_instruction & 0x00FF;
    uint8_t reg1 = (current_instruction & 0x0F00) >> 8;
    registers[reg1] = val & randomb;
}
void Processor::dxyn() {
    uint8_t reg1 = (current_instruction & 0x0F00) >> 8;
    uint8_t reg2 = (current_instruction & 0x00F0) >> 4;
    uint8_t n = current_instruction & 0x000F;
    uint8_t x = registers[reg1];
    uint8_t y= registers[reg2];
    uint8_t spr;
    registers[0xF] = 0;
    for (int i=0; i<n; i++) {

        spr = memory[index +i];
        for (int j=0; j<8; j++) {

            uint8_t spritePixel = (spr >> (7 - j)) & 1;
                if(screen[(((y+i)%32)*64) + ((x+j)%64)]==1 && spritePixel==1 ){

                registers[0xF] = 1;
            }

           screen[(((y+i)%32)*64) + ((x+j)%64)] ^= spritePixel;

        }

    }
    disp.draw(disp.window,screen);

}
void Processor::ex9e() {
    uint8_t x = (current_instruction & 0x0F00) >> 8;
    uint8_t key = registers[x] & 0x0F;

    if (keypad[key]) {
        pc += 2;
    }
}
void Processor::exa1() {
    uint8_t x = (current_instruction & 0x0F00) >> 8;
    uint8_t key = registers[x] & 0x0F;
    if (keypad[key]) {
        return;
    }
    pc += 2;
}