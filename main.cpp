#include <iostream>
#include <fstream>
#include "LogMixer.h"

int main(int, char**){
    std::cout << "##### Read the first file #####" << std::endl;
    std::string logName_1;
    std::cin >> logName_1;
    std::cout << "##### Read the second file #####" << std::endl;
    std::string logName_2;
    std::cin >> logName_2;
    auto mixer = std::make_shared<LogMixer>(logName_1, logName_2);

    mixer->startMix();
    
    return 0;
}
