PROJECT_NAME	= finite_state_machine
TARGETS			= fsm
OUTPUT_DIR		= _build

SRC_FILES +=\
	main.c\
	fsm.c\

INC_FOLDERS +=\

C_FLAGS =

CC		= g++
SZ		= size

help:
	@echo following targets are available:
	@echo fsm


include Makefile.common

$(foreach target, $(TARGETS), $(call define_target, $(target)))

OBJECTS := $(SRC_FILES:%.c=$(OUTPUT_DIR)/%.o)

all: build $(OUTPUT_DIR)/$(TARGETS)

$(OUTPUT_DIR)/%.o: %.c
	@echo compiling : $(notdir $<)
	@$(CC) $(C_FLAGS) $(INC_FOLDERS) -o $@ -c $<

$(OUTPUT_DIR)/$(TARGETS): $(OBJECTS)
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