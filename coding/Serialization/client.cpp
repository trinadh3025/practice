#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

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
	int sock_fd;
	struct sockaddr_in server_addr;

	//Create socket
	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_fd == -1){
		perror("Socket creation failed");
		return 1;
	}

	//Set up server address
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(8080);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //localhost
	
	//Connect to server
	if (connect(sock_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1){
		perror("Connection failed");
		return 1;
	}

	// Prepare struct data
	Person p;
	strcpy(p.name, "Alice");
	p.age = 25;

	//Convert to network byte order
	SerializedPerson data_to_send;
	strcpy(data_to_send.name, p.name);
	data_to_send.age = htonl(p.age); //Convert age to big-endian
	
	// Send struct data
	if (send(sock_fd, &data_to_send, sizeof(SerializedPerson), 0) == -1){
		perror("Send failed");
	}else{
		std::cout << "Sent: " << p.name << ", " << p.age << " years old" << endl;
	}

	close(sock_fd);
	return 0;
}

