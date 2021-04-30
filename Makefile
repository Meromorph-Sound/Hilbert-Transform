CC := gcc
CXX := g++

MKDIR := mkdir -p
RM := rm
CP := cp
CHMOD := chmod 755

SRCDIR := ./src

makeObjs = $(patsubst %.cpp,%.o,$(shell find $(SRCDIR) -name '*.cpp'))
compilerInfo = $(shell pkg-config --$1 $2)
libInfo = $(call compilerInfo,libs,$1)
hdrInfo = $(call compilerInfo,cflags,$1)

# LIBS := 
# HDR_INFO := $(call hdrInfo,$(LIBS)) 
# LIB_INFO := $(call libInfo,$(LIBS))




CPPFLAGS := -Wall -g -O3 -I$(SRCDIR) -I.
CXXFLAGS := -std=c++17 -c -fmessage-length=0 -fPIC 
#LDFLAGS := $(LIB_INFO)


APP := test
OBJ := $(call makeObjs,$(SRCDIR))

run: $(APP)
	./$(APP)
	
.PHONY: obj
obj:	$(OBJ)

.PHONY: app
app:    $(APP)

$(APP): $(OBJ)
	$(CXX) $(LDFLAGS) $^ -o $@
	$(CHMOD) $@
        
clean:
	$(RM) $(OBJ)
	$(RM) ./$(APP)
        
.PHONY: list
list: 
	
	$(info Source dir is $(SRCDIR))
	$(info File list is $(OBJ))
	$(info Compiler flags are $(CPPFLAGS) $(CXXFLAGS))
	$(info Linker flags are $(LDFLAGS))

.PHONY: gcc     
gcc:
	$(shell $(CC) -v) 
        
%.o: %.c
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $@ $<