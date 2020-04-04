// Client side C/C++ program to demonstrate Socket programming 
#include <iostream> 
#include <Winsock2.h>
//#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include <ctime>
#include <cmath>
#include <bits/stdc++.h> 
//#include <time.h>
#define PORT 8080 
using namespace std;
   
int main(int argc, char const *argv[]) 
{ 
	    // clock_t start, end;
	//double cpu_time_used;
	float x, y;
	clock_t time_req;

    int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
    char *hello = " packet from client"; 
    char buffer[1024] = {0}; 
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
	cout << "socket creation error"<<endl;
      //  printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       

    if(inet_ntoa(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
    { 

        return -1; 
    } 
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 

        return -1; 
    } 
	clock_t start, end;
	for (int i=0; i<=100; i++)
	{
		auto val = std::to_string(i);
		char *final_str;
		final_str = (char*) malloc(sizeof(hello) + sizeof(char));
		final_str = hello + val ;
		
    send(sock , final_str , strlen(final_str) , 0 ); 
	start = clock();
	cout << "packet_sent"<<endl;
	valread = read( sock, buffer, 1024);
	if (*final_str != *buffer)
	{
		cout << "packets are not same"<<endl;
		continue;
	}
	end = clock();
	double time_taken = double(end - start) / double(CLOCKS_PER_SEC); 
    cout << "Time taken by program is : " << fixed  
         << time_taken << end; 
    cout << " sec " << endl; 
	
	/*cout << "sending client time"<<endl;
     //time function_____________
        
        time_req = clock();
	for (int i = 0; i<100000; i++)
	{
		y = log(i*i*i*i*i);
	}

        //start = clock();
	//cout << "start" << start << endl;

	cout << "Hello message sent"<<endl;

    valread = read( sock , buffer, 1024); 
        time_req = clock() - time_req;
	//end = clock();
	/*cout << "end" << end << endl;
		cpu_time_used = end - start;
	cout <<"time"<< cpu_time_used<<endl;

	cout << buffer << endl;
cout << "Without using pow function, it took " << (float)time_req / CLOCKS_PER_SEC << " seconds" << endl;
	system("pause"); */
	free(final_str);
	}

    return 0; 
} 