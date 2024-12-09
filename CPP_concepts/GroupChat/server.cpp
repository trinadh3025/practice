#include<iostream>
#include<thread>
#include<vector>
#include<string>
#include<mutex>
#include<cstring>
#include<unistd.h>
#include<arpa/inet.h>

#define PORT 8080

std::mutex client_mutex;
std::vector<int> client_sockets;

void broadcastMessage(const std::string &message){
	std::lock_guard<std::mutex> lock(client_mutex);
	for(int sock : client_sockets){
		send(sock, message.c_str(), message.size(), 0);
	}
}

void handleClient(int client_socket){
	char buffer[1024];
	while(true){
		memset(buffer, 0, sizeof(buffer));
		int bytes_read = recv(client_socket, buffer, sizeof(buffer), 0);
		if (bytes_read <= 0){
			std::lock_guard<std::mutex> lock(client_mutex);
			for(auto it = client_sockets.begin(); it!=client_sockets.end(); it++){
				if (*it == client_socket) {
					client_sockets.erase(it);
					break;
				}
			}
			//client_sockets.erase(std::remove(client_sockets.begin(), client_sockets.end(), client_socket), client_sockets.end(),client_socket);
			close(client_socket);
			break;
		}
		std::string message = std::string(buffer);
		broadcastMessage("Client: " + std::to_string(client_socket) + ": " + message);
	}
}
int main(){
	
	int server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(server_fd == 0){
		perror("Socket failed");
		exit(EXIT_FAILURE);
	}

	sockaddr_in address{};
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0){
		perror("Bind failed");
		exit(EXIT_FAILURE);
	}

	if(listen(server_fd, 3) < 0){
		perror("Listen failed");
		exit(EXIT_FAILURE);
	}

	std::cout << "Server started, waiting for clients...\n" << std::endl;

	while(true){
		sockaddr_in client_address;
		socklen_t client_len = sizeof(client_address);
		int client_socket = accept(server_fd, (struct sockaddr *)&client_address, &client_len);
		if(client_socket < 0){
			perror("Accept failed");
			exit(EXIT_FAILURE);
			continue;
		}

		{
			std::lock_guard<std::mutex> lock(client_mutex);
			client_sockets.push_back(client_socket);

		}

		std::cout << "Client connected: " << client_socket << std::endl;

		if(client_sockets.size() == 2){
			broadcastMessage("Chat session started! Type messages");
		}

		std::thread(handleClient, client_socket).detach();
	
	}

	close(server_fd);
	return 0;
}
