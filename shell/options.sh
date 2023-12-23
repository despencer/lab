#!/bin/sh

usage() {
 echo "Usage: options --name NAME --ip IP"
 exit 1
}

opts=$(getopt --longoptions name:,ip: --name "test" --options "" -- "$@")
if [ "$?" -ne 0 ]; then
    usage
fi
eval set -- "$opts"

NAME=''
IP=''

while [[ $# -gt 0 ]]; do
   case "$1" in
      --name) NAME=$2 ; shift 2 ;;
      --ip) IP=$2 ; shift 2 ;;
      --) shift ;;
      *) echo "Internal error" ; exit 1 ;;
   esac
done

if [ $NAME=='' ]; then
  echo name is not provided
  usage
fi

echo "name=$NAME ip=$IP"
