INC_DIR:= .
SRC_DIR:= ./
SRCS:= $(wildcard ./*.cpp)
OBJS:= $(patsubst %.cpp, %.o, $(SRCS))
LIBS:= -lpthread

CXX:=g++

CXXFLAGS:= -w -g -std=c++11 $(addprefix -I, $(INC_DIR)) $(LIBS) -Wno-deprecated

EXE:=../../bin/client.exe

$(EXE):$(OBJS)
	$(CXX) -o $(EXE) $(SRCS) $(CXXFLAGS)
#$(SRC_DIR)/%.o:$(SRC_DIR)/%.cc
	#$(CXX)  -cpp $^ -o $@ $(CXXFLAGS)

clean:
	rm -rf $(EXE)
	rm -rf $(OBJS)
