#!/bin/bash
params=2
deniedSymbol='/'
if [ "$#" -ne "$params" ]
then
  {
    echo "Script takes two parameters:"
    echo "  1 - name of compiling file;"
    echo "  2 - name of exe file"
  } >&2
exit 1
fi

if ! [ -f $1 ]
then
  echo "Error: There is no such file" >&2
  exit 1
fi

case $2 in
*"$deniedSymbol"*)
echo "Error: Invalid exe file name" >&2
exit 1
;;
esac

gcc $1 -o $2 && ./"$2"
