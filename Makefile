# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/05/20 17:57:50 by frmarinh          #+#    #+#              #
#    Updated: 2017/09/18 04:57:47 by frmarinh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_MATT_DAEMON	=	Matt_daemon

NAME		=   Matt_daemon
NAMEBASE    =   $(shell basename $(NAME))
LENGTHNAME	=	`printf "%s" $(NAMEBASE) | wc -c`
MAX_COLS	=	$$(echo "$$(tput cols)-24-$(LENGTHNAME)"|bc)

CC			=	g++ -L /usr/local/lib/ -lboost_system -lboost_filesystem -std=c++11 -lpthread
FLAGS_O		=

SRCDIR_MATT_DAEMON		=	srcs/
OBJDIR_MATT_DAEMON		=	objs/

INCDIR				=	includes/

SRCBASE_MATT_DAEMON	=	\
					main.cpp				\
					Daemon.cpp				\
					ProcReader.cpp			\
					Tintin_reporter.cpp		\
					LockFile.cpp			\
					Server.cpp				\
					Client.cpp

INCS			=	$(addprefix $(INCDIR), $(INCBASE))

SRCS_MATT_DAEMON			=	$(addprefix $(SRCDIR_MATT_DAEMON), $(SRCBASE_MATT_DAEMON))
OBJS_MATT_DAEMON			=	$(addprefix $(OBJDIR_MATT_DAEMON), $(SRCBASE_MATT_DAEMON:.cpp=.o))

.SILENT:

all:		$(NAME)

$(NAME):
	if test -f $(NAME_MATT_DAEMON) ; then											\
		echo "make: Nothing to be done for \`all\`.";				        		\
	else																			\
		make MATT_DAEMON && 														\
		echo "\r\033[38;5;184m👥  AUTHOR(s): \033[0m\033[K" && 						\
		echo "\r\033[38;5;15m`cat auteur | sed s/^/\ \ \ \ -/g`\033[0m\033[K" &&	\
		echo "\033[38;5;44m☑️  ALL    $(NAMEBASE) is done\033[0m\033[K";			\
	fi

$(OBJDIR_MATT_DAEMON):
	mkdir -p $(OBJDIR_MATT_DAEMON)
	mkdir -p $(dir $(OBJS_MATT_DAEMON))

$(OBJDIR_MATT_DAEMON)%.o : $(SRCDIR_MATT_DAEMON)%.cpp | $(OBJDIR_MATT_DAEMON)
	$(CC) $(FLAGS) -MMD -c $< -o $@											\
		-I $(INCDIR)														\
		-I $(INCDIR)

fcleanlib:	fclean

re:			fclean all

relib:		fclean fcleanlib all

.PHONY:		fclean fcleanlib clean re relib

MATT_DAEMON: $(OBJDIR_MATT_DAEMON) $(OBJS_MATT_DAEMON)
	$(CC) $(FLAGS) $(FLAGS_O) -o $(NAME_MATT_DAEMON) $(OBJS_MATT_DAEMON)
	echo "\r\033[38;5;22m📗  MAKE $(NAME_MATT_DAEMON)"

clean:
	@rm -rf $(OBJDIR_MATT_DAEMON)
	echo "\r\033[38;5;124m📕  CLEAN $(OBJDIR_MATT_DAEMON)\033[0m\033[K";

fclean:		clean
	@rm -rf $(NAME_MATT_DAEMON)
	echo "\r\033[38;5;124m📕  FCLEAN $(NAME_MATT_DAEMON)\033[0m\033[K";

-include $(OBJS:.o=.d)
