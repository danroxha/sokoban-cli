FROM ubuntu:xenial-20210804

RUN apt-get update && apt-get install build-essential rsync -y

WORKDIR /opt/sokoban

COPY . /opt/sokoban

RUN make

ENTRYPOINT /opt/sokoban/build/sokoban
