#include "Daemon_statistics.hpp"

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

Daemon_statistics::Daemon_statistics ( void )
{
	this->initialize();
	return ;
}

Daemon_statistics::Daemon_statistics ( Daemon_statistics const & src )
{
	*this = src;
	return ;
}

Daemon_statistics &				Daemon_statistics::operator=( Daemon_statistics const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

Daemon_statistics::~Daemon_statistics ( void )
{
	return ;
}

// ###############################################################

// OVERLOAD OPERATOR #############################################

std::ostream &				operator<<(std::ostream & o, Daemon_statistics const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void	Daemon_statistics::update_start_time( void )
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	this->start_time = tv.tv_usec;
}

void	Daemon_statistics::update_end_time( void )
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	this->end_time = tv.tv_usec;
}

int		Daemon_statistics::get_number_of_message_received( void )
{
	return (this->number_of_message_received);
}

int		Daemon_statistics::get_number_of_connection_accepted( void )
{
	return (this->number_of_connection_accepted);
}

long	Daemon_statistics::get_start_time( void )
{
	return (this->start_time);
}

long	Daemon_statistics::get_end_time( void )
{
	return (this->end_time);
}

void	Daemon_statistics::set_number_of_message_received( int n )
{
	this->number_of_message_received = n;
}

void	Daemon_statistics::set_number_of_connection_accepted( int n )
{
	this->number_of_connection_accepted = n;
}

void	Daemon_statistics::set_start_time( long time )
{
	this->start_time = time;
}

void	Daemon_statistics::set_end_time( long time )
{
	this->end_time = time;
}


std::string	Daemon_statistics::to_string( void )
{
	time_t up_time = this->end_time - this->start_time;
	unsigned int days, hours, min, sec;

	up_time /= 60;
	days = static_cast<int>(up_time / (24*60*60*1000));
	up_time %= 24;
	hours = static_cast<int>(up_time / (60*60*1000));
	up_time %= 60;
	min = static_cast<int>(up_time / (60 * 1000));
	up_time %= 60;
	sec = static_cast<int>(up_time / 1000);

	std::ostringstream s;
	s << "\n-----------------------------------------------------------\n";
	s << "Deamon statistics :\n";
	s << "Total received message     : " << this->number_of_message_received << "\n";
	s << "Total connection accept    : " << this->number_of_connection_accepted << "\n";
	s << "Deamon total uptime        : " << days << "d";
	s << hours << "h" << min << "m" << sec << "s" << "\n";
	s << "-----------------------------------------------------------";
	return (s.str());
}

// ###############################################################

// GETTER METHOD #################################################

// ###############################################################

// SETTER METHOD #################################################

// ###############################################################

// PRIVATE METHOD ################################################

void						Daemon_statistics::initialize( void )
{
	this->number_of_message_received = 0;
	this->number_of_connection_accepted = 0;
	this->start_time = -1;
	this->end_time = -1;
}

// ###############################################################

// EXCEPTION METHOD ##############################################

// ###############################################################

// EXTERNAL ######################################################

// ###############################################################
