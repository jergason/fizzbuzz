SUPPRESIONS=./passoff/coll.supp
PASSOFF_DIR=./passoff
STUDENT_DIR = .

CC	= g++
CFLAGS	= -I./ -Wall -Winit-self -Wmissing-include-dirs -Wextra -Wfloat-equal -c -ggdb
LFLAGS	= -o 
LIB = -lboost_program_options -lboost_filesystem -lboost_iostreams

TESTR_BIN	= $(STUDENT_DIR)/test_runner
TESTR_SRC	= $(PASSOFF_DIR)/test_runner.cpp $(PASSOFF_DIR)/test_ll.cpp $(PASSOFF_DIR)/test_bst.cpp
TESTR_OBJ	= $(foreach obj, $(TESTR_SRC:.cpp=.o), $(addprefix $(STUDENT_DIR)/,$(shell basename $(obj))))

STUDENT_SRC = $(STUDENT_DIR)/LinkedList.cpp $(STUDENT_DIR)/BST.cpp
STUDENT_OBJ = $(STUDENT_SRC:.cpp=.o)

all: help

help:
	@ echo -e "Accepted Targets"
	@ echo -e "\tpart1 - Test with no memory check, auto-cleans"
	@ echo -e "\tpart2 - Test with memory check, auto-cleans"
	@ echo -e ""
	@ echo -e "\tnomem - Test with no memory check"
	@ echo -e "\tmem - Test with memory check"
	@ echo -e "\tdebug - Run the test with gdb"
	@ echo -e "\t$(TESTR_BIN) - Compile the executable"
	@ echo -e "\tclean - Clean the build"

part1: nomem clean

part2: mem clean

mem: $(TESTR_BIN)
	- time valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --suppressions=$(SUPPRESIONS) $(TESTR_BIN)
	

nomem: $(TESTR_BIN)
	- time $(TESTR_BIN)

debug: $(TESTR_BIN)
	gdb $(TESTR_BIN)
	

clean:
	rm -f $(TESTR_BIN)
	rm -f $(STUDENT_OBJ)
	rm -f $(TESTR_OBJ)

$(TESTR_BIN): $(TESTR_OBJ) $(STUDENT_OBJ)
	$(CC) $(TESTR_OBJ) $(STUDENT_OBJ) $(LIB) $(LFLAGS) $(TESTR_BIN)

#Makefile Debugging
#Target to print any variable, can be added to the dependencies of any other target
#Userfule flags for make, -d, -p, -n
print-%: ; @$(error $* is $($*) ($(value $*)) (from $(origin $*)))

#Support
%.o: $(PASSOFF_DIR)/%.cpp
	$(CC) $(CFLAGS) $< $(LFLAGS) $@

%.o: %.cpp
	$(CC) $(CFLAGS) $< $(LFLAGS) $@

# DO NOT DELETE THIS LINE --
