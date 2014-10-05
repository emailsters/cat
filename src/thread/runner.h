#ifndef _RUNNER_H_
#define _RUNNER_H_

class Runner{
public:
    Runner(){}
    
    virtual ~Runner(){}

    virtual void svc() = 0;
};

#endif

