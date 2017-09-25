#ifndef FLAG_HPP
# define FLAG_HPP

#include "all.hpp"
class Flag
{
	public:

		Flag(std::string flag, std::string value);
		Flag( Flag const & src );
		virtual ~Flag( void );

		Flag &							operator=( Flag const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, Flag const & i);
	std::string flag;
	std::string value;
};

#endif
