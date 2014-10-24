include makefile.conf

SRCDIRS = $(shell find $(SRCDIR) -type d)
DIRS = $(patsubst $(SRCDIR)%,$(BUILDDIR)%,$(SRCDIRS)) $(BINDIR)
SOURCES = $(shell find $(SRCDIR) -type f -name '*.$(SRCEXT)')
OBJECTS = $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

all: $(DIRS) $(TARGET)

tests:
	$(MAKE) -f makefile.tests

$(DIRS):
	$(MKDIR) $(DIRS)

$(TARGET): $(OBJECTS)
	$(CXX) $^ -o $(TARGET) $(LIBS) $(CFLAGS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	$(CXX) -c $< -o $@ $(INCLUDE) $(CFLAGS)

clean:
	! $(RM) $(DIRS) 2>/dev/null
