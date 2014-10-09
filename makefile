CFLAGS = -std=c++11
TARGET = bin/artificial-life-simulator.o
TEST_TARGET = bin/test.o
SRCDIR = src
TESTDIR = test
LIBDIR = lib
SRCEXT = cpp
BUILDDIR = build
INC = -I include

SOURCES = $(wildcard $(SRCDIR)/*.$(SRCEXT))
OBJECTS = $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
TESTS_SOURCES = $(wildcard $(TESTDIR)/*.$(SRCEXT))
TEST_SOURCES = $(filter-out $(SRCDIR)/main.$(SRCEXT),$(SOURCES))
TEST_OBJECTS = $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(TEST_SOURCES:.$(SRCEXT)=.o))

GTEST_TARGET = $(LIBDIR)/gtest-all.o
GMOCK_TARGET = $(LIBDIR)/gmock-all.o
TEST_LIB = $(LIBDIR)/libgtest.a
GTEST_DIR = $(LIBDIR)/gtest
GMOCK_DIR = $(LIBDIR)/gmock

TEST_SYSTEM_FLAGS = -isystem $(GTEST_DIR)/include -isystem $(GMOCK_DIR)/include
TEST_I_FLAGS = -I $(GTEST_DIR) -I $(GMOCK_DIR)

all: $(BUILDDIR) $(TARGET)

tests: $(BUILDDIR) $(TEST_TARGET)

$(BUILDDIR):
	@mkdir -p bin
	@mkdir -p $(BUILDDIR)

$(TARGET): $(OBJECTS)
	$(CXX) $^ -o $(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	$(CXX) $(CFLAGS) $(INC) -c -o $@ $<

$(TEST_TARGET): $(TEST_LIB) $(TEST_OBJECTS)
	$(CXX) $(CFLAGS) $(TEST_SYSTEM_FLAGS) -pthread  $(TESTS_SOURCES) $(TEST_LIB) $(TEST_OBJECTS) -o $(TEST_TARGET)

$(TEST_LIB): $(GMOCK_TARGET) $(GTEST_TARGET)
	@ar -rv $(TEST_LIB) $(GTEST_TARGET) $(GMOCK_TARGET)

$(GMOCK_TARGET):
	$(CXX) $(TEST_SYSTEM_FLAGS) $(TEST_I_FLAGS) -c lib/gmock/src/gmock-all.cc -o $(GMOCK_TARGET)

$(GTEST_TARGET):
	$(CXX) $(TEST_SYSTEM_FLAGS) $(TEST_I_FLAGS) -c lib/gtest/src/gtest-all.cc -o $(GTEST_TARGET)

clean:
	$(RM) -r $(BUILDDIR) $(TARGET) $(TEST_TARGET)
