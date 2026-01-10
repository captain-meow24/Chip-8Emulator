//
// Created by kanishka on 10/1/26.
//

#ifndef FILE_HANDLING_H
#define FILE_HANDLING_H

#include <fstream>
#include <vector>
#include <cstdint>
#include "Processor.h"


class File_handling {
public:
    void reads(std::string path, Processor* processor);
    void writes(std::string path, Processor* processor);
};
#endif //FILE_HANDLING_H
