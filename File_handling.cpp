//
// Created by kanishka on 10/1/26.
//

#include "File_handling.h"

#include <iomanip>
#include <iostream>
#include <sstream>


void File_handling::reads(std::string path, Processor* processor) {
    std::ifstream file(path);
    std::ostringstream content;
    content << file.rdbuf();
    std::string entireFileContents = content.str();
    //std::vector<std::string> arr;
    int j = 0x200;
    int i= 0;
    while ( i < entireFileContents.size()) {
        std::string s = entireFileContents.substr(i, 2);
        int x = std::stoi(s, nullptr, 16);
        processor->memory[j]= x;
        i = i+3;
        j++;
    }
}

void File_handling::writes(std::string path, Processor* processor) {
    std::ofstream file(path, std::ios::app | std::ios::binary);
    if (!file) return;

    file.put(processor->pc >> 8);
    file.put(processor->pc & 0xFF);

    for (int i = 0; i < 16; ++i) {
        file.put(processor->registers[i]);
    }

    file.close();
}



