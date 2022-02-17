#!/bin/bash
params=2
deniedSymbol='/'
if [ "$#" -ne "$params" ]
then
  echo "Script takes two parameters:"
  echo "  1 - name of compiling file;"
  echo "  2 - name of exe file"
exit 0
fi

if ! [ -f $1 ]
then
  echo "Error: There is no such file" >&2
  exit 0
fi

case $2 in
*"$deniedSymbol"*)
echo "Error: Invalid exe file name" >&2
exit 0
;;
esac

stdout=`gcc $1 -o $2 > temp_err`
if [ $? -ne 0 ]
then
  ER=`cat temp_err`
  echo $ER >&2
else
  echo "File compiled successfully"
  ./"$2"
fi
rm -f temp_err
