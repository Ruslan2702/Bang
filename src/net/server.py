import socket

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.bind(('127.0.0.1', 9999))
sock.listen(1)
conn, addr = sock.accept()

print('connected:', addr)

while True:
    # conn.send("You are here".encode())
    conn.send('{"count_bandits":2,"count_sherifs_helpers":3,"is_end":false,"player_list":[{"player0":{"cards_in_hand":[null],"hp":4,"is_dead":false,"max_hp":0,"name":"BOB","position":0,"range":1,"role":""}},{"player1":{"cards_in_hand":[null],"hp":2,"is_dead":false,"max_hp":0,"name":"ANN","position":0,"range":1,"role":""}},{"player2":{"cards_in_hand":[null],"hp":3,"is_dead":false,"max_hp":0,"name":"KATE","position":0,"range":1,"role":""}},{"player3":{"cards_in_hand":[null],"hp":1,"is_dead":false,"max_hp":0,"name":"TOM","position":0,"range":1,"role":""}},{"player4":{"cards_in_hand":[null],"hp":4,"is_dead":false,"max_hp":0,"name":"JOHN","position":0,"range":1,"role":""}},{"player5":{"cards_in_hand":[["[BANG]","[MISS]","[MISS]","[BEER]"]],"hp":3,"is_dead":false,"max_hp":0,"name":"BILL","position":0,"range":5,"role":"BANDIT"}}],"renigan_alive":true,"sherif_alive":true,"winner":""}'.encode())
    # data = conn.recv(1024)
    # if not data:
    	# break

    # print(data)
    # conn.send("You are here".encode())
	# conn.send(data.upper())


conn.close()