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
#define PORT 8080 
#define MICROSECONDS 1000 // 1 seconds
using namespace std;
double time_diff( const clock_t start, const clock_t end )
{
	double time_taken = double(end - start) / double(CLOCKS_PER_SEC); 
    return time_taken;
}
int main(int argc, char const *argv[]) 
{ 
	int sock = 0, valread; 
	
	struct sockaddr_in serv_addr; 
	char buffer[1024] = {0}; 
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) //sock_stream(TCP) can be changed to sock_dgram(UDP)
	{ 
		printf("\n Socket creation error \n"); 
		return -1; 
	} 

	serv_addr.sin_family = AF_INET; 
	serv_addr.sin_port = htons(PORT); 
	
	// Convert IPv4 and IPv6 addresses from text to binary form 
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
	{ 
		printf("\nInvalid address/ Address not supported \n"); 
		return -1; 
	} 

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
	{ 
		printf("\nConnection Failed \n"); 
		return -1; 
	} 
	clock_t start_pac, end_pac;
	start_pac = clock();
	for (int i=0; i<=100; i++)
	{
	// preparing data packet
	string val = to_string(i);
	string final_str1 = " packet no:";
	final_str1.append(val);
	const char*final_str = final_str1.data(); 
	
	// Packet is prepared and waiting to send.	
	
	sleep(MICROSECONDS);
	
	//controller program starting counter	
	clock_t start_SR = clock();	
	send(sock , final_str , strlen(final_str) , 0 ); 
	end_pac = clock();
	cout << "packet_sent"<<final_str << endl;
	
	// Going to recieve the packet_sent	
	valread = read( sock, buffer, 1024);
	
	// packet comparison	
	if (*final_str != *buffer)
	{
		cout << "packets are not same"<<endl;
		continue;
	}
	
	//stop the clock
	clock_t end_SR = clock();
	
	// round trip time calculation	
	cout << " Round trip time of " << i << "is :" << time_diff(start_SR, end_SR) << endl;
	
	//between packet
	cout << " Between Packet " << i << "and " << i+1 << " is :" << time_diff(start_pac, end_pac) << endl;
	start_pac = end_pac; 
    
	}
    return 0; 
} 

