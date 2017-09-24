#ifndef CLIENT_HPP
# define CLIENT_HPP

#include "all.hpp"
#include "Tintin_reporter.hpp"
# include <sys/socket.h>
# include <arpa/inet.h>
# include "LockFile.hpp"

# define CLIENT_BUFFER 4096
# define CLIENT_READ 4095
class Client
{
	public:

		Client( int fd, struct sockaddr_in	&in);
		Client( Client const & src );
		virtual ~Client( void );
		static void clientThread(Client *client);

		Client &							operator=( Client const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, Client const & i);
		int 					fd;
	private:
		std::string				address;
		struct sockaddr_in		in;
};

#endif
