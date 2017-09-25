#include "Client.hpp"
#include "daemon.hpp"
#include "Server.hpp"

Client::Client ( int fd, struct sockaddr_in	&in, Server *server)
{
	this->fd = fd;
	this->in = in;
	this->address = inet_ntoa(this->in.sin_addr);
	this->server = server;

	Tintin_reporter::instance()->log("New client connected from address: " + this->getAddress() + ":" + std::to_string(ntohs(this->in.sin_port)));
	std::thread thread(Client::clientThread, this);
	thread.detach();
}

std::string Client::getAddress()
{
	return this->address;
}

Client::Client ( Client const & src )
{
	*this = src;
	return ;
}

Client &				Client::operator=( Client const & rhs )
{
	if (this != &rhs)
	{
	}
	return (*this);
}

Client::~Client ( void )
{
	return ;
}

std::ostream &				operator<<(std::ostream & o, Client const & i)
{
	(void)i;
	return (o);
}

void Client::clientThread(Client *client)
{
	char buffer[CLIENT_BUFFER];
	int res = 0;
	while (true)
	{
		res = recv(client->fd, buffer, CLIENT_READ, 0);
		std::string data = buffer;
		if (data[data.size() - 1] == '\n')
			data[data.size()- 1] = '\0';
		if (res) {
			if (!strcmp(data.c_str(), "quit")) {
				LockFile *lockFile = Daemon::getLockFile();
				if (lockFile) {
					delete lockFile;
				}
				Tintin_reporter::instance()->log("Received a quit command from (" + client->getAddress() + ":" + std::to_string(ntohs(client->in.sin_port)) + ") and exited the daemon..");
				exit (0);
			} else {
				Tintin_reporter::instance()->log("Received from (" + client->getAddress() + ":" + std::to_string(ntohs(client->in.sin_port)) + "): " + data);
			}
			memset(&buffer, 0, CLIENT_READ);
		} else if (res <= 0) {
			client->server->removeClient(client);
			Tintin_reporter::instance()->log("(" + client->getAddress() + ":" + std::to_string(ntohs(client->in.sin_port)) + ") disconnected from the daemon");
			break;
		}
	}
}
