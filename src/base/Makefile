CC = g++
AR = ar
FLAGS = 
INCLUDES = 
BIN = libcatbase.a
BIN_PATH = ../../bin

SOURCE = $(wildcard *.cpp)  
OBJS = $(patsubst %.cpp,%.o,$(SOURCE))

$(BIN):$(OBJS)
	$(AR) -r $@ $^ $(FLAGS)
	cp $(BIN) $(BIN_PATH)

$(OBJS):%.o:%.cpp
	$(CC) -g -c $< $(INCLUDES)	
	
.PHONY:clean
clean:
	-rm -f $(OBJS) $(BIN) $(BIN_PATH)/$(BIN)