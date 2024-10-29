# Use a lightweight Python image
FROM python:3.10-slim

# Set working directory
WORKDIR /app

# Install nmap
RUN apt-get update && \
    apt-get install -y nmap && \
    rm -rf /var/lib/apt/lists/*

# Copy the telnet service script, client script, and auth.txt file
COPY telnetd_service.py /app/telnetd_service.py
COPY telnet_client.py /app/telnet_client.py
COPY auth.txt /app/auth.txt

# Expose the port
EXPOSE 62566

# Run the telnet service
CMD ["python", "telnetd_service.py"]