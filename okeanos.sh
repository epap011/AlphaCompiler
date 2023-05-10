#!/bin/bash
if [ -f $* ]; then
echo -e "\n***QUADS***"
echo -e "------------------------------------------------\n"
curl -s 'http://snf-68642.vm.okeanos.grnet.gr:5000/' -X POST -H 'Upgrade-Insecure-Requests: 1' --data-raw "$(echo code=$(cat $* | tr '\n' ' ' ))" | sed -n '/1:/,/------------------------------------------------/p' | head -n -1 | sed 's;\&\#39\;;;g' | sed 's;\&\#34;\";g' | sed 's;\^;_t;g' | sed 's;jump ;jump - - ;g' | sed -e 's/\(\bassign[[:space:]]*[[:alnum:]_]*[[:space:]]*[[:alnum:]_]*\)\b/\0 - /g' | sed -e 's/\(\bparam[[:space:]]*[[:graph:]]*\)\b/\0 - - /g' | sed -e 's/\(\bcall[[:space:]]*[[:graph:]]*\)\b/\0 - - /g' | sed -e 's/\(\bgetretval[[:space:]]*[[:graph:]]*\)\b/\0 - - /g' | sed -e 's/\(\bfuncstart[[:space:]]*[[:graph:]]*\)\b/\0 - - /g' | sed -e 's/\(\bfuncend[[:space:]]*[[:graph:]]*\)\b/\0 - - /g' | sed -e 's/\(\breturn[[:space:]]*[[:graph:]]*\)\b/\0 - - /g' | column -t -s " "
echo -e "\n------------------------------------------------"
else
echo Error: Den dineis sosto arxeio bro.
fi
