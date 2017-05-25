
JDK_9_INCLUDE=/home/yulong/jdk-9/include
LLVM_INCLUDE=/usr/include/llvm-3.9
LLVM_C_INCLUDE=/usr/include/llvm-c-3.9

BLACK2B_LIB=.
LLVM_LIB=/usr/lib/llvm-3.9/lib

CFLAGS=-std=c++0x -I. -I../../include -I${JDK_9_INCLUDE} -I${JDK_9_INCLUDE}/linux -I${LLVM_INCLUDE} -I${LLVM_C_INCLUDE} -O3 -Wall -fPIC
LFLAGS=-L${BLACK2B_LIB} -L${LLVM_LIB} -l:blake2b.so -lLLVM-3.9 -Wl,--no-undefined -shared

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
bytearrayext.o \
$(LFLAGS) -o libnvmjit.so

bytearrayext.o:
	gcc -std=c11 -I. -I../../include -I${JDK_9_INCLUDE} -I${JDK_9_INCLUDE}/linux -O3 -Wall -fPIC -c \
com_nuco_nvmjit_ByteArrayExt.c \
-o bytearrayext.o

clean:
	rm -rf *.o libnvmjit.so