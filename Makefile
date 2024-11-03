CXX = g++
AR = ar

COMPILE_OPTIONS = -O2 -std=c++20
LINK_OPTIONS =

SOURCE_DIR = ${PWD}/source
OBJ_DIR = ${PWD}/obj
BUILD_DIR = ${PWD}/build
TESTS_DIR = ${PWD}/tests

SOURCES = $(wildcard $(SOURCE_DIR)/*.cpp)
OBJECTS = $(patsubst $(SOURCE_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))

APPNAME = tuia
SHARED = ${BUILD_DIR}/${APPNAME}.dll
STATIC = ${BUILD_DIR}/lib${APPNAME}.a

help:
	@echo "make           - show this help message"
	@echo "make help      - show this help message"
	@echo "make all       - compile, build and test"
	@echo "make env       - print environment"
	@echo "make compile   - compile libraries"
	@echo "make build     - build libraries"
	@echo "make static    - build static library"
	@echo "make shared    - build shared library"
	@echo "make clean     - clean project"

all: compile build test

rebuild: clean all

env:
	@echo "SOURCE_DIR = ${SOURCE_DIR}"
	@echo "OBJ_DIR    = ${OBJ_DIR}"
	@echo "SOURCES    = ${SOURCES}"
	@echo "OBJECTS    = ${OBJECTS}"
	@echo "STATIC     = ${STATIC}"
	@echo "SHARED     = ${SHARED}"

${OBJ_DIR}: 
	@echo "create necessary directories"
	mkdir -p ${OBJ_DIR}
	@echo "done"

${BUILD_DIR}: 
	@echo "create necessary directories"
	mkdir -p ${BUILD_DIR}
	@echo "done"

compile: ${OBJ_DIR} ${BUILD_DIR} ${OBJECTS}

$(OBJ_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	$(CXX) $(COMPILE_OPTIONS) -c -o $@ $<

build: static shared

test: compile-tests run-tests

compile-tests:
	${CXX} ${TESTS_DIR}/testcolor.cpp -o ${BUILD_DIR}/testcolor ${COMPILE_OPTIONS} -I ${SOURCE_DIR} -L ${BUILD_DIR} -l ${APPNAME}
	${CXX} ${TESTS_DIR}/testtuia.cpp -o ${BUILD_DIR}/testtuia ${COMPILE_OPTIONS} -I ${SOURCE_DIR} -L ${BUILD_DIR} -l ${APPNAME}
	${CXX} ${TESTS_DIR}/draw.cpp -o ${BUILD_DIR}/draw ${COMPILE_OPTIONS} -I ${SOURCE_DIR} -L ${BUILD_DIR} -l ${APPNAME}
	${CXX} ${TESTS_DIR}/screen.cpp -o ${BUILD_DIR}/screen ${COMPILE_OPTIONS} -I ${SOURCE_DIR} -L ${BUILD_DIR} -l ${APPNAME}
	${CXX} ${TESTS_DIR}/change_screens.cpp -o ${BUILD_DIR}/change_screens ${COMPILE_OPTIONS} -I ${SOURCE_DIR} -L ${BUILD_DIR} -l ${APPNAME}
	${CXX} ${TESTS_DIR}/text_image.cpp -o ${BUILD_DIR}/text_image ${COMPILE_OPTIONS} -I ${SOURCE_DIR} -L ${BUILD_DIR} -l ${APPNAME}
	${CXX} ${TESTS_DIR}/ui.cpp -o ${BUILD_DIR}/ui ${COMPILE_OPTIONS} -I ${SOURCE_DIR} -L ${BUILD_DIR} -l ${APPNAME}

run-tests:
	${BUILD_DIR}/testcolor
	${BUILD_DIR}/testtuia
#	${BUILD_DIR}/draw

static:
	${AR} rvs ${STATIC} ${OBJECTS}

shared:
	${CXX} ${OBJECTS} -o ${SHARED} -shared ${LINK_OPTIONS}

clean:
	rm -rf ${OBJ_DIR}/* ${BUILD_DIR}/*