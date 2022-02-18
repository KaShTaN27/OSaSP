#!/bin/bash
params=2
deniedSymbol='/'
if [ "$#" -ne "$params" ]
then
  {
    echo "Script takes two parameters:"
    echo "  1 - catalog;"
    echo "  2 - name of output file;"
  } >&2
exit 0
fi

if ! [ -d $1 ]
then
  echo "Error: There is no such catalog" >&2
  exit 0
fi

case $2 in
*"$deniedSymbol"*)
echo "Error: Invalid output file name" >&2
exit 0
;;
esac

find $1 -type f -printf "%h %s\n" |
awk '{summArr[$1] += $2; amountArr[$1]++} END {for (i in amountArr) printf "Path: %s\nTotal size: %d bytes\nViewed files: %d\n\n", i, summArr[i], amountArr[i]}' > $2
cat $2
