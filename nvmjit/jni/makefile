# you need to specifiy the JAVA_HOME and BLAKE2B_DIR environment variables
# before building the projects

JDK_9_INCLUDE=${JAVA_HOME}/include
LLVM_INCLUDE=/usr/include/llvm-3.9
LLVM_C_INCLUDE=/usr/include/llvm-c-3.9

BLAKE2B_LIB=${BLAKE2B_DIR}
LLVM_LIB=/usr/lib/llvm-3.9/lib

CFLAGS=-std=c++0x -I. -I../../include -I${JDK_9_INCLUDE} -I${JDK_9_INCLUDE}/linux -I${LLVM_INCLUDE} -I${LLVM_C_INCLUDE} -O3 -Wall -fPIC
LFLAGS=-L${BLAKE2B_LIB} -L${LLVM_LIB} -l:blake2b.so -lLLVM-3.9 -Wl,--no-undefined -shared

BUILD_DIR=build
VERSION=0.0.2

all: libnvmjit.so

libnvmjit.so: bytearrayext.o
	g++ $(CFLAGS) \
../../libevmjit/Arith256.cpp \
../../libevmjit/Array.cpp \
../../libevmjit/BasicBlock.cpp \
../../libevmjit/Cache.cpp \
../../libevmjit/Compiler.cpp \
../../libevmjit/CompilerHelper.cpp \
../../libevmjit/Endianness.cpp \
../../libevmjit/ExecStats.cpp \
../../libevmjit/Ext.cpp \
../../libevmjit/GasMeter.cpp \
../../libevmjit/Instruction.cpp \
../../libevmjit/JIT.cpp \
../../libevmjit/Memory.cpp \
../../libevmjit/Optimizer.cpp \
../../libevmjit/RuntimeManager.cpp \
../../libevmjit/Type.cpp \
../../libevmjit/Utils.cpp \
NvmJIT_wrap.cxx \
NvmJIT.cpp \
${BUILD_DIR}/bytearrayext.o \
$(LFLAGS) -o build/libnvmjit.so

bytearrayext.o:
	mkdir -p ${BUILD_DIR}
	gcc -std=c11 -I. -I../../include -I${JDK_9_INCLUDE} -I${JDK_9_INCLUDE}/linux -O3 -Wall -fPIC -c \
com_nuco_nvmjit_ByteArrayExt.c \
-o ${BUILD_DIR}/bytearrayext.o

clean:
	rm -rf ${BUILD_DIR}
	
dist: libnvmjit.so
	cp ${BLAKE2B_LIB}/blake2b.so ${BUILD_DIR}
	cp ${LLVM_LIB}/libLLVM-3.9.so.1 ${BUILD_DIR}
	cp file.list ${BUILD_DIR}
	cd ${BUILD_DIR} && tar -czf nvmjit_all_${VERSION}.tar.gz file.list blake2b.so libLLVM-3.9.so.1 libnvmjit.so

