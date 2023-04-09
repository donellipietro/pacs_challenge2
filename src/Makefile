CXX ?= g++
CXXFLAGS ?= -std=c++20
CPPFLAGS ?= -O3 -Wall -I. -Wno-conversion-null -Wno-deprecated-declarations

SRCS = $(wildcard *.cpp)
EXEC_SRCS = $(filter main%.cpp,$(SRCS))

HEADERS = $(wildcard *.hpp)

OBJS = $(SRCS:.cpp=.o)
EXEC_OBJS = $(EXEC_SRCS:.cpp=.o)
DEP_OBJS = $(filter-out $(EXEC_OBJS),$(SRCS:.cpp=.o))

EXEC = $(EXEC_SRCS:.cpp=)

CPPFLAGS += -I ./include -I ${MY_PACS_ROOT}/include
LDFLAGS += -L ./lib -Wl,-rpath=./lib
LDLIBS += # -l

.PHONY = all clean distclean test run
.DEFAULT_GOAL = all

all: $(EXEC)

run: main
	./main

test: main_test
	./main_test

$(EXEC): $(OBJS) $(SRCS) $(HEADERS)
	@echo "Linker.."
	@for file in $(EXEC); \
	do \
	  $(CXX) $(CXXFLAGS) $(LDFLAGS) $(LDLIBS) $(DEP_OBJS) $${file}.o -o $${file}; \
	done

$(OBJS): $(SRCS) $(HEADERS)

clean:
	$(RM) $(OBJS)

distclean:
	$(MAKE) clean
	$(RM) $(EXEC)
	$(RM) *~
