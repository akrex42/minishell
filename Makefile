NAME := minishell

SRCS := srcs/term/main.c srcs/term/history.c srcs/term/manage_history.c \
		srcs/term/dop_2.c srcs/term/dop_3.c srcs/term/dop_1.c \
		srcs/parser/parser.c srcs/parser/tokens.c srcs/parser/parser_dop.c \
		srcs/handler/handler.c srcs/handler/comands_1.c srcs/parser/parser_for_errors.c\
		srcs/handler/errors.c srcs/handler/dop_1.c srcs/term/dop_4.c\
		srcs/handler/comands_2.c srcs/parser/parser_dop_2.c\
		srcs/builtins/ft_echo.c \
		srcs/builtins/ft_cd.c srcs/builtins/ft_allocate_env_builtins.c \
		srcs/builtins/ft_env.c srcs/builtins/ft_check_equal2.c \
		srcs/builtins/ft_exit.c \
		srcs/builtins/ft_export.c srcs/builtins/print_err_export.c \
		srcs/builtins/ft_pwd.c \
		srcs/builtins/ft_unset.c \

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