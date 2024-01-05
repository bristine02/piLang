TARGET := pilang
CXX := g++
OPTIONS := -Wall -Wextra
#JSONCPP_DIR = /usr/include/jsoncpp/json
C_FLAGS := -c #-I$(JSONCPP_DIR)
LD_FLAGS :=# -ljsoncpp

SRC_DIR := .
SRC_DIRS := $(wildcard $(SRC_DIR) */)
SOURCES := $(wildcard $(SRC_DIR)*.cpp) $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)*.cpp))
OBJECTS := $(patsubst %.cpp,outputs/%.o,$(notdir $(SOURCES)))

all: outputs $(TARGET)

main.o: main.cpp
	@echo 'Building main.o from main.cpp'
	$(CXX) $(C_FLAGS) main.cpp -o main.o

define generate_object_rule
$(1): $(2)
	@echo 'Building $$@ from $$^'
	$(CXX) $(C_FLAGS) $$< -o $$@
endef

$(foreach object, $(OBJECTS), \
	$(eval \
		$(call generate_object_rule, $(object), $(filter \
			%/$(notdir $(patsubst %.o, %.cpp, $(object))), $(SOURCES) \
			)) \
	) \
)

$(TARGET): $(OBJECTS) main.o
	@echo 'Building binary $@ from $^'
	$(CXX) $(OPTIONS) $^ -o $@ $(LD_FLAGS)

outputs:
	mkdir -p outputs

clean:
	rm -f $(TARGET) outputs/*.o main.o

.PHONY: $(TARGET) clean
