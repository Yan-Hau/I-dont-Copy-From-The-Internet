# 事前準備

## (For Windows User) WSL install
請以 **管理員身分** 開啟 windows power shell, 輸入以下指令
```shell
$ systeminfo | find "System Type"
$ dism.exe /online /enable-feature /featurename:Microsoft-Windows-Subsystem-Linux /all /norestart
$ dism.exe /online /enable-feature /featurename:VirtualMachinePlatform /all /norestart
```
並且根據系統型別(x64 or arm64), 下載對應的 WSL更新檔

[x64](https://wslstorestorage.blob.core.windows.net/wslblob/wsl_update_x64.msihttps://wslstorestorage.blob.core.windows.net/wslblob/wsl_update_x64.msi)

[arm64](https://wslstorestorage.blob.core.windows.net/wslblob/wsl_update_arm64.msi)

完成後, 在 Power Shell中執行
```shell
$ wsl --set-default-version 2
```
最後, [下載WSL](https://www.microsoft.com/zh-tw/p/ubuntu-1804-lts/9n9tngvndl3q?rtc=1&activetab=pivot:overviewtab)  或是在Windows商店輸入 Ubuntu 18.04 LTS 查詢) 並啟動

下載過程, 可以先在 Visual Studio Code 安裝 Remote WSL 套件, 之後等到WSL下載完成並啟動後, 設定帳號、密碼

## WSL or Linux (Ubuntu 18.04 LTS)

### 非Windows用戶可以跳過
可以在 `"開始" -> "Ubuntu"` 開啟 WSL, 或是在 VSCode 的 `RemoteWSL` 套件中開啟(建議)。
![RemoteWSL](image/RemoteWSL.png)
請注意, 請進入到 WSL的家目錄( ~/ 或是 /home/[username]) 下, 不要到 windows的目錄( /mnt/* )
因為 windows 目錄對 Virtual Machine 是掛載點 , 會受到一些作業系統的限制


### 進入WSL或是在Linux中
若為設定 git 資訊, 請先設定 git 資訊, 然後才 clone 專案
```shell=
$ git config --global user.name <Your username>
$ git config --global user.email <Your email>
```

把專案 clone 下來後, 在專案根目錄下執行
```shell=
$ chmod +x ./install.sh
$ ./install.sh
```
![install](image/install.png)
完成後, 已經完成套件安裝. install.sh中, 包含 docker 與 npm 的下載指令, 若有需要可以使用。

在 64 bits System 上, 已經完成對 32 bit System compiler的支援 , 透過使用 `g++-multilib gcc-multilib` 兩個 library , Ubuntu 16.04 ~ 20.04 的開發者, 已經完成向下編譯的支援

若想直接使用舊版 gcc 編譯, 可以取消 install.sh 中 `support i386` 區塊的註解, 並且自行安裝舊版 g++ 進行後編譯
若有其他考量 , 也可以使用 docker 封裝 i386的 Ubuntu 14.04, 取消 install.sh `docker` 區塊的註解, 然後修改 package.json 的 `<your 'code' path>`, 把自己的 `/code` 資料夾掛載到docker中, 進行編譯即可(專案根目錄已經提供 Dockerfile)

## Start
以下環境, 皆假設在 Linux / WSL 2 中執行

### Cross-compiler
若執行完成 install.sh , coff2noff 資料夾下應該會有檔案 `coff2noff`, 若沒有該檔案, 可以到 `<project root>/conff2noff`執行 ./configure , 並且把 `<project root>/conff2noff/Makefile` CFLAGS, LD 加上 `-m32` 編譯選項 (可直接參考 `./install.sh` 中的 `cross-compiler` 區塊指令)
![coff2noff](image/coff2noff.png)
請注意, 最後編譯的選項需要有 `-m32` 參數

### Build Nachos
接下來, 請到 `<project root>/code/build` 中執行 `cp ./depend.example ./Makefile.dep`, 再執行 `make depend`
![depend](image/depend.png)
此時會建立好編譯器的 Depends , 最後再執行 `make` , 就會編譯完成 nachos
![nachos](image/nachos.png)
如圖所示, 會建立出 `*.o` 檔案, 最後執行 `./nachos` , 會執行Nachos core, 若無出錯, 就對Nachos 編譯完成

### Build Test
最後, 請到 `<project root>/code/test` 中執行 `make`
![test](image/test.png)
輸出若無異常, 就編譯好 test code.
![run-test](image/run-test.png)
可以使用 `nachos -x <filename.noff>` , 執行編譯好的檔案

### Development skills
接下來, 我們可以開始針對 Nachos 進行修改, 但是在此之前, 有幾項你應該學會的技巧
#### Debug Flag
Debug Flag 是一個很實用的技巧, nachos中可以使用 `nachos -d <Flag>`, 開啟對應的Debug Flag, 可以在 `lib/debug.h`查看, 比方說:
- -d + Debug All
- -d t Debug thread
- -d i Debug interrupt
- -d f Debug file system
- -d a Debug address spaces
- -d u Debug system call
透過開啟 DEBUG flag, 可以大幅提高開發效率
![debug](image/debug-flag.png)
當然, 我們亦可以自行插入 DEBUG Flag, 比方說在某處使用
```cpp
/* Some statment*/
.
.
.
DEBUG('*', "It's MY DEBUG FLAG!");
.
.
.
/* Some statment*/
```
![result](image/my-flag.png)
如圖所示, 我們就加入了自己的DEBUG flag