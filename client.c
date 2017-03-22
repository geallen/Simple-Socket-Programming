/* GAMZE SEN 
	Body Mass Index Calculator
	How to run : gcc server.c -o server1
				./server1 port 
				gcc client.c -o client1
				./client1 IP port
				*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#define MAXBUF 1024
int main(int argc, char* argv[])
{
int udpSocket;
int returnStatus;
int addrlen;
struct sockaddr_in udpClient, udpServer;
int buf[MAXBUF];
int buf2[MAXBUF];
char buf3[MAXBUF];
if (argc < 3)
{
fprintf(stderr, "Usage: %s <ip address> <port>\n", argv[0]);
exit(1);
}
udpSocket = socket(AF_INET, SOCK_DGRAM, 0);
if (udpSocket == -1)
{
fprintf(stderr, "Could not create a socket!\n");
exit(1);
}
else {
printf("Socket created.\n");
}
udpClient.sin_family = AF_INET;
udpClient.sin_addr.s_addr = INADDR_ANY;
udpClient.sin_port = 0;
returnStatus = bind(udpSocket, (struct sockaddr*)&udpClient,sizeof(udpClient));
if (returnStatus == 0) {
fprintf(stderr, "Bind completed!\n");
}
else {
fprintf(stderr, "Could not bind to address!\n");
close(udpSocket);
exit(1);
}
printf("Enter your weight :(As kilogram) \n");
scanf("%d",buf);
printf("Enter your height : (As centimeter) \n");
scanf("%d",buf2);
udpServer.sin_family = AF_INET;
udpServer.sin_addr.s_addr = inet_addr(argv[1]);
udpServer.sin_port = htons(atoi(argv[2]));
returnStatus = sendto(udpSocket, buf, sizeof(buf)+1, 0,(struct sockaddr*)&udpServer, sizeof(udpServer));
if (returnStatus == -1) {
fprintf(stderr, "Could not send message1!\n");
}
else {
returnStatus = sendto(udpSocket, buf2, sizeof(buf2)+1, 0,(struct sockaddr*)&udpServer, sizeof(udpServer));
if (returnStatus == -1) {
fprintf(stderr, "Could not send message2!\n");
}
else {
addrlen = sizeof(udpServer);
returnStatus = recvfrom(udpSocket, buf3, MAXBUF, 0,(struct sockaddr*)&udpServer, &addrlen);
if (returnStatus == -1) {
fprintf(stderr, "Did not receive confirmation!\n");
}
else {
buf[returnStatus] = 0;
printf("Your Result is : %s\n", buf3);
}
}
}

close(udpSocket);
return 0;
}
