PACKAGE="com.nuco.nvmjit"
OUTDIR="./com/nuco/nvmjit"

cd "$(dirname "$0")"

rm -fr $OUTDIR
mkdir -p $OUTDIR

swig -java -c++ -package $PACKAGE -outdir $OUTDIR NvmJIT.i
