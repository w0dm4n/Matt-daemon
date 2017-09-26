#ifndef SERVER_HPP
# define SERVER_HPP

# include "all.hpp"
# include <sys/socket.h>
# include <arpa/inet.h>
# include "Tintin_reporter.hpp"
# include "Client.hpp"
# include "Deamon_statistics.hpp"

class Server
{
	public:

		Server(int port);
		Server( Server const & src );
		virtual ~Server( void );

		Server &							operator=( Server const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, Server const & i);
		
		void				listenInit();
		void				waitClients();
		int					ClientsSocket();
		void				readClients();
		void				removeClient(Client *client);
		Deamon_statistics	*get_statistics( void );

		struct ServerCantCreateSocket : public std::exception {
			ServerCantCreateSocket() { Tintin_reporter::instance()->log("Exception raised: " + std::string(this->what())); }
			virtual const char* what() const throw() {
				return "The server cant create socket";
			}
		};

		struct ServerCantAllowMultipleConnectionOnSocket : public std::exception {
			ServerCantAllowMultipleConnectionOnSocket() { Tintin_reporter::instance()->log("Exception raised: " + std::string(this->what())); }
			virtual const char* what() const throw() {
				return "The server cant allow multiple connection on socket";
			}
		};

		struct ServerCantBindSocket : public std::exception {
			ServerCantBindSocket() { Tintin_reporter::instance()->log("Exception raised: " + std::string(this->what())); }
			virtual const char* what() const throw() {
				return "The server cant bind the socket";
			}
		};

		struct ServerCantListenOnSocket : public std::exception {
			ServerCantListenOnSocket() { Tintin_reporter::instance()->log("Exception raised: " + std::string(this->what())); }
			virtual const char* what() const throw() {
				return "The server cant listen on the socket";
			}
		};

		struct ServerCantAcceptSocket : public std::exception {
			ServerCantAcceptSocket() { Tintin_reporter::instance()->log("Exception raised: " + std::string(this->what())); }
			virtual const char* what() const throw() {
				return "The server cant accept socket !";
			}
		};

		struct ServerCantSelectOnFd : public std::exception {
			ServerCantSelectOnFd() { Tintin_reporter::instance()->log("Exception raised: " + std::string(this->what())); }
			virtual const char* what() const throw() {
				return "The server cant select on clients fd";
			}
		};
	private:
		int						listenPort;
		struct sockaddr_in		in;
		int						sock;
		std::vector<Client*>	clients;
		Deamon_statistics		*statistics;
};

#endif
