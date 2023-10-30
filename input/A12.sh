#!/bin/bash
# ---------------------------------------------------------------------
# COMPILERS COURSE - SCRIPT                                           -
# SCRIPT A12 - CST8152 - Fall 2023                                    -
# ---------------------------------------------------------------------

COMPILER="./Compiler"

FILE1="INPUT0_Empty"
FILE2="INPUT1_Hello"
FILE3="INPUT2_Volume"
FILE4="INPUT3_Factorial"
FILE5="INPUT4_Datatypes"
FILE6="INPUT5_General"
FILE7="INPUT6_Big"

ASSIGNMENT="A12"
EXTENSION="nova"
OUTPUT="out"
ERROR="err"

PARAM="r"

# ---------------------------------------------------------------------
# Begin of Tests (A12 - F23) ------------------------------------------
# ---------------------------------------------------------------------

# Basic Tests
$COMPILER $PARAM "${FILE1}.${EXTENSION}" > "${FILE1}-${ASSIGNMENT}.${OUTPUT}" 2> "${FILE1}-${ASSIGNMENT}.${ERROR}"
$COMPILER $PARAM "${FILE2}.${EXTENSION}" > "${FILE2}-${ASSIGNMENT}.${OUTPUT}" 2> "${FILE2}-${ASSIGNMENT}.${ERROR}"
$COMPILER $PARAM "${FILE3}.${EXTENSION}" > "${FILE3}-${ASSIGNMENT}.${OUTPUT}" 2> "${FILE3}-${ASSIGNMENT}.${ERROR}"
$COMPILER $PARAM "${FILE4}.${EXTENSION}" > "${FILE4}-${ASSIGNMENT}.${OUTPUT}" 2> "${FILE4}-${ASSIGNMENT}.${ERROR}"
$COMPILER $PARAM "${FILE5}.${EXTENSION}" > "${FILE5}-${ASSIGNMENT}.${OUTPUT}" 2> "${FILE5}-${ASSIGNMENT}.${ERROR}"
$COMPILER $PARAM "${FILE6}.${EXTENSION}" > "${FILE6}-${ASSIGNMENT}.${OUTPUT}" 2> "${FILE6}-${ASSIGNMENT}.${ERROR}"

# Advanced Tests
$COMPILER $PARAM "${FILE7}.${EXTENSION}" f 100 10 > "${FILE7}-${ASSIGNMENT}-f-100-10.${OUTPUT}" 2> "${FILE7}-${ASSIGNMENT}-f-100-10.${ERROR}"
$COMPILER $PARAM "${FILE7}.${EXTENSION}" a 100 10 > "${FILE7}-${ASSIGNMENT}-a-100-10.${OUTPUT}" 2> "${FILE7}-${ASSIGNMENT}-a-100-10.${ERROR}"
$COMPILER $PARAM "${FILE7}.${EXTENSION}" m 100 10 > "${FILE7}-${ASSIGNMENT}-m-100-10.${OUTPUT}" 2> "${FILE7}-${ASSIGNMENT}-m-100-10.${ERROR}"

# ---------------------------------------------------------------------
# End of Tests (A12 - F23) --------------------------------------------
# ---------------------------------------------------------------------
