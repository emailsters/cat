#ifndef _LOG_H_
#define _LOG_H_
#include <string>
#include "mutex_lock.h"
using namespace std;

typedef enum LL{
    L_DEBUG,
    L_INFO,
    L_ERROR
}LogLevel;

#define LOG_FILE_NAME_DFT "cat.log"

// year-mon-day hour-min-sec(DEBUG):helloworld.
class Log{
public:
    Log(string filename = LOG_FILE_NAME_DFT);
    virtual ~Log();
    
    int Init();    
    int WriteLog(LogLevel level, const char *fmt, ...);
private:
    Log(const Log& other);
    Log& operator=(const Log& other);
    
    int WriteLog(char * log_info);
    int SetTimeStr();
    int SetLogLevelStr(LogLevel level);
    int FileSize();
    void CompressLogFile();
private:
    FILE* _fp;
    string _filename;
    MutexLock _mutex;
};

void LogInit();
void LogInit(const string& filename);
Log* RawLog();
void LogFini();

#define LogDebug(fmt, args...) \
    do { \
        if(RawLog()) RawLog()->WriteLog(L_DEBUG, fmt, #args); \
    }while(0)
    
#define LogInfo(fmt, args...) \
    do { \
        if(RawLog()) RawLog()->WriteLog(L_INFO, fmt, #args); \
    }while(0)

#define LogError(fmt, args...) \
    do { \
        if(RawLog()) RawLog()->WriteLog(L_ERROR, fmt, #args); \
    }while(0)   

#endif

