import sys
import threading
from DLL import DataLinkLayer









if __name__ == "__main__":

    datalinklayer = DataLinkLayer(2,9000)
    t1 = threading.Thread(target= datalinklayer.run)

    t1.start()
    print("Running...")
    t1.join()
