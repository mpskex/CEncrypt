#	Standard Makefile Template
#	mpsk
#	2017/07/20

ifeq ($(OS),Windows_NT)
	EXECUTABLE=CEncrypt.exe
else
	EXECUTABLE=CEncrypt.out
endif

SRC_PATH = src/
BIN_PATH = ./

CC = gcc
CXX = g++
CXXFLAGS = -std=c++11  -Wall -g

SRC = ${wildcard $(SRC_PATH)*.cpp}
OBJ = ${patsubst %.cpp, %.o, $(SRC)}

all:$(OBJ)
	$(CXX) $(CXXFLAGS) -o $(BIN_PATH)$(EXECUTABLE) $(OBJ) $(INCFLAGS) $(LDFLAGS) $(LDFLAGS_EXSDLIMG)

$(OBJ):%.o:%.cpp
	$(CXX) $(CXXFLAGS) $(INCFLAGS_CV2) -o $@ -c $<

.PHONY : clean
clean:
	rm -rf $(SRC_PATH)*.o