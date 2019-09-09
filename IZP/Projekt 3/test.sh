#!/bin/bash

# IZP proj3, neoficialni testy
# autor: xkukuc01, Discord: JohnyK
#
# spusteni vsech testu: 
# $ ./test.sh
#
# spusteni konkretniho testu:
# $ ./test.sh -t nazev
#
# spusteni s podrobnejsim vypisem (vypisuje vystup z diff a valgrind):
# $ ./test.sh -v

APP=./proj3
DIFF=diff
VALGRIND=valgrind
TESTS_DIR=./tests
ARGS_NAME=args
OUT_NAME=out
TMPFILE=tmp_out
VALGRIND_CHECK_PHRASE_01="All heap blocks were freed -- no leaks are possible"
VALGRIND_CHECK_PHRASE_02="ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)"
VALGRIND_CHECK_COUNT=2
RED='\033[1;31m'
GREEN='\033[1;32m'
NC='\033[0m' # No Color
USE_COLOR=1
TOTAL_CNT=0
ERROR_CNT=0

function print_ok() {
  TEXT=$1
  if [ "$USE_COLOR" -eq 1 ] ; then
    echo -e "[${GREEN}OK${NC}] $TEXT"
  else
    echo -e "[OK] $TEXT"
  fi
}

function print_err() {
  TEXT=$1
  if [ "$USE_COLOR" -eq 1 ] ; then
    echo -e "[${RED}FAILED${NC}] $TEXT"
  else
    echo -e "[FAILED] $TEXT"
  fi
}

function test() {
  TEST_PATH=$1
  
  if [ ! -d "$TEST_PATH" ]; then
    echo "TEST NOT EXIST"
    return
  fi
  
  ((TOTAL_CNT++))
  
  ARGS=$(cat ${TEST_PATH}/${ARGS_NAME})
  OUT=${TEST_PATH}/${OUT_NAME}
  
  # test output
  echo "Test: $(basename ${TEST_PATH})"
  ${APP} $ARGS 1> ${TMPFILE} 2> /dev/null
  RETURN_CODE=$?
  
  if [ "$(cat $OUT)" = "error" ]; then
    # error expected
    if [[ $RETURN_CODE -ne 0 ]]; then
      print_ok "error expected"
    else
      print_err "error expected"
      ((ERROR_CNT++))
    fi
    
    if [ -n "$VERBOSE" ] ; then
      cat ${TMPFILE}
    fi
  
  else
    # output expected
  
    DIFF_RESULT=$(${DIFF} ${OUT} ${TMPFILE})
    
    if [ -z "${DIFF_RESULT}" ]; then
      print_ok "output"
    else
      print_err "output"
      ((ERROR_CNT++))
      
      if [ -n "$VERBOSE" ] ; then
        echo ${DIFF_RESULT}
      fi
    fi
  fi
  
  # test valgrind
  ${VALGRIND} ${APP} $ARGS 1> /dev/null 2> ${TMPFILE}
  
  VALGRIND_CHECK_RESULT=$(cat ${TMPFILE} | grep "$VALGRIND_CHECK_PHRASE_01\|$VALGRIND_CHECK_PHRASE_02" | wc -l)
  
  if [ $VALGRIND_CHECK_RESULT -eq $VALGRIND_CHECK_COUNT ] ; then
    print_ok "valgrind"
  else
    print_err "valgrind"
    ((ERROR_CNT++))
    
    if [ -n "$VERBOSE" ] ; then
      cat ${TMPFILE}
    fi
  fi
  
  echo "---------------------------------"
  rm ${TMPFILE}
}

while getopts ":vt:" opt; 
do  
case $opt in    
    v)      VERBOSE=1
            ;;
    t)      SPECIFIC_TEST=$OPTARG
            ;;
   \?)      echo "Invalid option: -$OPTARG" >&2
            ;;  
esac
done

if [ -z "$SPECIFIC_TEST" ] ; then
  # all tests
  for file in $(ls ${TESTS_DIR});
  do
    test $TESTS_DIR/${file}
  done
else
  # perform specific test
  test $TESTS_DIR/${SPECIFIC_TEST}
fi

echo "Test count: $TOTAL_CNT, Error count: $ERROR_CNT"
