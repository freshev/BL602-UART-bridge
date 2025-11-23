#!/bin/sh
# lpt270
# lpt170
# lpt271
# lpb170
# lpb175
# lpt570
# lpt272

PROJECT_NAME="lpt270"
export PROJECT_NAME

make

if [ $? -eq 0 ]
then
./tools/IMG_Tools out/$PROJECT_NAME.bin ./out/$PROJECT_NAME-upgrade.bin ./tools/lzma "HF-LPx70x1 Image" --version3
python3 lpx70_upgrade.py ./out/$PROJECT_NAME-upgrade.bin
#./tools/IMG_Tools.exe out/$PROJECT_NAME.bin ./out/$PROJECT_NAME-upgrade.bin ./tools/lzma.exe "HF-LPx70x1 Image" --version3
fi

exit $?