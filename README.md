# 事前準備

## (Windows User) WSL install
請以 **管理員身分** 開啟 windows power shell, 輸入以下指令
```shell
$ systeminfo | find "System Type"
$ dism.exe /online /enable-feature /featurename:Microsoft-Windows-Subsystem-Linux /all /norestart
$ dism.exe /online /enable-feature /featurename:VirtualMachinePlatform /all /norestart
```
並且根據系統型別(x64 or arm64), 下載對應的 WSL更新檔
> x64
> https://wslstorestorage.blob.core.windows.net/wslblob/wsl_update_x64.msihttps://wslstorestorage.blob.core.windows.net/wslblob/wsl_update_x64.msi

> arm64
> https://wslstorestorage.blob.core.windows.net/wslblob/wsl_update_arm64.msi

完成後, 在 Power Shell中執行
```shell
$ wsl --set-default-version 2
```
最後, 下載WSL (下列網址, 或是在Windows商店輸入 Ubuntu 18.04 LTS 查詢) 並啟動
> https://www.microsoft.com/zh-tw/p/ubuntu-1804-lts/9n9tngvndl3q?rtc=1&activetab=pivot:overviewtab

下載過程, 可以先在 Visual Studio Code 安裝 Remote WSL 套件, 之後等到WSL下載完成並啟動後, 設定帳號、密碼

## WSL or Linux (Ubuntu 18.04 LTS)
### 非Windows用戶可以跳過
可以在 "開始" -> "Ubuntu" 開啟 WSL, 或是在 VSCode 的 RemoteWSL 套件中開啟(建議)。
請注意, 請進入到 WSL的家目錄( ~/ 或是 /home/[username]) 下, 不要到 windows的目錄( /mnt/* )
因為 windows 目錄對Virtual Machine是掛載點 , 會受到一些作業系統的限制


### 進入WSL或是在Linux中
請先設定 git 資訊, 在 clone 專案
```shell=
$ git config --global user.name <Your username>
$ git config --global user.email <Your email>
```

把專案 clone 下來後,進入專案目錄(可在 bash 使用 `code ./<folder name>` 進入) 進行以下指令
```shell=

$ chmod +x ./install.sh
$ ./install.sh
```
此時, 已經完成套件安裝。install.sh中, 包含 docker 與 npm 的下載指令, 若有需要可以使用。

在 64bits System 上, 已經完成對 32bit System compiler的支援 , 透過使用 `g++-multilib gcc-multilib` 兩個 library。
Ubuntu 16.04 ~ 20.04 的開發者, 已經完成向下編譯的支援

若想直接使用舊版gcc編譯, (Ubuntu 為 16.04 ~ 18.04), 可以取消 install.sh `support i386` 區塊的註解, 使用舊版 g++ 進行編譯
若有其他考量, 也可以使用 docker 封裝 i386的 Ubuntu 14.04, 取消 install.sh `docker` 區塊的註解, 然後修改 package.json 的 `<your 'code' path>`, 把自己的 `/code` 資料夾掛載到docker中, 再進行編譯即可

