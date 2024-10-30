FROM gcc:latest
RUN apt-get update && apt-get install -y libssl-dev net-tools iputils-ping telnet
WORKDIR /app
COPY rootCA.crt server.crt server.key server.c software_update.bin ./
RUN gcc -o server server.c -lssl -lcrypto
CMD ["./server"]