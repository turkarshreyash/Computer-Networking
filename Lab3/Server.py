import socket
import threading

port_number = 2328

def read_message(client):
    #recv messages from server
    while True:
        print(f"{client.recv(1024).decode()}")

def send_message(client):
    

if __name__ == "__main__":
    s = socket.socket()
    print("Socket Created !")
    s.bind(('',port_number))
    print("Bind Exec !")
    s.listen(5)
    while True:
        print("Listening !")
        client, client_addr = s.accept()
        print(f"{client_addr} is requesting connection !")
        while True:
            if input("Want send message ? ") == "0":
                break
            message = input("Type message : ")
            client.send(message.encode()) 
            print(f"{client.recv(1024).decode()}")
        client.close()