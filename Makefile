
## TDM number
TDM_NUMBER := 08

MODULE = xml
TEST_NAME := tree xml

SHELL := bash

##
## HELP
##
.PHONY : help

help : 
	@echo "Available:"
	@echo "- K => compilation (should not produce any error nor warning)"
	@for N in $(TEST_NAME) ; do echo "- t_$$N => make test with ./test_$$N" ; echo "- m_$$N => valgrind on ./test_$$N" ; done
	@echo "- T    => all test on output"
	@echo "- M    => all test on memory"
	@echo "- pack => produce the tgz archive"

##
## COMPILATION
##  automatic of  C++ ansi (98) => .hpp .cpp files
##
.PHONY : K

# Compiler
CCPP := g++

# Compilation options 
CPP_FLAG_OFF_UNUSED := -Wno-unused-variable -Wno-unused-parameter
CPP_FLAGS := -std=c++98 -Wall -Wextra -pedantic -ggdb $(CPP_FLAG_OFF_UNUSED)

#
# COMPILATION RULES
#

# remove implicit rules
%.o : %.c
%.o : %.cpp
% : %.c
% : %.cpp


# actual rules
%.o : %.cpp $(wildcard *.hpp) $(MAKEFILE_LIST)
	$(CCPP) -c $(CPP_FLAGS) -o $@ $<

test_% : test_%.cpp $(wildcard *.hpp) $(MODULE:%=%.o) $(MAKEFILE_LIST)
	$(CCPP) $(CPP_FLAGS) -o $@ $(MODULE:%=%.o) $<

% : %.cpp $(wildcard *.hpp) $(MODULE:%=%.o) $(MAKEFILE_LIST)
	$(CCPP) $(CPP_FLAGS) -o $@ $(MODULE:%=%.o) $<


# compile all
K : $(TEST_NAME:%=test_%)


##
## TEST
##
.PHONY :  T M#


VALGRIND := valgrind --leak-check=full --show-leak-kinds=all >/dev/null

OUTPUT_SUFFIX := _out.txt
OUTPUT_EXPECTED_SUFFIX := _out_expected.txt

t_% : test_%
	./test_$* > test_$*$(OUTPUT_SUFFIX)
	diff -s -Z test_$*$(OUTPUT_SUFFIX) test_$*$(OUTPUT_EXPECTED_SUFFIX)


## ERROR:     still reachable: 72,704 bytes in 1 blocks
## comes from std
m_% : test_%
	$(VALGRIND) ./test_$* > /dev/null

T : $(TEST_NAME:%=t_%)

M : $(TEST_NAME:%=m_%)



##
## CLEAN
##
.PHONY : clean


clean:
	rm -f *.o $(TEST_NAME:%=test_%) $(TEST_NAME:%=test_%$(OUTPUT_SUFFIX))


##
## PRODUCE THE ARCHIVE (to upload on Celene)
## 
.PHONY : pack


#
# Pour faire l'archive de remise
#
TGZ_FILES :=  *.cpp *.hpp ?akefile cr.pdf
TDM_DIR := TDM_$(TDM_NUMBER)

pack :
	[ -e cr.pdf ] || echo > cr.pdf
	cd .. ; tar czf $(TDM_DIR)/$(TDM_DIR).tgz $(TGZ_FILES:%=$(TDM_DIR)/%)


