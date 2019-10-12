import sys
import threading
from DLL import DataLinkLayer









if __name__ == "__main__":

    datalinklayer = DataLinkLayer(5,5000)
    t1 = threading.Thread(target = datalinklayer.run)
    t2 = threading.Thread(target=datalinklayer.sendTo,args=("sample.txt","localhost",9000))
    t1.start()
    t2.start()

    t1.join()

    t2.join()

    
