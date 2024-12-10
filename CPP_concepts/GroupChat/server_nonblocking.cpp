#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>
#include <arpa/inet.h>

#define PORT 8080

void setNonBlocking(int socket_fd){
	int flags = fcntl(socket_fd, F_GETFL, 0);
	fcntl(socket_fd, F_SETFL, flags | O_NONBLOCK);
}

int main(){
	
	int server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(server_fd == -1){
		perror("Socket creation failed");
		return 1;
	}

	sockaddr_in address{};
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0){
		perror("Bind failed");
		return 1; 
	}

	if (listen(server_fd, 5) < 0){
		perror("Listen failed");
		return 1;
	}

	setNonBlocking(server_fd);

	std::cout << "Server started on port " << PORT << std::endl;

	std::vector<int> clients;
	fd_set read_fds;

	while(true){
		FD_ZERO(&read_fds);
		FD_SET(server_fd, &read_fds);
		int max_fd = server_fd;

		// Add client sockets to the read_fds set
		for(int client_fd : clients){
			FD_SET(client_fd, &read_fds);
			max_fd = std::max(max_fd, client_fd);
		}

		//wait for activity on any socket
		int activity = select(max_fd+1, &read_fds, nullptr, nullptr, nullptr);
		if (activity < 0){
			perror("Select error");
			continue;
		}

		//check for new connections
		if (FD_ISSET(server_fd, &read_fds)){
			sockaddr_in client_address;
			socklen_t client_len = sizeof(client_address);
			int new_client = accept(server_fd, (struct sockaddr *)&client_address, &client_len);
			if(new_client >=0){
				setNonBlocking(new_client);
				clients.push_back(new_client);
				std::cout << "New client connected: " << new_client << std::endl;
			}

		}

		char buffer[1024];
		for(auto it = clients.begin(); it != clients.end();){
			int client_fd = *it;
			if (FD_ISSET(client_fd, &read_fds)){
				memset(buffer, 0, sizeof(buffer));
				int bytes_read = recv(client_fd, buffer, sizeof(buffer), 0);
				if(bytes_read <= 0){
					std::cout << "Client disconnected:" << client_fd << std::endl;
					close(client_fd);
					it = clients.erase(it);
					continue;
				}
			}

			std::string message = std::string(buffer);
			std::cout << "Client : " << client_fd << ": " << message << std::endl;

			//broadcast message
			for(int other_client : clients){
				if (other_client != client_fd){
					send(other_client, message.c_str(), message.size(), 0);
				}
			}
			++it;
		}
	}

	close(server_fd);
	return 0;

}
