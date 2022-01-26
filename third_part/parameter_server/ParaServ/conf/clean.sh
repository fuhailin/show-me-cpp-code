find /usr/local/webserver/log/ -size +2G|while read f;do cat /dev/null > $f;done;
find /data/logs/ps_logs/ -size +10G|while read f;do cat /dev/null > $f;done;