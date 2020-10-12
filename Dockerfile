FROM i386/ubuntu:14.04

VOLUME /home/yanhau/NachOS:/app
COPY  ./usr /usr
RUN apt update && apt install -y ed build-essential g++-4.6 wget vim && rm -rf /var/lib/apt/lists/*