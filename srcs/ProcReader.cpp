#include "ProcReader.hpp"

ProcReader::ProcReader (std::string path)
{
	this->proc_path = path;

	this->readCmdLine();
	this->readComm();
}

ProcReader::ProcReader ( ProcReader const & src )
{
	*this = src;
	return ;
}

ProcReader &				ProcReader::operator=( ProcReader const & rhs )
{
	if (this != &rhs)
	{
	}
	return (*this);
}

ProcReader::~ProcReader ( void )
{
	return ;
}

std::ostream &				operator<<(std::ostream & o, ProcReader const & i)
{
	(void)i;
	return (o);
}

void	ProcReader::readCmdLine()
{
	std::ifstream cmdline (std::string(this->proc_path + "/cmdline").c_str());
	std::string line;
	if (cmdline.is_open())
	{
		while (getline (cmdline, line))
			this->cmdLine += line;
		cmdline.close();
	}
}

void	ProcReader::readComm()
{
	std::ifstream cmdline (std::string(this->proc_path + "/comm").c_str());
	std::string line;
	if (cmdline.is_open())
	{
		while (getline (cmdline, line))
			this->comm += line;
		cmdline.close();
	}
}
