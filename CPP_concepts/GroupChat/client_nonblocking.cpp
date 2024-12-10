#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <thread>

#define PORT 8080

void setNonBlocking(int socket_fd){
	int flags = fcntl(socket_fd, F_GETFL, 0);
	fcntl(socket_fd, F_SETFL, flags | O_NONBLOCK);
}

void receiveMessages(int socket_fd){
	char buffer[1024];
	while(true){
		memset(buffer, 0, sizeof(buffer));
		int bytes_read = recv(socket_fd, buffer, sizeof(buffer), 0);
		if (bytes_read > 0){
			std::cout << "Server: " << buffer << std::endl;
		}
		usleep(100000);
	}
}

int main(){
	
	int client_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (client_socket == -1){
		perror("Socket creation failed");
		return 1;
	}

	sockaddr_in server_address{};
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(PORT);

	if(inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0){
		perror("Invalid address");
		return 1;
	}

	if(connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0){
		perror("Connection failed");
		return 1;
	}

	setNonBlocking(client_socket);
	std::cout << "Connected to the server. Type messages to send" << std::endl;

	std::thread receiver(receiveMessages, client_socket);
	receiver.detach();

	while(true){
		std::string message;
		std::getline(std::cin, message);
		send(client_socket, message.c_str(), message.size(), 0);
	}

	close(client_socket);
	return 0;
}
