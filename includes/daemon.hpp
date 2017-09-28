/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daemon.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/23 16:44:24 by frmarinh          #+#    #+#             */
/*   Updated: 2017/09/23 16:44:29 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef DAEMON_HPP
# define DAEMON_HPP

#include "all.hpp"
#include "ProcReader.hpp"
#include "Tintin_reporter.hpp"
#include "LockFile.hpp"
#include "Server.hpp"
#include "Flags.hpp"

class Daemon
{
	public:
		static void							handleSignal(int signal);
		static LockFile*						getLockFile();
		static Server*							getServer(int port);
		static Flags*							getFlags(Flags *f);

		Daemon(Flags *flags);
		Daemon(Daemon const & src);
		virtual ~Daemon(void);

		Daemon &							operator=( Daemon const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, Daemon const & i);
		void			initFork();
		void			init();
		void			startDaemon();
		bool			DaemonStarted();

		struct DaemonCantReadProcFolder : public std::exception {
			DaemonCantReadProcFolder() { Tintin_reporter::instance()->log("Exception raised: " + std::string(this->what())); }
			virtual const char* what() const throw() {
				return "The daemon can't read the proc folder";
			}
		};

		struct DaemonForkFailed : public std::exception {
			DaemonForkFailed() { Tintin_reporter::instance()->log("Exception raised: " + std::string(this->what())); }
			virtual const char* what() const throw() {
				return "The daemon can't start a fork";
			}
		};

		struct DaemonAlreadyRunning : public std::exception {
			DaemonAlreadyRunning() { Tintin_reporter::instance()->log("Exception raised: " + std::string(this->what())); }
			virtual const char* what() const throw() {
				return "An instance of the daemon is already running";
			}
		};

		struct DaemonCantDetachProcess : public std::exception {
			DaemonCantDetachProcess() { Tintin_reporter::instance()->log("Exception raised: " + std::string(this->what())); }
			virtual const char* what() const throw() {
				return "Cant detach the process for starting the daemon";
			}
		};
	private:
	Tintin_reporter		logger;
	Flags			*flags;
	Server			*server;
};

#endif
