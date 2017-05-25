JAVA_HOME=/home/yulong/jdk-9
BLAKE2B_DIR=/home/yulong

PACKAGE="com.nuco.nvmjit"
OUTDIR="./build/com/nuco/nvmjit"

cd "$(dirname "$0")"

rm -fr $OUTDIR
mkdir -p $OUTDIR

swig -java -c++ -package $PACKAGE -outdir $OUTDIR NvmJIT.i

make && make dist
