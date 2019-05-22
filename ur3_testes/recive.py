import socket
import csv
HOST = '192.168.1.63'  # Endereco IP do Servidor
PORT = 5000            # Porta que o Servidor esta
tcp = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
orig = (HOST, PORT)
tcp.bind(orig)
tcp.listen(1)
tempo = 0.0
with open('meu_arquivo.csv', 'w') as csvfile:
        fieldnames = ['tempo','largura']
        writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
        writer.writeheader()
        
        con, cliente = tcp.accept()
        print 'Concetado por', cliente
        while True:
            msg = con.recv(8)
            if not msg: break
           #print 'tempo', tempo, 'largura',msg
            print('tempo = {0:10f} largura = {1:10f}'.format(tempo, float(msg)))
  
            writer.writerow({'tempo': str(tempo), 'largura': str(msg) })
            tempo = tempo + 0.008
        print 'Finalizando conexao do cliente', cliente
        con.close()