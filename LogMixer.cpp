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
            insertLog(logStr1, flag1, logFile_1);
        } else if (!flag1 && flag2) {
            insertLog(logStr2, flag2, logFile_2);
        }
    }
    std::cout << COMBINED_LOG << " has been created" << std::endl;
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

void LogMixer::insertLog(std::string &log, bool &flag, std::ifstream &logFile) {
    resLogFile << log;
    std::getline(logFile, log);
    flag = log.length() != 0;
}

void LogMixer::compareAndInsertLog(std::string &log1, std::string &log2,
                                   bool &flag1, bool &flag2) {
    std::istringstream iLogStr1(log1);
    std::istringstream iLogStr2(log2);
    std::string tts1;
    std::string tts2;
    for (int i = 0; i < 3; ++i) {
        getline(iLogStr1, tts1, ' ');
        getline(iLogStr2, tts2, ' ');
    }
    std::shared_ptr<Time> time1 = std::make_shared<Time>(tts1);
    std::shared_ptr<Time> time2 = std::make_shared<Time>(tts2);
    if (Time::compareTime(time1, time2)) {
        insertLog(log2, flag2, logFile_2);
    } else {
        insertLog(log1, flag1, logFile_1);
    }
    return;
}

/*
@Parameter: t1 t2
Two Times that are going to be compared

@Return
true: t1 is later than t2 in time 
      OR
      t1 is the same as t2
false: t2 is later than t1 in time
*/
bool LogMixer::Time::compareTime(std::shared_ptr<Time> &t1, std::shared_ptr<Time> &t2) {
    if (t1->hour > t2->hour) {
        return true;
    } else if (t1->hour < t2->hour) {
        return false;
    }
    if (t1->minute > t2->minute) {
        return true;
    } else if (t1->minute < t2->minute) {
        return false;
    }
    if (t1->second > t2->second) {
        return true;
    } else if (t1->second < t2->second) {
        return false;
    }
    if (t1->micro_second > t2->micro_second) {
        return true;
    } else if (t1->micro_second < t2->micro_second) {
        return false;
    }
    return true;
}