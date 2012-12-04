#!/bin/bash

LEX_TEST="./test_lex"
PARSE_TEST="./test_parse"
SEM_TEST="./test_sem"

chmod +x $LEX_TEST
chmod +x $PARSE_TEST
chmod +x $SEM_TEST

$LEX_TEST
$PARSE_TEST
$SEM_TEST

