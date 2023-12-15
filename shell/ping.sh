log="/dev/null"
if ping -c 1 archlinux.org &> $log
then
   echo "Success 1" "$?"
else
   echo "Fail 1" "$?"
fi
if ping -c 1 archlnux.org &> /dev/null
then
   echo "Success 2" "$?"
else
   echo "Fail 2" "$?"
fi
ping -c 1 archlnux.org &> /dev/null
if [ "$?" -ne 0 ]; then
   echo "Fail 3"
fi
