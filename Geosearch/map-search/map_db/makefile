BUILD_PATH = build
PY_BUILD_PATH = py_build

CC = g++
INCLUDES = -I include
LIBS =
CFLAGS = -Wall -Werror -g
LINKFLAGS =


SRCDIRS = json_src db
TESTFILE = test.cpp

PYMODULE = db
PYWRAPPER = py_wrapper.cc
PYFLAGS = -I /usr/include/python2.7 -I /usr/lib/python2.7/config

CPP_SOURCES = $(foreach d, $(SRCDIRS), $(wildcard $(d)/*.cpp))
CPP_OBJS = $(patsubst %.cpp, $(BUILD_PATH)/%.o, $(CPP_SOURCES))

CPP_FPIC_OBJS = $(patsubst %.cpp, $(PY_BUILD_PATH)/%.o, $(CPP_SOURCES))
PYWRAPPER_OBJS = $(patsubst %.cc, $(PY_BUILD_PATH)/%.o, $(PYWRAPPER))

default: init $(CPP_OBJS)

$(CPP_OBJS): $(BUILD_PATH)/%.o: %.cpp
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

init:
	$(foreach d, $(SRCDIRS), mkdir -p $(BUILD_PATH)/$(d);)

test: $(CPP_OBJS) $(TESTFILE)
	$(CC) $^ -o test $(LINKFLAGS) $(LIBS)

py: init_py $(CPP_FPIC_OBJS) py_build

py_build: $(CPP_FPIC_OBJS) $(PYWRAPPER_OBJS)
	$(CC) -shared -o $(PYMODULE).so $^

init_py:
	$(foreach d, $(SRCDIRS), mkdir -p $(PY_BUILD_PATH)/$(d);)

$(CPP_FPIC_OBJS): $(PY_BUILD_PATH)/%.o: %.cpp
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@ -fpic

$(PYWRAPPER_OBJS): $(PY_BUILD_PATH)/%.o: %.cc
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@ -fpic $(PYFLAGS)

info:
	@echo "CPP_SOURCES: $(CPP_SOURCES)"
	@echo "CPP_OBJS: $(CPP_OBJS)"
	@echo "CPP_FPIC_OBJS: $(CPP_FPIC_OBJS)"
