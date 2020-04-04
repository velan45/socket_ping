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
using namespace std;
int main(int argc, char const *argv[]) 
{ 
	int sock = 0, valread; 
	unsigned int microseconds = 1000;
	struct sockaddr_in serv_addr; 
	char *hello = "Hello from client"; 
	char buffer[1024] = {0}; 
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
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
	clock_t start, end;
	for (int i=0; i<=100; i++)
	{
		string val = to_string(i);
		string final_str1 = " packet no:";
		final_str1.append(val);
		const char*final_str = final_str1.data(); 
		
    send(sock , final_str , strlen(final_str) , 0 ); 
	start = clock();
	cout << "packet_sent"<<endl;
	valread = read( sock, buffer, 1024);
	if (*final_str != *buffer)
	{
		cout << "packets are not same"<<endl;
		continue;
	}
	usleep(microseconds);
	end = clock();
	double time_taken = double(end - start) / double(CLOCKS_PER_SEC); 
    cout << "Time taken by program is : " << fixed  
         << time_taken << end; 
    cout << " sec " << endl;
   
	}

    return 0; 
 
	
} 

