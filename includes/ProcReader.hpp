#ifndef PROCREADER_HPP
# define PROCREADER_HPP

#include "all.hpp"
class ProcReader
{
	public:

		ProcReader(std::string path);
		ProcReader( ProcReader const & src );
		virtual ~ProcReader( void );

		ProcReader &							operator=( ProcReader const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, ProcReader const & i);
	void readCmdLine();
	void readComm();
	std::string cmdLine;
	std::string comm;
	private:
		std::string proc_path;
};

#endif
