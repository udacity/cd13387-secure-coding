import socket
import base64

# Load credentials from auth.txt
def load_credentials():
    try:
        with open('auth.txt', 'r') as file:
            lines = file.read().strip().split('\n')
            if len(lines) != 2:
                raise ValueError("auth.txt must contain exactly two lines.")
            username = lines[0].strip()
            password_base64 = lines[1].strip()
            return username, password_base64
    except Exception as e:
        print(f"Error loading credentials: {e}")
        exit(1)

USERNAME, PASSWORD_BASE64 = load_credentials()

def handle_client_connection(client_socket):
    try:
        # Prompt for username
        client_socket.sendall(b"Username: ")
        username = client_socket.recv(1024).decode('utf-8').strip()

        # Prompt for password
        client_socket.sendall(b"Password: ")
        password = client_socket.recv(1024).decode('utf-8').strip()

        # Check credentials
        if username == USERNAME and base64.b64encode(password.encode('utf-8')).decode('utf-8') == PASSWORD_BASE64:
            client_socket.sendall(b"Login successful\n")
        else:
            client_socket.sendall(b"Login failed\n")

    finally:
        client_socket.sendall(b"Closing connection\n")
        client_socket.close()

def main():
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind(('0.0.0.0', 62566))
    server.listen(5)

    while True:
        client_sock, _ = server.accept()
        handle_client_connection(client_sock)

if __name__ == "__main__":
    main()