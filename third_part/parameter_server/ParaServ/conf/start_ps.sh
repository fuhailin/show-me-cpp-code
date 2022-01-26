#!/bin/sh

ulimit -c unlimited

echo "$@"

next=""
need=2
ModelName=""
ModelType=""
exitCode=0
for arg in $*
do
        [[ "x$next" == "xmn" ]] && ModelName=$arg && need=$((need-1));
        [[ "x$next" == "xmt" ]] && ModelType=$arg && need=$((need-1));
        next=""
        (( $need == 0 )) && break
        [[ "$arg" == "-mn" ]] && next="mn" && continue;
        [[ "$arg" == "-mt" ]] && next="mt" && continue;
done

echo STARTING PS SERVER $ModelName $ModelType

STRCMD=" "
for arg in $*
do
        STRCMD="${STRCMD} $arg "
done

echo $CMD

if [[ "_$ModelType" == "_online" ]]
then
        disk_name=/dev/vdb
        disk_id=$(ls -l ${disk_name} | awk '{print $5,$6}' | sed 's/ //g' | tr ',' ':')

        echo "model name is ${ModelName}"
        #echo "disk id is $disk_id"

        cgcreate -g "cpu,blkio:ps_${ModelName}"
        if [ $? != 0 ] ;then
                yum install -y libcgroup-tools;
                sleep 1
                /usr/bin/cgcreate -g "cpu,blkio:ps_${ModelName}";
        fi

        cgset -r blkio.throttle.read_iops_device="${disk_id} 1600" ps_$ModelName
        cgset -r blkio.throttle.write_iops_device="${disk_id} 1400" ps_$ModelName
        cgset -r blkio.throttle.read_bps_device="${disk_id} 157286400" ps_$ModelName
        cgset -r blkio.throttle.write_bps_device="${disk_id} 157286400" ps_$ModelName
        cgset -r cpu.cfs_quota_us="50000" ps_$ModelName
        cgset -r cpu.cfs_period_us="10000" ps_$ModelName

        cgexec -g cpu,blkio:ps_$ModelName ./ParaServ "$@" 2>&1
        exitCode=$?
        cgdelete -g cpu,blkio:ps_$ModelName
else
        ./ParaServ "$@" 2>&1
        exitCode=$?
fi

echo PS SERVER EXIT CODE IS $exitCode



#alarm 



if [[ "_$exitCode" != "_15" ]] && [[ "_$exitCode" != "_137" ]]
then
    webServer=""
    Pwd=$(/usr/bin/pwd)
    if [[ "$Pwd" =~ "webserver" ]]; then
        webServer="10.11.11.251:8082"
    elif [[ "$Pwd" =~ "develop" ]]; then
        webServer="10.11.11.1:9082"
    else
        exit
    fi
    Content="ps server exception, exit code is $exitCode"
    #urlencode
    cont=$(echo $Content | xxd -plain | tr -d '\n' | sed 's/\(..\)/%\1/g')
    #curl ps_monitor
    echo curl "${webServer}/alarm/individual?model_name=${ModelName}&content=${cont}"
    curl "${webServer}/alarm/individual?model_name=${ModelName}&content=${cont}"
fi
