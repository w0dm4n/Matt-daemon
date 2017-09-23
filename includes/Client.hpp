#ifndef CLIENT_HPP
# define CLIENT_HPP

#include "all.hpp"
#include "Tintin_reporter.hpp"
# include <sys/socket.h>
# include <arpa/inet.h>

class Client
{
	public:

		Client( int fd, struct sockaddr_in	&in);
		Client( Client const & src );
		virtual ~Client( void );

		Client &							operator=( Client const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, Client const & i);
	private:
		int 					fd;
		struct sockaddr_in		in;
};

#endif
