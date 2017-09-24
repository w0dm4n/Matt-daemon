/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/23 15:16:40 by frmarinh          #+#    #+#             */
/*   Updated: 2017/09/23 15:16:42 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "daemon.hpp"

int		main(int argc, char **argv)
{
	Daemon daemon;

	try
	{
		daemon.init();
	}
	catch (std::exception &error)
	{
		LockFile *lockFile = Daemon::getLockFile();
		if (lockFile) {
			delete lockFile;
		}
		std::cout << "An error occured while trying to init the daemon: " <<
			error.what() << std::endl;
	}
}
