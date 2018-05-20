# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: satkins <satkins@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/07/25 14:05:53 by satkins           #+#    #+#              #
#    Updated: 2018/05/20 00:28:51 by satkins          ###   ########.fr        #
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
			accept_connection \
			server \
			select_loop \
			client_message \
			server_pass \
			nickname \
			send_channel_msg \
			close_connection \
			color \
			join \
			who

SRC_CLIENT = \
			connect_to_server \
			command_loop \
			prompt \
			recv_channel_msg \
			move_to_prompt
SRC_COMMANDS = \
			nick \
			pass \
			join \
			color \
			who

SRC_UTILS = \
			fd_set_utils \
			socket_utils \
			pwd_terminal \
			termcap_utils \
			my_putchar \
			setup_termcaps \
			color

SRC_CLASSES = \
			client \
			channel


################################################################################
# Source directories identifiers                                               #
################################################################################

SRCDIR_SERVER = src/server/
SRCDIR_CLIENT = src/client/
SRCDIR_COMMANDS = commands/
SRCDIR_UTILS = src/utils/

SRCDIR_CLASSES = src/classes/

SERVERSRC = $(patsubst %, %.o, $(addprefix $(SRCDIR_SERVER), $(SRC_SERVER)))
SERVERSRC += $(patsubst %, %.o, $(addprefix $(SRCDIR_UTILS), $(SRC_UTILS)))
SERVERSRC += $(patsubst %, %.o, $(addprefix $(SRCDIR_CLASSES), $(SRC_CLASSES)))

CLIENTSRC = $(patsubst %, %.o, $(addprefix $(SRCDIR_CLIENT), $(SRC_CLIENT)))
CLIENTSRC += $(patsubst %, %.o, $(addprefix $(SRCDIR_CLIENT), \
	$(addprefix $(SRCDIR_COMMANDS), $(SRC_COMMANDS))))
CLIENTSRC += $(patsubst %, %.o, $(addprefix $(SRCDIR_UTILS), $(SRC_UTILS)))

################################################################################
# INCLUDE PATHS                                                                #
################################################################################

INCLUDES = \
		-I libft/inc \
		-I inc

LIB_LINK = \
	-l ftprintf \
	-l termcap

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
	$(CC) $(FLAGS) -L $(LIBPATH) $(LIB_LINK) $(INCLUDES) $(SERVERSRC) -o $(SERVER)
	$(CC) $(FLAGS) -L $(LIBPATH) $(LIB_LINK) $(INCLUDES) $(CLIENTSRC) -o $(CLIENT)
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
