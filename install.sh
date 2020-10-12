#support 32-bit system
dpkg --print-architecture
dpkg --print-foreign-architectures
sudo dpkg --add-architecture i386
sudo apt update
sudo apt-get dist-upgrade
sudo apt-get install csh

#compiler
sudo apt-get install -y build-essential
sudo apt-get install -y g++-4.8 gcc-4.8
sudo apt-get install -y g++-4.8-multilib g++-4.8-multilib 
sudo rm /usr/bin/g++ /usr/bin/gcc
sudo ln -s g++-4.8 g++
sudo ln -s gcc-4.8 gcc

#docker
sudo apt-get install -y apt-transport-https ca-certificates curl gnupg-agent software-properties-common
curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo apt-key add -
sudo apt-key fingerprint 0EBFCD88
sudo add-apt-repository "deb [arch=amd64] https://download.docker.com/linux/ubuntu $(lsb_release -cs) stable"
sudo apt-get update
sudo apt-get install -y docker-ce docker-ce-cli containerd.io
sudo usermod -aG docker ${USER}

#npm
sudo apt-get install -y npm