CC=clang
CXX=clang++
CPPINCLUDES=lib
CPPFLAGS=-g -Wall -std=c++11 -I $(CPPINCLUDES)
LDFLAGS=-g
LDLIBS=
LIB_SOURCES=lib/FileLineException.cpp  lib/Version.cpp lib/GitVersionRefs.cpp
LIB_OBJECTS=$(subst .cpp,.o,$(LIB_SOURCES))

TEST_SOURCES=test/test.cpp test/VersionTests.cpp test/TestGitVersionRefs.cpp
TEST_OBJECTS=$(subst .cpp,.o,$(TEST_SOURCES))

HOTFIX_SOURCES=app/git-hotfix.cpp
HOTFIX_OBJECTS=$(subst .cpp,.o,$(HOTFIX_SOURCES))

RELEASE_SOURCES=app/git-release.cpp
RELEASE_OBJECTS=$(subst .cpp,.o,$(RELEASE_SOURCES))

SOURCES=$(LIB_SOURCES) $(TEST_SOURCES) $(HOTFIX_SOURCES) $(RELEASE_SOURCES)
OBJECTS=$(LIB_OBJECTS) $(TEST_OBJECTS) $(HOTFIX_OBJECTS) $(RELEASE_OBJECTS)

all: test git-hotfix git-release

depend: .depend

.depend: $(SOURCES)
	rm -f ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

test: lib $(TEST_OBJECTS)
	$(CXX) $(LDFLAGS) -o tests $(LIB_OBJECTS) $(TEST_OBJECTS) $(LDLIBS)

git-hotfix: lib $(HOTFIX_OBJECTS)
	$(CXX) $(LDFLAGS) -o git-hotfix $(LIB_OBJECTS) $(HOTFIX_OBJECTS) $(LDLIBS)

git-release: lib $(RELEASE_OBJECTS)
	$(CXX) $(LDFLAGS) -o git-release $(LIB_OBJECTS) $(RELEASE_OBJECTS) $(LDLIBS)

lib: $(LIB_OBJECTS)
	
clean:
	rm -f $(OBJECTS)

dist-clean: clean clean-depend clean-doc
	rm -f tests
	rm -f git-hotfix
	rm -f git-release

clean-doc:
	rm -rf doc/

clean-depend:
	rm -f ./.depend

include .depend
