#include "Flag.hpp"

Flag::Flag (std::string flag, std::string value)
{
	this->flag = flag;
	this->value = value;
}

Flag::Flag ( Flag const & src )
{
	*this = src;
	return ;
}

Flag &				Flag::operator=( Flag const & rhs )
{
	if (this != &rhs)
	{

	}
	return (*this);
}

Flag::~Flag ( void )
{
	return ;
}

std::ostream &				operator<<(std::ostream & o, Flag const & i)
{
	(void)i;
	return (o);
}
