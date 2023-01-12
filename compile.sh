#! /bin/sh
#SET VARIABLES
ERRORS_LOG=./logs/errors.log
COMPILE_LOG=./logs/compile.log
LOG_TIME=`date "+%Y-%m-%d %T"`

YELLOW='\033[0;33m'
RED='\033[0;31m'
NC='\033[0m'

pushd ./ >>/dev/null
cd code


echo "COMPILE" >>../${COMPILE_LOG}
echo -e "\n${LOG_TIME}" >>../${ERRORS_LOG}
make main >&1 | tee -a ../${ERRORS_LOG}
#gcc main.c -l glut -o comp
EXITCODE=${PIPESTATUS[0]}
if [ ${EXITCODE} -eq 0 ]
then
    echo -e "${YELLOW}Compiled correctly${NC}"
    mv ./comp ../build/
    popd >>/dev/null
    ./build/comp

else
    echo -e "${RED}Compiled with errors!${NC}"
    popd >>../${COMPILE_LOG}
fi

