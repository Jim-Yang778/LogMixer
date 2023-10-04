#include "LogMixer.h"
#include <iostream>
#include <fstream>

const std::string COMBINED_LOG = "combinedLog.txt";

LogMixer::LogMixer(std::string &logName1, std::string &logName2) {
    bool ret = true;
    ret &= readLogFile(logName1, logFile_1);
    ret &= readLogFile(logName2, logFile_2);
    resLogFile.open(COMBINED_LOG, std::ios::in | std::ios::out);
    if (!resLogFile.is_open()) {
        std::cerr << "#ERROR# UNABLE TO OPEN FILE #" << COMBINED_LOG << "#" << std::endl;
        ret &= false;
    }
    if (!ret) assert("Failed to initialize logMixer/n");
}

void LogMixer::startMix() {
    bool flag1 = true;
    bool flag2 = true;

    std::string logStr1;
    std::string logStr2;
    std::getline(logFile_1, logStr1);
    std::getline(logFile_2, logStr2);

    flag1 = logStr1.length() != 0;
    flag2 = logStr2.length() != 0;
    // keep processing if there is a log read by any of file.
    while (!flag1 && !flag2) {
        if (flag1 && flag2) {
            compareAndInsertLog(logStr1, logStr2, flag1, flag2);
        } else if (flag1 && !flag2) {
            insertLog(logStr1);
        } else if (!flag1 && flag2) {
            insertLog(logStr2);
        }
    }
}

bool LogMixer::readLogFile(std::string &logName, std::ifstream &logFile) {
    if (!logName.find(".txt")) {
        if (!std::rename(logName.c_str(), (logName.append(".txt")).c_str())) {
            std::cerr << "#ERROR# UNABLE TO RENAME THIS FILE #####" << std::endl;
            return false;
        }
    }
    logFile.open(logName, std::ios::in);
    if (!logFile.is_open()) {
        std::cerr << "#ERROR# UNABLE TO OPEN THIS FILE #####" << std::endl;
        return false;
    }
    return true;
}

void LogMixer::insertLog(std::string &log) {
    resLogFile << log;
}

void LogMixer::compareAndInsertLog(std::string &log1, std::string &log2,
                                   bool &flag1, bool &flag2) {
    std::istringstream iLogStr1(log1);
    std::istringstream iLogStr2(log2);
    std::string tts1;
    std::string tts2;
    for (int i = 0; i < 3; ++i) {
        getline(iLogStr1, tts1, " ");
        getline(iLogStr2, tts2, " ");
    }
    auto time1 = std::make_shared(tts1);
    auto time2 = std::make_shared(tts2);
    if ()
    return;
}