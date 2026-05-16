CPP             = g++
RM              = rm -f
CPP_FLAGS       = -Wall -c -I. -g -std=c++17
PHPCPP_DIR      ?=
PULSAR_DIR      ?=

LD              = g++
LD_FLAGS        = -Wall -shared -O2
RESULT          = pulsar-phpcpp.so

SOURCES         = $(wildcard src/*.cpp)
OBJECTS         = $(SOURCES:%.cpp=%.o)

ifneq ($(PHPCPP_DIR),)
CPP_FLAGS      += -I$(PHPCPP_DIR)/include
LD_FLAGS       += -L$(PHPCPP_DIR)/lib
endif

ifneq ($(PULSAR_DIR),)
CPP_FLAGS      += -I$(PULSAR_DIR)/include
LD_FLAGS       += -L$(PULSAR_DIR)/lib
endif

all: $(OBJECTS) $(RESULT)

$(RESULT): $(OBJECTS)
	$(LD) $(LD_FLAGS) -o $@ $(OBJECTS) -lphpcpp -lpulsar

clean:
	$(RM) *.obj *~* $(OBJECTS) $(RESULT)

src/%.o: src/%.cpp
	$(CPP) $(CPP_FLAGS) -fpic -c $< -o $@

install: $(RESULT)
	cp $(RESULT) $$(php-config --extension-dir)/
	@echo "extension=pulsar-phpcpp" > $$(php-config --ini-dir 2>/dev/null || echo "/usr/local/etc/php/conf.d")/pulsar.ini
	@echo "Installed $(RESULT) to $$(php-config --extension-dir)/"

.PHONY: all clean install
