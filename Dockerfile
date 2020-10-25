FROM i386/ubuntu:14.04

VOLUME /mnt/d/OS/NachOS/code:/app
COPY ./usr /usr
RUN apt update
RUN apt install -y ed build-essential g++-4.6 wget vim csh
RUN rm -rf /var/lib/apt/lists/*