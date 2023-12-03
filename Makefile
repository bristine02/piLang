TARGET := pilang
CXX := g++
#LD := $(CXX)
SDIR:= .
OPTIONS := -Wall -Wextra
C_FLAGS:= -c

C_SOURCES = $(shell ls *.cpp)
C_OBJS := $(patsubst %.cpp, ./outputs/%.o, $(C_SOURCES))
outputs/%.o:%.cpp
	@echo 'Building file: $(@F)'
	$(CXX) $(C_FLAGS) $< -o $@

build: $(TARGET)

$(TARGET): $(C_OBJS)
	@echo 'building binary $(@F)'
	$(CXX) $(OPTIONS) $(C_OBJS) -o $(@F)

clean:
	rm -f $(TARGET) ./outputs/*.o

.PHONY: $(TARGET)