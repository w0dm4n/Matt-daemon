#ifndef LOCKFILE_HPP
# define LOCKFILE_HPP

#include "all.hpp"

class LockFile
{
	public:

		LockFile( bool );
		LockFile( LockFile const & src );
		virtual ~LockFile( void );

		LockFile &							operator=( LockFile const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, LockFile const & i);

		void logAttempt();
		std::string getCurrentTime();
	private:
		std::fstream file;
		bool		deleteFile;
};

#endif
