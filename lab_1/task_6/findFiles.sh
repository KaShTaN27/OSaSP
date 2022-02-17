#!/bin/bash
a=3
deniedSymbol='/'
if [ "$#" -ne "$a" ]
then
  echo "Script takes three parameters:"
  echo "  1 - name of output file;"
  echo "  2 - catalog;"
  echo "  3 - files extension;"
exit 0
fi

case $1 in
*"$deniedSymbol"*)
echo "Error: Invalid output file name" >&2
exit 0
;;
esac

if ! [ -d $2 ]
then
  echo "Error: There is no such catalog" >&2
  exit 0
fi

find $2 -maxdepth 1 -name "*.$3" -printf "%f\n" | sort > $1
cat $1
