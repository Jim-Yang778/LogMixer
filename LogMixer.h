class LogMixer {
public:
    class Time {
    Time (std::string tts) {
        while (getline(iLogStr1, tts1, ":")) {
            
        }
    }
    public:
        uint32_t hour;
        uint32_t minute;
        uint32_t second;
        uint64_t micro_second;
    };
public:
    LogMixer() {};
    LogMixer(std::string logName1, std::string logName2);
    virtual ~LogMixer() {
        logFile_1.close();
        logFile_2.close();
        resLogFile.close();
    }
    void startMix();
private:
    void readLogFile(std::ifstream &logFile);
    void compareAndInsertLog(std::string &log1, std::string &log2, bool &flag1, bool &flag2);
    void LogMixer::insertLog(std::string &log);
private:
    std::ifstream logFile_1;
    std::ifstream logFile_2;
    std::ofstream resLogFile;
};