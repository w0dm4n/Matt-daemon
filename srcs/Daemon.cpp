#include "Daemon.hpp"

Daemon::Daemon ()
{
	Tintin_reporter *instance = Tintin_reporter::instance();
	this->logger = *instance;
}

Daemon::Daemon ( Daemon const & src )
{
	*this = src;
	return ;
}

Daemon &				Daemon::operator=( Daemon const & rhs )
{
	if (this != &rhs)
	{
	}
	return (*this);
}

Daemon::~Daemon ( void )
{
	return ;
}

std::ostream &				operator<<(std::ostream & o, Daemon const & i)
{
	(void)i;
	return (o);
}

void	Daemon::startDaemon()
{
	LockFile lock(true);
	Server	server(4242);
	int		current_pid = getpid();

	this->logger.log("Daemon started with PID " + std::to_string(current_pid));
	server.listenInit();
}

void	Daemon::initFork()
{
	pid_t	pid = fork();
	if (pid == 0) {
		this->startDaemon();
	} else if (pid < 0) {
		throw DaemonForkFailed();
	}
}

void	Daemon::init()
{
	if (!this->DaemonStarted()) {
		if (logger.initLogs()) {
			this->logger.log("Starting the daemon...");
			this->initFork();
		}
	}
}

bool	Daemon::DaemonStarted()
{
	DIR					*dir;
	struct dirent		*ent;
	int					current_pid = getpid();

	if ((dir = opendir ("/proc")) != NULL) {
	  while ((ent = readdir (dir)) != NULL) {
		  int pid = atoi(ent->d_name);
		  if (pid > 0 && pid != current_pid) {
			  ProcReader reader("/proc/" + std::string(ent->d_name));
			  if (reader.comm.length() && strstr(reader.comm.c_str(), "Matt_daemon")
		  		|| reader.cmdLine.length() && strstr(reader.cmdLine.c_str(), "Matt_daemon")) {
					LockFile lock(false);
					lock.logAttempt();
					throw DaemonAlreadyRunning();
					return false;
			  }
			}
	  }
	  closedir (dir);
	} else {
		throw DaemonCantReadProcFolder();
		return false;
	}
	return false;
}
