#!/bin/bash

APP=./proj1
DIFF=diff
TESTS_DIR=./tests
IN_NAME=in
OUT_NAME=out
CMDS_NAME=cmds
TMPFILE=tmp_out

function test() {
  TEST_PATH=$1
  CMDS_PATH=${TEST_PATH}/${CMDS_NAME}
  IN=${TEST_PATH}/${IN_NAME}
  OUT=${TEST_PATH}/${OUT_NAME}
  ${APP} ${CMDS_PATH} < ${IN} > ${TMPFILE}
  DIFF_RESULT=$(${DIFF} ${OUT} ${TMPFILE})
  rm ${TMPFILE}
  NAME=$(basename ${TEST_PATH})
  if [ -z "${DIFF_RESULT}" ]; then
    echo "${NAME} - OK"
  else
    echo "${NAME} - FAILED"
    echo ${DIFF_RESULT}
  fi
}

for file in $(ls ${TESTS_DIR});
do
  test $TESTS_DIR/${file}
done
