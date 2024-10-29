# Use the official GCC image from the Docker Hub
FROM gcc:latest

# Install OpenSSL library
RUN apt-get update && apt-get install -y libssl-dev hexdump

# Set the working directory inside the container
WORKDIR /app

# Copy the C program to the working directory
COPY login.c /app/
COPY start.sh /app/

# Compile the C program
RUN gcc /app/login.c -o /app/app -lssl -lcrypto

# Make start.sh executable
RUN chmod +x /app/start.sh

# Specify the command to run the program
CMD ["/bin/bash", "/app/start.sh"]
