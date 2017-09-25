#include "Flags.hpp"

Flags::Flags()
{

}

Flags::Flags (int argv_len, char **argv)
{
	for (int i = 1; i < argv_len; i++)
	{
		std::string arg = argv[i];
		if (arg.size() > 2 && arg.substr(0, 2) == "--") {
			std::string value;
			if ((i + 1) < argv_len) {
				value = argv[i + 1];
				if (value.substr(0, 2) == "--") {
					value = "";
				}
			}
			this->addFlag(arg.substr(2, arg.size()), value);
		}
	}
}

bool Flags::flagExist(std::string flag)
{
	for (int i = 0; i < this->active_flags.size(); i++)
	{
		if (this->active_flags[i]->flag == flag)
			return true;
	}
	return false;
}

void Flags::addFlag(std::string flag, std::string value)
{
	if (!this->flagExist(flag)) {
		this->active_flags.push_back(new Flag(flag, value));
	}
}

Flag *Flags::getFlag(std::string flag)
{
	for (int i = 0; i < this->active_flags.size(); i++)
	{
		if (this->active_flags[i]->flag == flag) {
			return this->active_flags[i];
		}
	}
	return NULL;
}

Flags::Flags ( Flags const & src )
{
	*this = src;
	return ;
}

Flags &				Flags::operator=( Flags const & rhs )
{
	if (this != &rhs)
	{
	}
	return (*this);
}

Flags::~Flags ( void )
{
	for (int i = 0; i < this->active_flags.size(); i++) {
		delete this->active_flags[i];
	}
}

std::ostream &				operator<<(std::ostream & o, Flags const & i)
{
	(void)i;
	return (o);
}
