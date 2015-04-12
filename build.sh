#! /bin/sh

CURRENT_PATH=$PWD
SRC_PATH=$CURRENT_PATH/src
EXAMPLE_PATH=$CURRENT_PATH/examples


build(){
    cd $SRC_PATH/base
    make || exit 1
    cd $SRC_PATH/util
    make || exit 1
    cd $SRC_PATH/log
    make || exit 1
    cd $SRC_PATH/memory
    make || exit 1
    cd $SRC_PATH/thread
    make || exit 1

    cd $EXAMPLE_PATH || exit 1
    make -f Makefile.test_condition || exit 1
    make -f Makefile.test_mem_list || exit 1
    make -f Makefile.test_memory_manager || exit 1
    make -f Makefile.test_thread || exit 1
    make -f Makefile.test_thread_pool || exit 1
}

clean(){
    cd $SRC_PATH/base
    make clean || exit 1
    
    cd $SRC_PATH/util
    make clean || exit 1
    
    cd $SRC_PATH/log
    make clean || exit 1

    cd $SRC_PATH/memory
    make clean || exit 1

    cd $SRC_PATH/thread
    make clean || exit 1

    cd $EXAMPLE_PATH || exit 1
    make -f Makefile.test_condition clean || exit 1
    make -f Makefile.test_mem_list clean || exit 1
    make -f Makefile.test_memory_manager clean || exit 1
    make -f Makefile.test_thread clean || exit 1
    make -f Makefile.test_thread_pool clean || exit 1
    cd $CURRENT_PATH
}

if [ $1 = "-b" ]
then
    build
    exit 0
elif [ $1 = "-c" ]
then
    clean
    exit 0
else
    echo "parameter not right"
    exit 1
fi
