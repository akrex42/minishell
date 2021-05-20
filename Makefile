NAME := minishell

SRCS := srcs/term/main.c srcs/term/history.c srcs/term/manage_history.c\
		srcs/term/dop_2.c srcs/term/dop_3.c srcs/term/dop_1.c\
		srcs/parser/parser.c srcs/parser/tokens.c srcs/parser/parser_dop.c \
		srcs/handler/handler.c srcs/handler/comands.c \
		srcs/handler/ft_cd.c \
		srcs/handler/errors.c \
		srcs/handler/dop_1.c \

		
OBJS := ${patsubst %.c,%.o,${SRCS}}
D_FILES := ${patsubst %.c,%.d,${SRCS}}

GCC := gcc
# FLAGS := -Wall -Wextra -Werror 
FLAGS := -g # -g для дебагинга 
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