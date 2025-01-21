CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
RM = rm -f
NAME = philo

# ! Src file
SRC = src/main.c 				\
	  src/ft_atol_handle.c 		\
	  src/destroy_resources.c 	\
	  src/init_argument.c		\
	  src/time_of_philo.c		\
	  src/start_simulation.c 	\
	  src/all_philo_ate.c 	 	\
	  src/monitor_death.c    	\
	  src/philo_routine_too.c	\
	  src/philo_routine.c		

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re