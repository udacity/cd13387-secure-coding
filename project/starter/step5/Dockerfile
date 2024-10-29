# Use the official GCC image from the Docker Hub
FROM gcc:latest

# Install build essentials, and legacy services
RUN apt-get update && \
    apt-get install -y build-essential \
    telnetd ftpd rsh-server net-tools nmap xinetd

# Set the working directory inside the container
WORKDIR /app

# Copy the C program to the working directory
COPY login.c /app/
COPY users.txt /app/

# Compile the C program
RUN gcc /app/login.c -o /app/login

# Configure services
RUN echo "ALL: ALL" >> /etc/hosts.allow && \
    echo "ALL: ALL" >> /etc/hosts.deny


#Expose ports
EXPOSE 21,23,513

# Configure xinetd to start services
COPY xinetd.conf /etc/xinetd.conf
COPY telnetd /etc/xinetd.d/telnet
COPY vsftpd /etc/xinetd.d/ftp
COPY rlogind /etc/xinetd.d/rlogin

# Start xinetd and the services
CMD ["/bin/bash", "-c", "service xinetd start && /bin/bash"]

# Specify the command to run the program
#CMD ["/bin/bash", "/app/start.sh"]