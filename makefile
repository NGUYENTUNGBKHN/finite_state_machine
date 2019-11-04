PROJECT_NAME	= finite_state_machine
TARGETS			= fsm
OUTPUT_DIR		= _build

SRC_FILES +=\
	main.cpp\
	fsm.cpp\

INC_FOLDERS +=\

C_FLAGS = -Wall

CC		= g++
SZ		= size

help:
	@echo following targets are available:
	@echo fsm


include Makefile.common


OBJECTS := $(SRC_FILES:%.cpp=$(OUTPUT_DIR)/%.o)

all: build $(OUTPUT_DIR)/$(TARGETS)

$(OUTPUT_DIR)/%.o: %.cpp
	@echo compiling : $(notdir $<)
	@$(CC) $(C_FLAGS) $(INC_FOLDERS) -o $@ -c $<

$(OUTPUT_DIR)/$(TARGETS): $(OBJECTS)
	@rm -rf $(OUTPUT_DIR)/$(TARGETS).exe
	@echo Preparing: $(TARGETS).exe
	@$(CC) $(C_FLAGS) $(INC_FOLDERS) -o $(OUTPUT_DIR)/$(TARGETS) $(OBJECTS)

build:
ifneq ("$(wildcard $(OUTPUT_DIR))","")
	@echo $(OUTPUT_DIR) existed
else
	@echo create file $(OUTPUT_DIR)
	mkdir $(OUTPUT_DIR)
endif

clean:
	rm -rf $(OUTPUT_DIR)