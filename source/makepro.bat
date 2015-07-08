cd algorithm
qmake -t vclib

cd ../qtexdb
qmake -t vclib

cd ../protocol
qmake -t vclib

cd ../comobject
qmake -t vclib

cd ../logger
qmake -t vclib

cd ../usermanage/logindialog
qmake -t vclib
cd ../

cd ../systemset/systemsetdlg
qmake -t vclib

cd ..
qmake -t vcapp

cd ../resultquery
qmake -t vclib

cd ../datatest/datatestdlg
qmake -t vclib

cd ..
qmake -t vcapp

cd ../delucom
qmake -t vcapp

cd ../report
qmake -t vclib

cd ../qexcel
qmake -t vclib

cd ../calcverify
qmake -t vclib

cd ../cmbverify
qmake -t vclib

cd ../flowweight
qmake -t vclib

cd ../masterslaveset
qmake -t vclib

cd ../flowstandard
qmake -t vclib

cd ../totalweight
qmake -t vclib

cd ../totalstandard
qmake -t vclib

cd ../tvercomp
qmake -t vclib

cd ../tverparam
qmake -t vclib

cd ../gui
qmake -t vcapp

cd ..
