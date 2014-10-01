#ifndef _LOG_H_
#define _LOG_H_

namespace Log{

/*
#define I(strformat, params) \
    do{ \
        fprintf(stdout, strformat, params); \
    }while(0)
 */   
    void i(const char *mdlName, const char *fmt, ...);
//    void e();
//    void d();
}

#endif

