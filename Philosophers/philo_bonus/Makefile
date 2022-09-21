# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/07 10:52:13 by schuah            #+#    #+#              #
#    Updated: 2022/09/21 14:16:43 by schuah           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo_bonus
CC			=	gcc
RM			=	rm -f
CFLAGS		=	-Wall -Wextra -Werror
# CFLAGS		+= 	-pthread
# CFLAGS		+= 	-g -fsanitize=thread
SRCS_FILES	=	ph_main_bonus \
				ph_init_bonus \
				ph_libft_bonus \
				ph_getters_bonus \
				ph_philosophizing
SRCS		= 	$(addprefix $(SRCS_DIR), $(addsuffix .c, $(SRCS_FILES)))
OBJS		= 	$(addprefix $(OBJS_DIR), $(addsuffix .o, $(SRCS_FILES)))
SRCS_DIR	=	srcs/
OBJS_DIR	=	objs/

all:			
				mkdir -p $(OBJS_DIR)
				make $(NAME)

bonus:			
				mkdir -p $(OBJS_DIR)
				make $(NAME)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
				$(CC) $(CFLAGS) -c $< -o $@

$(NAME):		$(OBJS)
				$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
				rm -rf $(OBJS_DIR)

fclean:			clean
				rm -rf $(NAME)

re:				fclean all

.PHONY:			all bonus clean fclean re