# Use an official Python runtime as a parent image
FROM python:3.9-slim

# Install tcpdump
RUN apt-get update && apt-get install -y tcpdump

# Install Flask and requests for the simple HTTP server and client
RUN pip install flask requests


# Set up the working directory
WORKDIR /app

# Add the HTTP server and client scripts
COPY server.py /app/server.py
COPY client.py /app/client.py

# Expose the port the server will run on
EXPOSE 5000

# Run the HTTP server script by default
CMD ["python", "server.py"]
