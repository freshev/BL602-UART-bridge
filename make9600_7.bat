@make.exe clean
@make.exe PROJECT_NAME="lpt570" BAUDRATE=9600 DATABITS=7 %*
@cp out\lpt570.bin out\lpt570_full_9600_7.bin
@.\tools\IMG_Tools out\lpt570.bin .\out\lpt570_upgrade_9600_7.bin .\tools\lzma "EPORT-PW41 Image" --version3
