// ------------------------------------------------------------	//
//																//
//																//
// ------------------------------------------------------------	//

#ifndef DAEMON_STATISTICS_HPP
# define DAEMON_STATISTICS_HPP

# include "all.hpp"
# include <sys/time.h>

class Daemon_statistics
{
	public:

		Daemon_statistics( void );
		Daemon_statistics( Daemon_statistics const & src );
		virtual ~Daemon_statistics( void );

		Daemon_statistics &				operator=( Daemon_statistics const & rhs );
		friend std::ostream &			operator<<(std::ostream & o, Daemon_statistics const & i);

		void		update_start_time( void );
		void		update_end_time( void );
		int			get_number_of_message_received( void );
		int			get_number_of_connection_accepted( void );
		long		get_start_time( void );
		long		get_end_time( void );
		void		set_number_of_message_received( int n );
		void		set_number_of_connection_accepted( int n );
		void		set_start_time( long time );
		void		set_end_time( long time );
		std::string	to_string( void );

	private:
	// PRIVATE METHOD ################################################
		void	initialize( void );
	// PRIVATE VARIABLES ################################################
		int		number_of_message_received;
		int		number_of_connection_accepted;
		time_t	start_time;
		time_t	end_time;
};

#endif
