LIBNAME=$1;
OUT="../libs/";

CFLAGS="-std=c99 -Wall -Wextra"
LIBS=$2;

pushd ./ >>/dev/null
cd code/common/functions
gcc ${CFLAGS} -c -g ${LIBNAME}.c ${LIBS} 
EXITCODE=${PIPESTATUS[0]}
if [ ${EXITCODE} -eq 0 ]
then
    mv ./${LIBNAME}.o ${OUT}${LIBNAME}.o
    echo "COMPILED!"
fi
popd >>/dev/null
