#ifndef LOCKFILE_HPP
# define LOCKFILE_HPP

#include "all.hpp"
#include <sys/file.h>
#define   LOCK_SH   1    /* shared lock */
#define   LOCK_EX   2    /* exclusive lock */
#define   LOCK_NB   4    /* don't block when locking */
#define   LOCK_UN   8    /* unlock */

class LockFile
{
	public:

		LockFile();
		LockFile( LockFile const & src );
		virtual ~LockFile( void );

		LockFile &							operator=( LockFile const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, LockFile const & i);

		void logAttempt();
		std::string getCurrentTime();
	private:
		int			fd;
		std::fstream file;
};

#endif
