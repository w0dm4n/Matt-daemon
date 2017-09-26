#include "Tintin_reporter.hpp"

Tintin_reporter::Tintin_reporter ()
{
}

Tintin_reporter::Tintin_reporter ( Tintin_reporter const & src )
{
	*this = src;
	return ;
}

Tintin_reporter &				Tintin_reporter::operator=( Tintin_reporter const & rhs )
{
	if (this != &rhs)
	{

	}
	return (*this);
}

Tintin_reporter::~Tintin_reporter ( void )
{
	return ;
}

std::ostream &				operator<<(std::ostream & o, Tintin_reporter const & i)
{
	(void)i;
	return (o);
}

std::string Tintin_reporter::getCurrentTime()
{
	time_t rawtime;
	struct tm *timeinfo;
	char buffer[80];

	time (&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buffer,sizeof(buffer),"%d-%m-%Y %I:%M:%S", timeinfo);
	std::string str(buffer);
	return (buffer);
}

long 	Tintin_reporter::getCurrentTimeMillis()
{
	 struct timeval tv;

	 gettimeofday(&tv, NULL);
	 return (tv.tv_usec);
}

void	Tintin_reporter::log(std::string message)
{
	std::fstream file;
	std::string filename = "/var/log/matt_daemon/matt_daemon.log";
	file.open(filename.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);
	if (file.is_open()) {
		file << "[" << this->getCurrentTime() << "]: " << message << "\n";
	}
}

bool	Tintin_reporter::initLogs()
{
	if (!boost::filesystem::exists("/var/log/matt_daemon/")) {
	    bool res = boost::filesystem::create_directory("/var/log/matt_daemon/");
		if (!res) {
			throw CantCreateLogFolder();
			return false;
		}
	}
	std::fstream file;
	std::string filename = "/var/log/matt_daemon/matt_daemon.log";
	file.open(filename.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);
	if (!file.is_open())
	{
		throw CantOpenLogFile();
		return false;
	} else
		file.close();
	return true;
}
