file = open("fileHandling.txt","rb")
binary_string = bytearray()
for i in file:
    binary_string.extend(i)
#print(binary_string)
for i in binary_string:
    print(i)
file.close()
file = open("fileHandling_2.txt","wb")
file.write(binary_string)
