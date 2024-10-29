import socket
import sys

def main():
    if len(sys.argv) != 3:
        print("Usage: python telnet_client.py <host> <port>")
        sys.exit(1)

    host = sys.argv[1]
    port = int(sys.argv[2])

    # Create socket
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client.connect((host, port))

    # Input username and password
    username = input("Username: ")
    client.sendall(username.encode('utf-8') + b'\n')

    password = input("Password: ")
    client.sendall(password.encode('utf-8') + b'\n')

    # Receive and print response
    response = client.recv(1024).decode('utf-8').strip()
    print(response)

    response = client.recv(1024).decode('utf-8').strip()
    print(response)

    client.close()

if __name__ == "__main__":
    main()