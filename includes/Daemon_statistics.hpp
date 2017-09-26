// ------------------------------------------------------------	//
//																//
//																//
// ------------------------------------------------------------	//

#ifndef DAEMON_STATISTICS_HPP
# define DAEMON_STATISTICS_HPP

class Daemon_statistics
{
	public:
	
		Daemon_statistics( void );
		Daemon_statistics( Daemon_statistics const & src );
		virtual ~Daemon_statistics( void );

		Daemon_statistics &				operator=( Daemon_statistics const & rhs );
		friend std::ostream &			operator<<(std::ostream & o, Daemon_statistics const & i);

		int		get_number_of_message_received( void );
		int		get_number_of_connection_accepted( void );
		long	get_start_time( void );
		long	get_end_time( void );
		void	set_number_of_message_received( int n );
		void	set_number_of_connection_accepted( int n );
		void	set_start_time( long time );
		void	set_end_time( long time );

	private:
	// PRIVATE METHOD ################################################
		void	initialize( void );
	// PRIVATE VARIABLES ################################################
		int		number_of_message_received;
		int		number_of_connection_accepted;
		long	start_time;
		long	end_time;
};

#endif
