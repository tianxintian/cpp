INC_DIR:= ./inc
SRC_DIR:= ./src
SRCS:= $(wildcard $(SRC_DIR)/*.cpp)
OBJS:= $(patsubst %.cpp, %.o, $(SRCS))
LIBS:= -lboost_regex -lpthread

CXX:=g++
CXXFLAGS:=-w -g -std=c++11 $(addprefix -I,$(INC_DIR)) $(LIBS) -Wno-deprecated
EXE:=./bin/main

$(EXE):$(OBJS)
	$(CXX) -o $(EXE) $(OBJS) $(CXXFLAGS)
clean:
	rm -rf $(EXE)
	rm -rf $(OBJS)

