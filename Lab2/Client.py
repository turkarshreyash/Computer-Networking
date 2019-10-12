# -*- coding: utf-8 -*-
import socket
import threading

s = socket.socket()
print('Socket created')
port = 2328


s.connect(('192.168.106.141',port))
print('Connection established')

while True:
    if input("Send another message ? ")=="0":
        break
    message = input("Enter message you want to send")
    
    s.send(message.encode())
    print(s.recv(1024).decode())

s.close()
print('Connection Closed')

#192.168.106.141