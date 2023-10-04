#include <iostream>
#include <fstream>

void readLogFile(std::ifstream &logFile) {
    std::string LOGFILE;
    std::cin >> LOGFILE;
    if (!LOGFILE.find(".txt")) {
        if (!std::rename(LOGFILE.c_str(), (LOGFILE.append(".txt")).c_str())) {
            std::cerr << "#ERROR# UNABLE TO RENAME THIS FILE #####" << std::endl;
        }
    }
    logFile.open(LOGFILE, std::ios::in);
    if (!logFile.is_open()) {
        std::cerr << "#ERROR# UNABLE TO RENAME THIS FILE #####" << std::endl;
    }
}

int main(int, char**){
    std::cout << "##### Read the first file #####" << std::endl;
    std::ifstream logFile_1;
    readLogFile(logFile_1);
    std::cout << "##### Read the second file #####" << std::endl;
    std::ifstream logFile_2;
    readLogFile(logFile_2);

    std::string str1;
    std::string str2;
    std::getline(logFile_1, str1);
    std::getline(logFile_2, str2);


    std::cout << "##### first file" << str1 << "#####" << std::endl;
    std::cout << "##### second file"<< str2 << "#####" << std::endl;

    


    logFile_1.close();
    logFile_2.close();
    return 0;
}
