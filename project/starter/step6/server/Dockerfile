FROM gcc:latest
RUN apt-get update && apt-get install -y libssl-dev net-tools iputils-ping telnet
WORKDIR /app
COPY rootCA.crt server.crt server.key server.c software_update.bin start.sh ./
RUN gcc -o server server.c -lssl -lcrypto

# Make start.sh executable
RUN chmod +x ./start.sh

# Specify the command to run the program
CMD ["/bin/bash", "./start.sh"]
#CMD ["./server"]