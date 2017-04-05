A system for two peers and a single file information server. The design details are as follows.
1. A File Information Server (FIS). The FIS maintains a table
that has information about all the peers’ IP addresses and the files available to
those peers.
2. A server and client processes at the individual peers.
The communication protocol between the peers and between a peer and the FIS
is as follows.
a. Peer A wants to download a file named abc.pdf. The file is available at
Peer B.
b. Peer A communicates with the FIS to get the details of Peer B
c. Then Peer A communicates with Peer B to download the file abc.pdf.
d. The communication between a peer and the FIS is through Datagram
sockets.
e. The communication between two peers is through stream sockets.

It can be used for a system for N number of
peers, where N can be any number. In this scenario, a single peer can have multiple files.
Note that, the FIS can receive simultaneous requests from multiple peers. Similarly, a
single peer may receive file download requests from multiple other peers.


==============How to use============

1. In file FIS_Server.c add file name in the file array.
2. Add server-ip in the ip array (can be multiple servers)
3. In the client add server ip and port and enter the name of file you need to download.
