#include "Server.hpp"

Server::Server (int port)
{
	this->listenPort = port;
}

Server::Server ( Server const & src )
{
	*this = src;
	return ;
}

Server &				Server::operator=( Server const & rhs )
{
	if (this != &rhs)
	{
	}
	return (*this);
}

Server::~Server ( void )
{
	return ;
}

std::ostream &				operator<<(std::ostream & o, Server const & i)
{
	(void)i;
	return (o);
}

void Server::waitClients()
{
	int 					fd = 0;
	struct sockaddr_in		in;
	socklen_t				length = sizeof(in);

	while (true)
	{
		if ((fd = accept(this->sock, (struct sockaddr*)&in, &length)) == -1)
			throw ServerCantAcceptSocket();
		else {
			this->clients.push_back(Client(fd, in));
		}
	}
}

void Server::listenInit()
{
	bool opt = true;
	if ((this->sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		throw ServerCantCreateSocket();
	this->in.sin_family = AF_INET;
	this->in.sin_addr.s_addr = INADDR_ANY;
	this->in.sin_port = htons(this->listenPort);
	/*if ((setsockopt(this->sock, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, \
		sizeof(opt))) < 0)
		throw ServerCantAllowMultipleConnectionOnSocket();*/
	if ((bind(this->sock, (struct sockaddr *)&this->in, \
			sizeof(this->in))) < 0)
		throw ServerCantBindSocket();
	if ((listen(this->sock, 3)) == -1)
		throw ServerCantListenOnSocket();
	Tintin_reporter::instance()->log("Server started on port " + std::to_string(this->listenPort));
	this->waitClients();
}
