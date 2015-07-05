#ifndef _LOG_H_
#define _LOG_H_
#include <string>
#include "mutex_lock.h"
using namespace std;

typedef enum LL{
    L_DEBUG,
    L_INFO,
    L_ERROR,
    L_WARNING
}LogLevel;

#define LOG_FILE_NAME_DFT "cat.log"

// year-mon-day hour-min-sec[DEBUG][business.cpp:1234]:helloworld.
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
        if(RawLog()) RawLog()->WriteLog(L_DEBUG, "[%s:%u]:" fmt, __FILE__, __LINE__, ##args); \
    }while(0)
    
#define LogInfo(fmt, args...) \
    do { \
        if(RawLog()) RawLog()->WriteLog(L_INFO, "[%s:%u]:" fmt, __FILE__, __LINE__, ##args); \
    }while(0)

#define LogError(fmt, args...) \
    do { \
        if(RawLog()) RawLog()->WriteLog(L_ERROR, "[%s:%u]:" fmt, __FILE__, __LINE__, ##args); \
    }while(0)

#define LogWarning(fmt, args...) \
    do { \
        if(RawLog()) RawLog()->WriteLog(L_WARNING, "[%s:%u]:" fmt, __FILE__, __LINE__, ##args); \
    }while(0)  

#endif

