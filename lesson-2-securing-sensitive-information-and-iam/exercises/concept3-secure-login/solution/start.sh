#!/bin/bash

# Function to handle termination signals
term_handler() {
  echo "Received termination signal. Exiting..."
  exit 0
}

# Trap termination signals
trap 'term_handler' INT TERM

while true; do
#  echo "Starting the application..."
  /app/app
#  echo "Application exited with status $?. Restarting in 1 second..."
#  sleep 1
done