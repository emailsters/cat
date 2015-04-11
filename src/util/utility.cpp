#include "utility.h"
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <list>

using namespace std;
#define CMD_RETURN_STR_LENGTH 128

static char cmd_ret_line_buf[CMD_RETURN_STR_LENGTH];
static int ParseCmdRet(int fd, list<string>& ret);

namespace cat{

int System(const string& cmd, list<string>& ret){
    pid_t pid;
    int fds[2];
    if(-1 == pipe(fds)){
        return -1;
    }
    pid = fork();
    if(pid < 0){
        return -1;
    }else if(pid == 0){
        close(fds[0]);
        
        // redirect command result to fds[1]
        dup2(fds[1], STDOUT_FILENO);

        // need to close all files in child
        struct rlimit rlim;
        if(-1 == getrlimit(RLIMIT_NOFILE, &rlim)) exit(1);
        for(int i = 2; i < rlim.rlim_max; ++i){
            close(i);
        }
        
        execl("/bin/sh", "sh", "-c", cmd.c_str(), NULL);
        exit(1);
    }else{
        close(fds[1]);
        int status = 0;
        waitpid(pid, &status, 0);

        // errors in child
        if(status != 0) return -1;
        if(-1 == ParseCmdRet(fds[0], ret)) return -1;
    };
    return 0;
}
};

int ParseCmdRet(int fd, list<string>& ret){
    if(fd < 0) return -1;
    FILE* fp = fdopen(fd, "r");
    if(!fp) return -1;
    (void)memset(cmd_ret_line_buf, 0, CMD_RETURN_STR_LENGTH);
    while(NULL != fgets(cmd_ret_line_buf, CMD_RETURN_STR_LENGTH -1, fp)){
        ret.push_back(cmd_ret_line_buf);
        (void)memset(cmd_ret_line_buf, 0, CMD_RETURN_STR_LENGTH);
    }
    fclose(fp);
    return 0;
}

