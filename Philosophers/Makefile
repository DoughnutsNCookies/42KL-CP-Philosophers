# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: schuah <schuah@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/07 10:52:13 by schuah            #+#    #+#              #
#    Updated: 2022/08/10 13:48:37 by schuah           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo
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
SRCS		= 	$(addprefix $(SRCS_DIR), $(addsuffix .c, $(SRCS_FILES)))
OBJS		= 	$(addprefix $(OBJS_DIR), $(addsuffix .o, $(SRCS_FILES)))
SRCS_DIR	=	srcs/
OBJS_DIR	=	objs/

all:			$(NAME)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
				$(CC) $(CFLAGS) -c $< -o $@

$(NAME):		mkdir_objs $(OBJS)
				$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

mkdir_objs:
				mkdir -p $(OBJS_DIR)

clean:
				rm -rf $(OBJS_DIR)

fclean:			clean
				rm -rf $(NAME)

re:				fclean all