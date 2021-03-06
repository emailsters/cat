#include "log.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <list>
#include "mutex_guard.h"
#include "utility.h"
#include <unistd.h>
using namespace std;

#define LOG_BUF_LEN (1024)

//compress log file while reaches 3M
#define LOG_FILE_LIMIT (3 * 1024 * 1024)

const char* g_LogLevelInfo[] = {
    "DEBUG",
    "INFO",
    "ERROR",
    "WARNING"
};

Log::Log(string filename):_filename(filename), _fp(NULL){}

Log::~Log(){
    MUTEX_GUARD(&_mutex);
    if(_fp){
        fclose(_fp);
        _fp = NULL;
    }
}

int Log::Init(){
    MUTEX_GUARD(&_mutex);
    if(_fp){
        fclose(_fp);
        _fp = NULL;
    }
    if(_filename == "") return -1;
    _fp = fopen(_filename.c_str(), "a+");
    if(!_fp) return -1;
    return 0;
}

#define TIME_STR_LEN sizeof("1900-01-01 00:00:00")
#define TIME_FORMAT "%4d-%02d-%02d %02d:%02d:%02d"
static char g_LogBuf[LOG_BUF_LEN];

int Log::WriteLog(LogLevel level, const char *fmt, ...){
    MUTEX_GUARD(&_mutex);
    (void)memset(g_LogBuf, 0, LOG_BUF_LEN);
    int time_len = SetTimeStr();
    int lev_len = SetLogLevelStr(level);
    va_list arg;
    va_start(arg, fmt);
    vsprintf(g_LogBuf + time_len + lev_len, fmt, arg);
    va_end(arg);
    g_LogBuf[LOG_BUF_LEN - 1] = 0;
    return WriteLog(g_LogBuf);
}

int Log::FileSize(){
    struct stat statbuff;
    if(stat(_filename.c_str(), &statbuff) < 0){  
        return 0;
    }
    return statbuff.st_size;
}

void Log::CompressLogFile(){
    char time_buf[TIME_STR_LEN + 1];
    (void)strncpy(time_buf, g_LogBuf, TIME_STR_LEN - 1);
    
    //replace " " with "_"
    time_buf[10] = '_';
    time_buf[TIME_STR_LEN] = 0;
    string zfile = _filename + ".gz";
    string target_file = _filename + "." + time_buf + ".gz";
    string cmd = "gzip " + _filename + ";mv " + zfile + " " + target_file;
    list<string> result;
    if(-1 == cat::System(cmd, result)){
        //cout<<"compress file failed"<<endl;
    }
}

int Log::SetTimeStr(){
    time_t rawtime;
    struct tm* timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    (void)snprintf(g_LogBuf, TIME_STR_LEN, TIME_FORMAT, 1900+timeinfo->tm_year, 
        1+timeinfo->tm_mon,timeinfo->tm_mday,timeinfo->tm_hour,timeinfo->tm_min,
        timeinfo->tm_sec);
    return TIME_STR_LEN - 1;
}

int Log::SetLogLevelStr(LogLevel level){
    string lev_str = "[";
    switch(level){
    case L_DEBUG:
        lev_str += g_LogLevelInfo[L_DEBUG];
        break;
    case L_INFO:
        lev_str += g_LogLevelInfo[L_INFO];
        break;
    case L_ERROR:
        lev_str += g_LogLevelInfo[L_ERROR];
        break;
    case L_WARNING:
        lev_str += g_LogLevelInfo[L_WARNING];
        break;
    default:
        break;
    }
    lev_str += "]";
    snprintf(g_LogBuf + TIME_STR_LEN - 1, lev_str.size() + 1, "%s", lev_str.c_str());
    return lev_str.size();
}

int Log::WriteLog(char * log_info){
    if(!_fp) return -1;

    //file was deleted when writing, recreate it
    if(0 != access(_filename.c_str(), F_OK)){
        Init();
    }
    
    if(FileSize() >= LOG_FILE_LIMIT){
        CompressLogFile();
        Init();
    }
    fprintf(_fp, "%s\n", g_LogBuf);
    fflush(_fp);
    fsync(fileno(_fp));
    return 0;
}

static Log* g_Log;

//should be called before any threads started
void LogInit(){
    if(g_Log) return;
    g_Log = new Log;
    if(g_Log)
        g_Log->Init();
}

void LogInit(const string& filename){
    if(g_Log) return;
    g_Log = new Log(filename);
    if(g_Log)
        g_Log->Init();
}

Log* RawLog(){
    return g_Log;    
}

void LogFini(){
    if(g_Log){
        delete g_Log;
        g_Log = NULL;
    }
}


