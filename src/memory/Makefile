CC = g++
AR = ar
FLAGS = -shared -fPIC -lpthread -L../../bin -lcatbase -lcatlog
INCLUDES = -I../base -I../log
BIN = libcatmemory.so
BIN_PATH = ../../bin

SOURCE = $(wildcard *.cpp)  
OBJS = $(patsubst %.cpp,%.o,$(SOURCE))

$(BIN):$(OBJS)
	$(CC) -o $@ $^ $(FLAGS)
	cp $(BIN) $(BIN_PATH)

$(OBJS):%.o:%.cpp
	$(CC) -g -c $< $(INCLUDES)	
	
.PHONY:clean
clean:
	-rm -f $(OBJS) $(BIN) $(BIN_PATH)/$(BIN)