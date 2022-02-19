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
exit 1

fi

if ! [ -d $1 ]
then
  echo "Error: There is no such catalog" >&2
  exit 1

fi

case $2 in
*"$deniedSymbol"*)
echo "Error: Invalid output file name" >&2
exit 1
;;
esac

echo -n > $2
for i in $(find $1 -type d)
do
    echo "Viewed files: $(find $i -maxdepth 1 -type f | wc -l)" >> $2
    echo "Total size: $(du -bsh $i)" >> $2
done
cat $2
