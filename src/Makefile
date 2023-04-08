CXX ?= g++
CXXFLAGS ?= -std=c++20
CPPFLAGS ?= -O3 -Wall -I. -Wno-conversion-null -Wno-deprecated-declarations

SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)
HEADERS = $(wildcard *.hpp)

EXEC_SRCS = $(filter main%.cpp,$(SRCS))
EXEC_OBJS = $(EXEC_SRCS:.cpp=.o)
EXEC = $(EXEC_SRCS:.cpp=)

CPPFLAGS += -I ./include
LDFLAGS += -L ./lib -Wl,-rpath=./lib
LDLIBS += # -l

.PHONY = all clean distclean test run
.DEFAULT_GOAL = all

all: $(EXEC) 

$(EXEC): $(EXEC_OBJS)
	@for file in $(EXEC); \
	do \
	  $(CXX) $(CXXFLAGS) $(LDFLAGS) $(LDLIBS) $${file}.o -o $${file}; \
	done

$(EXEC_OBJ): $(EXEC_SRCS) $(HEADERS)

clean:
	$(RM) $(OBJS)

distclean:
	$(MAKE) clean
	$(RM) $(EXEC)
	$(RM) *~
