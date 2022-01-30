NAME_SERVER = server
NAME_CLIENT = client

CC = clang
FLAGS = -Wall -Wextra -Werror

SRC_SERVER = server.c
SRC_CLIENT = client.c

OBJ_SERVER = $(SRC_SERVER:%.c=%.o)
OBJ_CLIENT = $(SRC_CLIENT:%.c=%.o)

all: $(NAME_SERVER) $(NAME_CLIENT)

$(NAME_SERVER): $(OBJ_SERVER)
	@$(CC) $(FLAGS) $(OBJ_SERVER) -o $(NAME_SERVER)
	@echo $(NAME_SERVER) has been compiled.

$(NAME_CLIENT): $(OBJ_CLIENT)
	@$(CC) $(FLAGS) $(OBJ_CLIENT) -o $(NAME_CLIENT)
	@echo $(NAME_CLIENT) has been compiled.

%.o: %.c
	@$(CC) -c $< -o $@

clean:
	@rm -rf $(OBJ_SERVER) $(OBJ_CLIENT)

fclean: clean
	@rm -rf $(NAME_SERVER) $(NAME_CLIENT)

re: clean fclean all

.PHONY: clean fclean re all
