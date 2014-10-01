#include "log.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string>
#include <iostream>

using namespace std;

#define LOG_BUF_LEN 256
string generateLogString(const char *moduleID, const char *buf);

namespace Log{
    void i(const char *mdlName, const char *fmt, ...){
        va_list arg;
        char buf[LOG_BUF_LEN];
        va_start(arg, fmt);
        vsprintf(buf, fmt, arg);
        va_end(arg);         //用fputs和fprintf在memory_list中出现问题，改用cout
        //fputs(buf, stdout);
        //fprintf(stdout, "%s", buf);        cout<<"("<<mdlName<<"):"<<buf<<endl;
    }
}

string generateLogString(const char *moduleID, const char *buf){
    string moduleName(moduleID);
    string fmtString(buf);
    string outputString;
    outputString = "(" + moduleName + "): " + fmtString;
    outputString += "\n\0";
    return outputString;
}



