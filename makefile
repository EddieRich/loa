# CFLAGS is not defined by default
CXXFLAGS = -MMD -Wall -Wextra -Werror -std=c++23 -march=x86-64

SRC=$(wildcard *.cpp)
OBJ=$(SRC:%.cpp=%.o)
DEP=$(OBJ:%.o=%.d)

EXE=loa

.PHONY: clean

debug: CXXFLAGS += -g -Wno-unused-but-set-variable -Wno-unused-parameter
debug: $(EXE)

remake: clean debug
.NOTPARALLEL: remake

release: CXXFLAGS += -Os -s -fno-ident -fno-asynchronous-unwind-tables -faggressive-loop-optimizations
release: clean $(EXE)
.NOTPARALLEL: release

clean:
	$(RM) $(OBJ) $(DEP) $(EXE)

install: release
	sudo cp $(EXE) /usr/local/bin/$(EXE)

$(EXE): $(OBJ)
	g++ -o $@ $^ -l:libraylib.a -lm

-include $(DEP)

