# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/07 10:52:13 by schuah            #+#    #+#              #
#    Updated: 2022/08/16 16:21:40 by schuah           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo
BNS_NAME	=	philo_bonus
CC			=	gcc
RM			=	rm -f
CFLAGS		=	-Wall -Wextra -Werror
# CFLAGS		+= 	-pthread
# CFLAGS		+= 	-g -fsanitize=thread
SRCS_FILES	=	ph_main \
				ph_init \
				ph_libft \
				ph_getters \
				ph_checkstate \
				ph_philosophizing
BNS_FILES	=	ph_main_bonus \
				ph_init_bonus \
				ph_libft_bonus \
				ph_getters_bonus \
				ph_philosophizing
SRCS		= 	$(addprefix $(SRCS_DIR), $(addsuffix .c, $(SRCS_FILES)))
BNS			= 	$(addprefix $(BNS_DIR), $(addsuffix .c, $(BNS_FILES)))
OBJS		= 	$(addprefix $(OBJS_DIR), $(addsuffix .o, $(SRCS_FILES)))
BNS_OBJS	=	$(addprefix $(BNS_DIR), $(addsuffix .c, $(BNS_FILES)))
SRCS_DIR	=	philo/
OBJS_DIR	=	objs/
BNS_DIR		=	philo_bonus/

all:			$(NAME)

bonus:			$(BNS_NAME)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
				$(CC) $(CFLAGS) -c $< -o $@

$(NAME):		mkdir_objs $(OBJS)
				$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

$(BNS_NAME):	mkdir_objs $(BNS_OBJS)
				$(CC) $(CFLAGS) $(BNS) -o $(BNS_NAME)

mkdir_objs:
				mkdir -p $(OBJS_DIR)

clean:
				rm -rf $(OBJS_DIR)

fclean:			clean
				rm -rf $(NAME) $(BNS_NAME)

re:				fclean all