#include "Client.hpp"
#include "daemon.hpp"

Client::Client ( int fd, struct sockaddr_in	&in)
{
	this->fd = fd;
	this->in = in;

	this->address = inet_ntoa(this->in.sin_addr);
	Tintin_reporter::instance()->log("New client connected from address: " + this->address + ":" + std::to_string(ntohs(this->in.sin_port)));

	std::thread thread(Client::clientThread, this);
	thread.detach();
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
				exit (0);
			} else {
				Tintin_reporter::instance()->log("Received from (" + client->address + ":" + std::to_string(ntohs(client->in.sin_port)) + "): " + data);
			}
			memset(&buffer, 0, CLIENT_READ);
		}
	}
}
