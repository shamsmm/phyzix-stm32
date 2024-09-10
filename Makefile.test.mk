# Toolchains
PP=g++

INCDIR = src test
SRCDIR = src/app

INCLUDES = $(addprefix -I, $(INCDIR))

# User defined added source files
SRC += $(wildcard src/app/engine/*.cpp)
SRC += $(wildcard src/app/math/*.cpp)
SRC += $(wildcard test/*.cpp)

OBJ = $(SRC:.cpp=.o)

BINDIR = build/test
TARGET = $(BINDIR)/run

test: $(TARGET)
	./$(TARGET)

build: $(TARGET)

$(TARGET): $(OBJ)
	$(PP) -o $(TARGET) $(addprefix $(BINDIR)/, $(OBJ))

%.o: %.cpp
	@mkdir -p $(dir $(BINDIR)/$@)
	$(PP) $(INCLUDES) -c $< -o $(BINDIR)/$@

clean:
	rm -rf $(BINDIR)

.PHONY: clean