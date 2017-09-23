#include "LockFile.hpp"

LockFile::LockFile ( bool deleteFile )
{
	this->deleteFile = deleteFile;
	std::string filename = "/var/lock/matt_daemon.lock";
	this->file.open(filename.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);
	this->file.close();
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
		// make stuff
	}
	return (*this);
}

LockFile::~LockFile ( void )
{
	if (this->deleteFile) {
		std::remove("/var/lock/matt_daemon.lock");
	}
	return ;
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

void	LockFile::logAttempt()
{
	std::string filename = "/var/lock/matt_daemon.lock";
	this->file.open(filename.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);
	if (this->file.is_open()) {
		this->file << "[" << this->getCurrentTime() << "]: " << "A daemon tried to run while an instance was already running !\n";
	}
}
