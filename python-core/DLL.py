import json
import time
import socket
import threading
import random


class DataLinkLayer:
    
    def __init__(self, window_size,port):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.sock.bind(("localhost", port))
        self.timeout = 2 #secs
        self.busy = False
        self.window_size = window_size
        self.semaphore = threading.Lock()
        self.window_status = [False]*window_size
        self.timer_out = [0]*window_size
        self.no_of_busy_windows = 0
        self.window_buffer = [0]*window_size
        self.next_window_number = 0
        self.port = port
        
    def run(self):
        recv = threading.Thread(target=self.rx)
        recv.start()
        while True:
            print(self.window_status)
            time.sleep(.5)
            if self.no_of_busy_windows > 0:
                for i,j in enumerate(self.window_status):
                    if j and self.timer_out[i] < time.time():
                        print(f"Timer for {i} has expired !")
                        self.timer_out[i] = time.time()+self.timeout
                        self.__resend__(self.window_buffer[i])
                        
                    
    def __getwindownumber__(self):
        self.semaphore.acquire()
        self.no_of_busy_windows+=1
        if self.no_of_busy_windows == self.window_size:
            self.busy = True
        
        for nw,i in enumerate(self.window_status):
            if i == False:
                self.next_window_number = nw
                self.window_status[nw] = True
                self.timer_out[nw] = time.time() + self.timeout
                break
        
        self.semaphore.release()
        return self.next_window_number
        
    
    def sendTo(self,file_name,IPAddr,port):
        file = open(file_name,'r')
        for line_number,line in enumerate(file):
            
            #create frame
            #[frame_type,window_number,line_number,data]  
            #[ack,window_number,checksum]     -->>> ACK FRAME
            #[nack,window_number,checksum]     --->>NACK FRAME
            #[data,window_number,line_number,data,checksum] -->> data frame
            #store in window buffer
            
            
            
            data = [line_number,line]
            self.__send__("data",data,IPAddr,port)
            
            
    
    def __send__(self,frame_type,frame,IPAddr,port):
        
        while self.busy:
            print("All windows busy ! Retrying in 5 secs...")
            time.sleep(5)
            print("Retrying....")
        print(f"{self.window_size-self.no_of_busy_windows} windows free !")
        window_number = self.__getwindownumber__()
        frame = [frame_type,window_number]+list(frame)
    

        byte_frame = json.dumps(frame)
        print(byte_frame)
        checksum_payload = self.checksumCalculator(byte_frame)
        frame.append(checksum_payload[0])
        byte_frame = json.dumps(frame).encode()
        
        frame.extend([IPAddr,port])
        self.window_buffer[window_number] = list(frame)
        print(byte_frame)
        self.sock.sendto(byte_frame, (IPAddr, port))

    def __resend__(self,frame):
        print(frame)
        byte_frame = json.dumps(frame[:-2]).encode()
        self.sock.sendto(byte_frame,(frame[-2],frame[-1]))


    
    def rx(self):
        while True:
            byte_data,addr = self.sock.recvfrom(1024)
            #print(byte_data)
            data = json.loads(byte_data.decode())
            checksum_payload = data[-1]
            #print(data[:-1])
            print(checksum_payload,self.checksumCalculator(json.dumps(data[:-1]))[0])
            if self.checksumCheck(checksum_payload,self.checksumCalculator(json.dumps(data[:-1]))[0]):
                self.recv(data[:-1],addr)
            else:
                print("Bad Frame Recved !")
    
    
    def recv(self,data,addr):
        print(data,addr)
        if data[0] == "data":
            time.sleep(3)
            byte_frame = json.dumps(["ack",data[1]])
            checksum = self.checksumCalculator(byte_frame)
            byte_frame=json.dumps(["ack",data[1],checksum[0]]).encode()
            self.sock.sendto(byte_frame,(addr[0],addr[1]))
            file = open("recv.txt","a")
            file.writelines(str(data[2:]))
            file.close()
         
        if data[0] == "ack":
            self.semaphore.acquire()
            self.no_of_busy_windows -= 1
            self.window_status[data[1]] = False
            self.busy = False
            self.semaphore.release()

        
        
    def onesComplimentAddition(self,a,b):
        c = ['0','0','0','0','0','0','0','0','0']
        a=a[::-1]
        a+=(8-len(a))*'0'
        b=b[::-1]
        b+=(8-len(b))*'0'
        #print(a,b)
        for i in range(8):
            #print(c)
            lache = c[i]
            c[i] = str((int(a[i])^int(b[i]))^int(lache))
            c[i+1] = str(((int(a[i])^int(b[i]))&int(lache))|(int(a[i])&int(b[i])))
            #print(a[i],b[i],c[i],c[i+1])

        c = ''.join(c[::-1])
        #print("return")
        if(c[0]=='0'):
            return c[1:]

        return self.onesComplimentAddition(c[1:],'00000001')


    def checksumCalculator(self,playload):
        print(playload)
        checksum = '00000000'
        for i in playload:
            checksum = self.onesComplimentAddition(checksum,bin(ord(i))[3:])
        
        return (bin(255 - int("0b"+checksum,2)),"0b"+checksum)
    
    def checksumCheck(self,recv,calculated):
        #print(recv,calculated)
        return int(recv,2) == int((calculated),2)