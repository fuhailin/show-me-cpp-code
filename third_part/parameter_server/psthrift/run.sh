cd /home/silingtong/parameter_server/psthrift
current=`date "+%Y-%m-%d %H:%M:%S"`  
timeStamp=`date -d "$current" +%s`   
#将current转换为时间戳，精确到毫秒  
#currentTimeStamp=$((timeStamp*1000+`date "+%N"`/1000000)) 
/home/zangruozhou/parameter_server/bazel-bin/psthrift/server -thread_num 64 -n /home/data/base_recall.net -m /home/data/base_recall.meta -mn $1 -d conf/db.conf -tp $2  -mp 1090

#/home/silingtong/parameter_server/bazel-bin/psthrift/server -thread_num 64 -d conf/db.conf -tp $1  -mp 1090
#$currentTimeStamp