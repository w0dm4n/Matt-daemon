#ifndef TINTIN_REPORTER_HPP
# define TINTIN_REPORTER_HPP

#include "all.hpp"
class Tintin_reporter
{
	public:

		Tintin_reporter( void );
		Tintin_reporter( Tintin_reporter const & src );
		virtual ~Tintin_reporter( void );

		Tintin_reporter &							operator=( Tintin_reporter const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, Tintin_reporter const & i);
		bool initLogs();
		std::string getCurrentTime();
		void log(std::string message);
		struct CantCreateLogFolder : public std::exception {
			CantCreateLogFolder() { }
			virtual const char* what() const throw() {
				return "The logger cant create the log folder";
			}
		};

		struct CantOpenLogFile : public std::exception {
			CantOpenLogFile() { }
			virtual const char* what() const throw() {
				return "The logger cant open the log file";
			}
		};

		static Tintin_reporter	*instance()
	    {
	        static Tintin_reporter *s = new Tintin_reporter();
	        return s;
	    }
};

#endif
