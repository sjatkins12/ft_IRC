# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: satkins <satkins@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/07/25 14:05:53 by satkins           #+#    #+#              #
#    Updated: 2018/05/14 11:56:01 by satkins          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_irc

CLIENT = client
SERVER = server

LIBPATH = libft/
LIBFT = libftprintf.a

CC = gcc

FLAGS = -Wall -Wextra -Werror -g -fsanitize=address
CFLAGS = -Wall -Wextra -Werror -c

################################################################################
# SOURCE FILES                                                                 #
################################################################################

SRC_SERVER =  \
			server \
			inter_proc_comm \
			master_process \
			worker_sockets \
			workers
SRC_FTP_FUNC = \
			ftp_functions \
			nlst
SRC_CLIENT = \
			client
SRC_UTILS = \
			dtp_connection \
			fd_set_utils


################################################################################
# Source directories identifiers                                               #
################################################################################

SRCDIR_SERVER = src/server/
SRCDIR_FTP_FUNC = ftp_functions/
SRCDIR_CLIENT = src/client/
SRCDIR_UTILS = src/utils/

SERVERSRC = $(patsubst %, %.o, $(addprefix $(SRCDIR_SERVER), $(SRC_SERVER)))
SERVERSRC += $(patsubst %, %.o, $(addprefix $(SRCDIR_UTILS), $(SRC_UTILS)))
SERVERSRC += $(patsubst %, %.o, $(addprefix $(SRCDIR_SERVER), \
	$(addprefix $(SRCDIR_FTP_FUNC), $(SRC_FTP_FUNC))))

CLIENTSRC = $(patsubst %, %.o, $(addprefix $(SRCDIR_CLIENT), $(SRC_CLIENT)))
CLIENTSRC += $(patsubst %, %.o, $(addprefix $(SRCDIR_UTILS), $(SRC_UTILS)))

################################################################################
# INCLUDE PATHS                                                                #
################################################################################

INCLUDES = \
		-I libft/inc \
		-I inc

################################################################################
# COLOR                                                                        #
################################################################################

RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
CYAN = \033[1;36m
RES = \033[0m

################################################################################
# RULES                                                                        #
################################################################################

all: $(NAME)

$(NAME): $(LIBFT) $(SERVERSRC) $(CLIENTSRC)
	@ echo "$(YELLOW)Compiling programs$(RES)"
	$(CC) $(FLAGS) -L $(LIBPATH) -lftprintf $(INCLUDES) $(SERVERSRC) -o $(SERVER)
	$(CC) $(FLAGS) -L $(LIBPATH) -lftprintf $(INCLUDES) $(CLIENTSRC) -o $(CLIENT)
	@echo "$(GREEN)Binaries Compiled$(RES)"


$(LIBFT):
	@make -C $(LIBPATH)

%.o: %.c
	@ echo "$(YELLOW)Compiling $<...$(RES)"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

debug: CFLAGS += -g -DDEBUG
debug: clean $(NAME)

clean:
	rm -f $(CLIENTSRC) $(SERVERSRC)
	@make -C $(LIBPATH) clean
	@ echo "$(RED)Cleaning folders of object files...$(RES)"

fclean: clean
	rm -f $(SERVER) $(CLIENT)
	@make -C $(LIBPATH) fclean
	@ echo "$(RED)Removing library file and binary...$(RES)"

re: fclean all
	@ echo "$(GREEN)Binary Remade$(RES)"
