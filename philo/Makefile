# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/25 10:15:19 by pirichar          #+#    #+#              #
#    Updated: 2022/05/31 12:28:01 by pirichar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME = philo

SRC			= src
INC			= include
OBJ			= obj
CFILES		= create.c main.c parsing.c print.c queue.c routine.c time.c check.c
HFILES		= colors.h philo.h
OFILES		= $(CFILES:.c=.o)
SRCS		= $(addprefix $(SRC)/, $(CFILES))
HEADERS		= $(addprefix $(INC)/, $(HFILES))

OBJS		= $(addprefix $(OBJ)/, $(OFILES))
VPATH		= $(SRC)


CC			= gcc
CFLAGS		= -Wall -Werror -Wextra -g -pthread 
RM			= rm -rf

$(OBJ)/%.o:	%.c 
			@$(CC) $(CFLAGS) -c $< -o  $@
			
$(NAME):	$(OBJ) $(OBJS) 
			@$(CC) $(OBJS) -o $(NAME)
			@echo "COMPILING DONE"

$(OBJ):	
			@mkdir -p $(OBJ)


all:		$(NAME)

bonus :		$(OBJ) $(OBJBNS)
			@$(CC) $(OBJBNS) -o $(NAME)
			@echo "COMPILING BONUS DONE"

clean:
			@$(RM) $(OBJS) $(OBJBNS) $(OBJ)

fclean:		clean
			@$(RM) $(NAME)

re:			fclean all

norme:
			@norminette $(SRCS) $(HEADERS) $(GETNEXT) $(BONUSNORM)
