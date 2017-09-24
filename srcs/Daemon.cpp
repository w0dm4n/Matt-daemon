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

LockFile *Daemon::getLockFile()
{
	static LockFile *lock;

	if (!lock){
		lock = new LockFile();
	}
}

void	Daemon::handleSignal(int signal)
{
	LockFile *lockFile = Daemon::getLockFile();
	Tintin_reporter::instance()->log("Received signal " + std::to_string(signal) + " and exited the daemon..");

	if (lockFile) {
		delete lockFile;
	}
	exit(signal);
}

void	Daemon::startDaemon()
{
	Server	server(4242);
	int		current_pid = getpid();
	LockFile *lockFile = Daemon::getLockFile();

	chdir("/");
	this->logger.log("Daemon started with PID " + std::to_string(current_pid));
	for (int i = 1 ; i < _NSIG; i++)
		signal(i, Daemon::handleSignal);
	server.listenInit();
}

void	Daemon::initFork()
{
	pid_t	pid = fork();
	if (pid == 0) {
		int sid = setsid();
		if (sid > 0) {
			pid_t new_pid = fork();
			if (new_pid == 0) {
				this->startDaemon();
			} else if (new_pid > 0) {
				exit(0);
			}
		} else {
			throw DaemonCantDetachProcess();
		}
	} else if (pid < 0) {
		throw DaemonForkFailed();
	} else {
		exit (0);
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
	bool				process_running = false;

	if ((dir = opendir ("/proc")) != NULL) {
	  while ((ent = readdir (dir)) != NULL) {
		  int pid = atoi(ent->d_name);
		  if (pid > 0 && pid != current_pid) {
			  ProcReader reader("/proc/" + std::string(ent->d_name));
			  if (reader.comm.length() && strstr(reader.comm.c_str(), "Matt_daemon")
		  		|| reader.cmdLine.length() && strstr(reader.cmdLine.c_str(), "Matt_daemon")) {
					process_running = true;
			  }
			}
	  }
	  closedir (dir);
	} else {
		throw DaemonCantReadProcFolder();
		return true;
	}
	if (boost::filesystem::exists("/var/lock/matt_daemon.lock") || process_running) {
		throw DaemonAlreadyRunning();
		return true;
	}
	return false;
}
