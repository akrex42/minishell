NAME := minishell

SRCS := srcs/main.c srcs/ft_history.c srcs/ft_manage_history.c \
		srcs/ft_dop_1.c srcs/ft_dop_2.c srcs/ft_dop_3.c

OBJS := ${patsubst %.c,%.o,${SRCS}}
D_FILES := ${patsubst %.c,%.d,${SRCS}}

GCC := gcc
FLAGS := -Wall -Wextra -Werror -g # -g для дебагинга 
# FLAGS := -g # -g для дебагинга 
INCLUDES := includes

all: ${NAME}

${NAME}: ${OBJS}
	make -C libft
	make -C libft bonus
	cp libft/libft.a ./
	${GCC} -ltermcap libft.a ${OBJS} -o ${NAME}

%.o : %.c
	${GCC} ${FLAGS} -I ${INCLUDES}  -c $< -o $@ -MD

include ${wildcard ${D_FILES}}

clean:
	rm -f ${OBJS} ${D_FILES}

fclean: clean
	rm -f ${NAME}
	rm -f libft.a 
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re