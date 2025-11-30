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

void Processor::decode(uint16_t current_instruction) {
    switch (current_instruction){

    }


}


