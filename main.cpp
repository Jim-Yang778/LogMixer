#include <iostream>
#include "LogMixer.h"

int main() {
    std::cout << "##### Read the first file #####" << std::endl;
    std::string logName_1;
    std::cin >> logName_1;
    std::cout << "##### Read the second file #####" << std::endl;
    std::string logName_2;
    std::cin >> logName_2;
    std::shared_ptr<LogMixer> mixer = std::make_shared<LogMixer>(logName_1, logName_2);

    mixer->startMix();

    return 0;
}
