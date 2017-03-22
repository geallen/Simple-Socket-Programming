/* GAMZE SEN 
	Body Mass Index Calculator
	How to run : gcc server.c -o server1
				./server1 port  
				gcc client.c -o client1
				./client1 IP port
				*/
#include <math.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>

#define MAXBUF 1024
int main(int argc, char* argv[])
{
int udpSocket;
int returnStatus = 0;
int addrlen = 0;
int y =100;
float z;
float height;
float weight;
float  ycc;
float bmi; // bmi is for body mass index
struct sockaddr_in udpServer, udpClient;
int buf[MAXBUF];
int buf2[MAXBUF];
char buf3[MAXBUF];
if (argc < 2)
{
fprintf(stderr, "Usage: %s <port>\n", argv[0]);
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
udpServer.sin_family = AF_INET;
udpServer.sin_addr.s_addr = htonl(INADDR_ANY);
udpServer.sin_port = htons(atoi(argv[1]));
returnStatus = bind(udpSocket, (struct sockaddr*)&udpServer,
sizeof(udpServer));
if (returnStatus == 0) {
fprintf(stderr, "Bind completed!\n");
}
else {
fprintf(stderr, "Could not bind to address!\n");
close(udpSocket);
exit(1);
}
while (1)
{
addrlen = sizeof(udpClient);
returnStatus = recvfrom(udpSocket, buf, MAXBUF, 0,(struct sockaddr*)&udpClient, &addrlen);
if (returnStatus == -1) {
fprintf(stderr, "Could not receive message first!\n");
}
else {

weight = (float)buf[0];
returnStatus = recvfrom(udpSocket, buf2, MAXBUF, 0,(struct sockaddr*)&udpClient, &addrlen);
if (returnStatus == -1) {
fprintf(stderr, "Could not receive message second!\n");
}
else {

height = (float) buf2[0]/ y;
printf("%.2f\n",height);
ycc = (float)(((int)(height * 100.0f) / 100.0f));
printf("%f\n",ycc);
height = ycc*ycc;
bmi = weight/ height;
printf("%f\n",bmi);

   if(bmi<18.5){
   		strcpy(buf3,"underweight");
   }
   else if(bmi>18.5 && bmi<24.9){
   		strcpy(buf3,"normal weight");
   }
   else if(bmi>24.9 && bmi<29.9){
   		strcpy(buf3,"overweight");
   }
   else if(bmi>29.9 && bmi<34.9){
   		strcpy(buf3,"first degree fat");
   }
   else if(bmi>34.9 && bmi<39.9){
   		strcpy(buf3,"second degree fat");
   }
   else{
   		strcpy(buf3,"obesity");
   }

returnStatus = sendto(udpSocket, buf3, sizeof(buf3)+1, 0,
(struct sockaddr*)&udpClient,
sizeof(udpClient));
if (returnStatus == -1) {
fprintf(stderr, "Could not send confirmation!\n");
}
else {
printf("Confirmation sent.\n");
}
}
}
}

close(udpSocket);
return 0;
}
