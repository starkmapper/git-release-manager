CC=clang
CXX=clang++
CPPINCLUDES=lib
CPPFLAGS=-g -Wall -std=c++11 -I $(CPPINCLUDES)
LDFLAGS=-g
LDLIBS=
LIB_SOURCES=lib/FileLineException.cpp  lib/Version.cpp lib/GitVersionRefs.cpp
TEST_SOURCES=test/test.cpp test/VersionTests.cpp test/TestGitVersionRefs.cpp
SOURCES=$(LIB_SOURCES) $(TEST_SOURCES)

LIB_OBJECTS=$(subst .cpp,.o,$(LIB_SOURCES))
TEST_OBJECTS=$(subst .cpp,.o,$(TEST_SOURCES))
OBJECTS=$(LIB_OBJECTS) $(TEST_OBJECTS)

all: test

depend: .depend

.depend: $(SOURCES)
	rm -f ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

test: lib $(TEST_OBJECTS)
	$(CXX) $(LDFLAGS) -o tests $(LIB_OBJECTS) $(TEST_OBJECTS) $(LDLIBS)

lib: $(LIB_OBJECTS)
	
clean:
	rm -f $(OBJECTS)

dist-clean: clean clean-depend
	rm -f tests

clean-depend:
	rm -f ./.depend

include .depend
