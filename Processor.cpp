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






    }


}


