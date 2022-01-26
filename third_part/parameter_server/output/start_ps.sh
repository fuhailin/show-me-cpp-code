#!/bin/sh

echo "$@"

next=1
ModelName=""
for arg in $*
do
        ModelName=$arg
        (( next == 0 )) && break
        [[ "$arg" == "-mn" ]] && next=0
done

echo STARTING PS SERVER $ModelName

STRCMD=" "
for arg in $*
do
        STRCMD="${STRCMD} $arg "
done

echo $CMD
./ParaServ "$@" 2>&1

echo PS SERVER EXIT CODE IS $?
