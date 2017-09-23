#include "Client.hpp"

Client::Client ( int fd, struct sockaddr_in	&in)
{
	this->fd = fd;
	this->in = in;

	std::string address = inet_ntoa(this->in.sin_addr);
	Tintin_reporter::instance()->log("New client connected from address: " + address + ":" + std::to_string(ntohs(this->in.sin_port)));
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
