INC_DIR:= ./inc/server/ ./inc/server/net/ ./inc/server/threadpool/ ./inc/server/timer/ ./inc/server/cache/ ./inc/server/log/
SRC_DIR:= ./src/server/ ./src/server/net/ ./src/server/threadpool/ ./src/server/timer/ ./src/server/cache/ ./src/server/log/
SRCS:= $(wildcard ./src/server/*.cpp) $(wildcard ./src/server/net/*.cpp) $(wildcard ./src/server/threadpool/*.cpp) $(wildcard ./src/server/log/*.cpp) $(wildcard ./src/server/cache/*.cpp) $(wildcard ./src/server/timer/*.cpp)
OBJS:= $(patsubst %.cpp, %.o, $(SRCS))
LIBS:= -lpthread -llog4cpp

CXX:=g++

CXXFLAGS:= -w -g -std=c++11 $(addprefix -I, $(INC_DIR)) $(LIBS) -Wno-deprecated

EXE:=./bin/server.exe

$(EXE):$(OBJS)
	$(CXX) -o $(EXE) $(OBJS) $(CXXFLAGS)

clean:
	rm -rf $(EXE)
	rm -rf $(OBJS)
