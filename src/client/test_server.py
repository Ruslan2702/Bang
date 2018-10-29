import socket
 
HOST = '127.0.0.1'
PORT = 5555 
 
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print('Socket created')

s.bind((HOST, PORT))
print('Socket bind complete')

s.listen(11)
print('Socket now listening')
 
while True:
    conn, addr = s.accept()
    print('Connected with ' + addr[0] + ':' + str(addr[1]))
    data = conn.recv(1024)
    if not data:
    	break
    else:
    	print(data)
     
s.close()