#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include<vector>
#include<pthread.h>
#include<iostream>
#include<set>
#define PORT 8080
using namespace std;

pthread_t thread;
set<int> clients;
set<int> Terminated;
int i = 0;
int server_fd, valread;
sockaddr_in address;
int opt = 1;
int addrlen = sizeof(address);
bool terminate = false;


void* ClientFunction(void *args){
	cout << "New player added \n";
	cout << "Total player's : " << clients.size() << "\n";
	int *socketPointer =  (int*) args;
	int newSocket = *socketPointer;
	while (true){
		char buffer[1024] ={0};
		valread = read(newSocket, buffer, 1024);
		string val(buffer);
		string s(val.begin(), val.end());
		
		for (int x: clients){
			if (x == newSocket || Terminated.find(x) != Terminated.end()) continue;
           
			send(x, s.c_str(), strlen(s.c_str()), 0);
		}
		if (val == "please_exit") {
           
			Terminated.insert(newSocket);
            
			return NULL;
		}
	}
	return NULL;
}

int main(int argc, char const* argv[])
{
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0))
		== 0) {
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	
	if (setsockopt(server_fd, SOL_SOCKET,
				SO_REUSEADDR | SO_REUSEPORT, &opt,
				sizeof(opt))) {
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	
	if (bind(server_fd, (struct sockaddr*)&address,
			sizeof(address))
		< 0) {
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	
	while (true){
		if (listen(server_fd, 3) < 0) {
			perror("listen");
			exit(EXIT_FAILURE);
		}
		int newSocket;
		if ((newSocket = accept(server_fd, (struct sockaddr*)&address,(socklen_t*)&addrlen))< 0) {
			perror("accept");
			exit(EXIT_FAILURE);
		}
		pthread_create(&thread, NULL, ClientFunction, (void*)(&newSocket));
		clients.insert(newSocket);
	}
	return 0;
}
