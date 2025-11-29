@make.exe clean
@make.exe PROJECT_NAME="lpt570" BAUDRATE=115200 DATABITS=8 PARITY=N STOPBITS=1 %*
@cp out\lpt570.bin out\lpt570_full_115200_8N1.bin
@.\tools\IMG_Tools out\lpt570.bin .\out\lpt570_upgrade_115200_8N1.bin .\tools\lzma "EPORT-PW41 Image" --version3

