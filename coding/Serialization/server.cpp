#include<iostream>
#include<cstring>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>

using namespace std;

struct Person{
	char name[50];
	int age;
};

//Struct used for network transmissionwith correct endianness
struct SerializedPerson{
	char name[50];
	uint32_t age; //Age stored in big-endian
};

int main(){

	int server_fd, client_fd;
	struct sockaddr_in server_addr, client_addr;
	socklen_t client_len = sizeof(client_addr);

	//Create Socket
	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd == -1){
		perror("Socket creation failed");
		return -1;
	}

	//Set up address
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(8080);

	// Bind Socket
	if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1){
		perror("Bind failed");
		return 1;
	}

	//Listen for connection
	if (listen(server_fd, 5) == -1){
		perror("Listen failed");
		return 1;
	}

	std::cout << "Server is listening on port 8080.. \n";

	//Accept connection
	client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
	if(client_fd == -1){
		perror("Accept failed");
		return 1;
	}

	//Receive serialized struct
	SerializedPerson received_data;
	int bytesReceived = recv(client_fd, &received_data, sizeof(SerializedPerson), 0);
	if (bytesReceived > 0){
		//Convert back from network byte order
		Person received_person;
		strcpy(received_person.name, received_data.name);
		received_person.age = ntohl(received_data.age); //Convert back to host order

		std::cout << "Received: " << received_person.name << ", " << received_person.age
			  << " years old" << endl;

	}else{
		perror("Receive failed");
	}

	close(client_fd);
	close(server_fd);
	return 0;
}
