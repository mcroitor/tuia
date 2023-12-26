CXX = g++
AR = ar

COMPILE_OPTIONS = -O2 -std=c++20
LINK_OPTIONS =

SOURCE_DIR = ${PWD}/source
OBJ_DIR = ${PWD}/obj
BUILD_DIR = ${PWD}/build
TESTS_DIR = ${PWD}/tests

SOURCES = $(wildcard $(SOURCE_DIR)/*.cpp)
OBJECTS = $(SOURCES:$(SOURCE_DIR)/%.cpp=$(OBJ_DIR)/%.o)

APPNAME = tuia
SHARED = ${BUILD_DIR}/${APPNAME}.dll
STATIC = ${BUILD_DIR}/lib${APPNAME}.a

all: compile build test

env:
	@echo "SOURCE_DIR = ${SOURCE_DIR}"
	@echo "OBJ_DIR    = ${OBJ_DIR}"
	@echo "SOURCES    = ${SOURCES}"
	@echo "OBJECTS    = ${OBJECTS}"
	@echo "STATIC     = ${STATIC}"
	@echo "SHARED     = ${SHARED}"

prepare:
	@echo "create necessary directories"
	mkdir -p ${OBJ_DIR} ${BUILD_DIR}
	@echo "done"

compile: ${OBJECTS}

$(OBJ_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	$(CXX) $(COMPILE_OPTIONS) -c -o $@ $<

build: static shared

test:

static:
	${AR} rvs ${STATIC} ${OBJECTS}

shared:
	${CXX} ${OBJECTS} -o ${SHARED} -shared ${LINK_OPTIONS}

clean:
	rm -rf ${OBJ_DIR}/* ${BUILD_DIR}/*