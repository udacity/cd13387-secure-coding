import requests

username = 'user'
password = 's3cretP4ssword'

response = requests.post('http://localhost:5000', json={'username': username, 'password': password})
print('Response from server:', response.text)
