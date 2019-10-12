import threading
import time

def function1():
    global semaphore
    print(f"{threading.current_thread().ident}")
    while semaphore:
        print("counting. . .")
        time.sleep(1)
    print("Thread 2 Waked up !")

def function2():
    global semaphore
    print(f"{threading.current_thread().ident}")
    time.sleep(10)
    semaphore = False




if __name__ == "__main__":
    semaphore = True

    t1 = threading.Thread(target = function1)
    t2 = threading.Thread(target = function2)

    t1.start()
    t2.start()

    t1.join()
    t2.join()