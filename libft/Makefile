# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yzombie <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/18 14:53:22 by yzombie           #+#    #+#              #
#    Updated: 2021/04/18 14:54:08 by yzombie          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #




NAME := libft.a
OBJS :=  ft_strrchr.o ft_strnstr.o ft_strncmp.o ft_atoi.o ft_isalpha.o ft_isdigit.o \
		 ft_isalnum.o ft_isascii.o ft_isprint.o ft_toupper.o ft_tolower.o ft_memset.o \
		 ft_bzero.o ft_memcpy.o ft_memccpy.o ft_memmove.o ft_memchr.o ft_memcmp.o \
		 ft_strlen.o ft_strlcpy.o ft_strlcat.o ft_strchr.o ft_calloc.o ft_strdup.o \
		 ft_substr.o ft_strjoin.o ft_split.o ft_strtrim.o ft_itoa.o ft_strmapi.o \
		 ft_putchar_fd.o ft_putstr_fd.o ft_putendl_fd.o ft_putnbr_fd.o

OBJS_BONUS :=	ft_lstnew.o ft_lstadd_front.o ft_lstsize.o ft_lstlast.o ft_lstadd_back.o \
				ft_lstdelone.o ft_lstclear.o ft_lstiter.o ft_lstmap.o

FLAGS := -Wall -Wextra -Werror
GCC := gcc

all: ${NAME}

bonus: ${OBJS_BONUS}
	ar rc ${NAME} $^

deps := $(patsubst %.o,%.d,$(OBJS))
	-include $(deps)
deps_bonus := $(patsubst %.o,%.d,$(OBJS_BONUS))
	-include $(deps_bonus)
DEPFLAGS = -MMD -MF ${@:.o=.d}

$(NAME): ${OBJS}
	 ar rc ${NAME} $^

%.o: %.c
	${GCC} ${FLAGS} -c $< ${DEPFLAGS}

clean:
	rm -f ${OBJS} ${OBJS:.o=.d} 
	rm -f ${OBJS_BONUS} ${OBJS_BONUS:.o=.d}

fclean:	clean
	rm -f ${NAME}

re:	fclean all

.PHONY: all clean fclean re bonus