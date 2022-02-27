PHILO = philo

CFLAGS  = -Wall -Wextra -Werror

CC   = gcc

HEADER  = philo.h

RM   = rm -f

SRCS	=	initialization.c philo.c utils.c utils_libft.c \

OBJS   = ${SRCS:.c=.o}

all:   ${PHILO}

.c.o:
	${CC} ${CFLAGS} -g -pthread -c $< -o ${<:.c=.o}

$(PHILO):	$(OBJS)  $(HEADER)
			$(CC) $(OBJS) $(CFLAGS)  -o $(PHILO)

clean:
	${RM} ${OBJS} ${OBJS_B}

fclean:  clean
		${RM} ${PHILO}

re:   fclean all

.PHONY:  all clean fclean re
