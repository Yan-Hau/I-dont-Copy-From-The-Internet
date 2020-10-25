## ======START support 32-bit system====== ##
echo "check system"
dpkg --print-architecture
dpkg --print-foreign-architectures
sudo dpkg --add-architecture i386

echo "update apt package"
sudo apt update
sudo apt-get dist-upgrade
sudo apt-get install csh
## ======END support 32-bit system====== ##

## ======START compiler====== ##
echo "install build"
sudo apt-get install -y build-essential
sudo apt-get install -y g++-multilib g++-multilib 
## ======END compiler====== ##

## ======START cross-compiler====== ##
echo "cross-compiler"
tar xvf ./usr.tar ./usr
sudo cp -r ./usr/* /usr
rm -rf ./usr
cd ./coff2noff
./configure
sed -i 's/LD=gcc/LD=gcc -m32/' ./Makefile
sed -i 's/CFLAGS= -g -O2 -DRDATA -DHAVE_CONFIG_H -I@top_dir@/CFLAGS= -g -O2 -DRDATA -DHAVE_CONFIG_H -I@top_dir@ -m32/' ./Makefile
make
## ======END cross-compiler ##

## ======START support i386====== ##
# echo "install i386 compiler"
# sudo apt-get install -y g++-4.8 gcc-4.8
# sudo apt-get install -y g++-4.8-multilib g++-4.8-multilib 

# echo "link g++"
# cd /usr/bin
# sudo rm g++ gcc
# sudo ln -s g++-4.8 g++
# sudo ln -s gcc-4.8 gcc
## ======END support i386====== ##

## ======START docker====== ##
# sudo apt-get install -y apt-transport-https ca-certificates curl gnupg-agent software-properties-common
# curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo apt-key add -
# sudo apt-key fingerprint 0EBFCD88
# sudo add-apt-repository "deb [arch=amd64] https://download.docker.com/linux/ubuntu $(lsb_release -cs) stable"
# sudo apt-get update
# sudo apt-get install -y docker-ce docker-ce-cli containerd.io
# sudo usermod -aG docker ${USER}
## ======END docker====== ##