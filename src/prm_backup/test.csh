# First line in csh scripts must be commented

setenv RFLIST rflist.99
set local=LOCAL

set input_zbs = $1
echo "input_zbs   = " $input_zbs

cat <<! >! $RFLIST
10{{"$input_zbs",$local,,RED,,,"recl=5670 status=old"}}
!

date
cat $RFLIST

./test

date
/bin/rm $RFLIST

