INC_DIR:= ./inc/ ./inc/net/ ./inc/threadpool/ ./inc/log/
SRC_DIR:= ./src/ ./src/net/ ./src/threadpool/ ./src/log/
SRCS:= $(wildcard ./src/*.cpp) $(wildcard ./src/net/*.cpp) $(wildcard ./src/threadpool/*.cpp) $(wildcard ./src/log/*.cpp)  
OBJS:= $(patsubst %.cpp, %.o, $(SRCS))
LIBS:= -lpthread -llog4cpp -ljson

CXX:=g++

CXXFLAGS:= -w -g -std=c++11 $(addprefix -I, $(INC_DIR)) $(LIBS) -Wno-deprecated

EXE:=./bin/server

$(EXE):$(OBJS)
	$(CXX) -o $(EXE) $(OBJS) $(CXXFLAGS)

clean:
	rm -rf $(EXE)
	rm -rf $(OBJS)
