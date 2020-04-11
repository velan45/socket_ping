// Client side C/C++ program to demonstrate Socket programming 
#include <bits/stdc++.h> 
#include<iostream>
#include <stdlib.h>
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include<string>
#include <chrono>
#define PORT 8081 //client port no 
#define MICROSECONDS 10000 // microseconds 
using namespace std;

int main(int argc, char const *argv[]) 
{ 
	int sock = 0, valread;
	
	struct sockaddr_in servaddr, cliaddr; 
	//char *hello = "Hello from client";
	char buffer[1024] = {0}; 
	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) //sock_stream(TCP) can be changed to sock_dgram(UDP)
	{ 

		cout << "Socket creation error"<<endl;
		return -1; 
	} 
	memset(&servaddr,0,sizeof(sockadr_in));
	memset(&cliaddr, 0 , sizeof(sockaddr_in));
	cliaddr.sin_family = AF_INET; 
	cliaddr.sin_port = htons(PORT); 
	cliaddr.sin_addr.s_addr = INADDR_LOOPBACK; //ip address of 127.0.0.1
	
	// Convert IPv4 and IPv6 addresses from text to binary form 
	/*if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
	{ 
		cout << "Invalid address/ Address not supported"<<endl;
		//printf("\nInvalid address/ Address not supported \n"); 
		return -1; 
	} 

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
	{ 
		cout << "connection failed"<<endl; 
		return -1; 
	} */
	
	
	if(bind(sock, (struct sockaddr_in*) &cliaddr, sizeof(struct sockaddr_in)) == -1)
	{
		
		cout << " bind failed " << endl;
	}
	std::chrono::time_point<std::chrono::high_resolution_clock> start_pac, end_pac;
	start_pac = std::chrono::high_resolution_clock::now();

	socklen_t len;
	len = sizeof(struct sockaddr_in);

	for (int i=0; i<=10; i++)
	{
	// preparing data packet
	string val = to_string(i);
	string final_str1 = " packet no:";
	final_str1.append(val);
	const char*final_str = final_str1.data(); 
	
	// Packet is prepared and waiting to send.	
	
	usleep(MICROSECONDS);
	int n;
	
	//controller program starting counter	
	auto start_SR = std::chrono::high_resolution_clock::now();

	sendto(sock, final_str, strlen(final_str), 
        MSG_CONFIRM, (struct sockaddr_in *) &servaddr, sizeof(sockaddr_in));	

	//send(sock , final_str , strlen(final_str) , 0 ); 
	
	cout << "packet_sent"<<final_str << endl;
	
	// Going to recieve the packet_sent	
	n = recvfrom(sock, (char *)buffer,1024,  
                MSG_WAITALL, ( struct sockaddr *) &servaddr, 
                &len);  
 
	//valread = read( sock, buffer, 1024);
	
	// packet comparison	
	if (*final_str != *buffer)
	{
		cout << "packets are not same"<<endl;
		continue;
	}
	
	//stop the clock
	auto end_SR = std::chrono::high_resolution_clock::now();
	
	// round trip time calculation	
	auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>( end_SR - start_SR ).count();
	cout << " Round trip time of " << i << "is :" << float(duration1) / 1000 << " miliseconds"  << endl;
	
	//between packet
		
	
	end_pac = std::chrono::high_resolution_clock::now(); 
    auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>( end_pac - start_pac ).count();
	cout << " Between Packet " << i << "and " << i+1 << " is :" << float(duration2) / 1000  << " miliseconds" << endl;
	start_pac = end_pac;
	
	}
    return 0; 
} 

