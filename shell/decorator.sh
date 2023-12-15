log="./decorator.log"

_start_log() {
 rm $log
 date > $log
}

_run_cmd() {
 echo "================= $1" >> $log
 eval "$2" &>> $log
 if [ "$?" -ne 0 ]; then
    echo "Fail $2 with $?"
 else
    echo "[+] $1"
 fi
}

_start_log
_run_cmd "ping1" 'ping -c 1 archlinux.org'
_run_cmd "sort" 'echo -e "1\n3\n2" | sort'
_run_cmd "ping2" 'ping -c 1 archlnux.org'
