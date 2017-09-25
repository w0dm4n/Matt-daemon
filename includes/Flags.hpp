#ifndef FLAGS_HPP
# define FLAGS_HPP

#include "all.hpp"
#include "Flag.hpp"
class Flags
{
	public:

		Flags();
		Flags(int argv_len, char **argv);
		Flags( Flags const & src );
		virtual ~Flags( void );
		bool	flagExist(std::string flag);
		void	addFlag(std::string flag, std::string value);
		Flag	*getFlag(std::string flag);

		Flags &							operator=( Flags const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, Flags const & i);
		std::vector<Flag*>	active_flags;
};

#endif
