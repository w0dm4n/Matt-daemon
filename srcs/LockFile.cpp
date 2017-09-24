#include "LockFile.hpp"

LockFile::LockFile ()
{
	std::string filename = "/var/lock/matt_daemon.lock";
	this->fd = open(filename.c_str(), O_CREAT);
	if (this->fd > 0) {
		flock(fd, LOCK_EX);
	}
}

LockFile::LockFile ( LockFile const & src )
{
	*this = src;
	return ;
}

LockFile &				LockFile::operator=( LockFile const & rhs )
{
	if (this != &rhs)
	{

	}
	return (*this);
}

LockFile::~LockFile ( void )
{
	std::string filename = "/var/lock/matt_daemon.lock";
	if (this->fd) {
		unlink(filename.c_str());
    	flock(this->fd, LOCK_UN);
	}
}

std::ostream &				operator<<(std::ostream & o, LockFile const & i)
{
	(void)i;
	return (o);
}

std::string LockFile::getCurrentTime()
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
