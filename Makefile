NAME_SERVER = server
NAME_CLIENT = client
NAME_SERVER_BONUS = server_bonus
NAME_CLIENT_BONUS = client_bonus

CC = clang
FLAGS = -Wall -Wextra -Werror

SRC_SERVER = server.c
SRC_CLIENT = client.c
SRC_SERVER_BONUS = server_bonus.c
SRC_CLIENT_BONUS = client_bonus.c

OBJ_SERVER = $(SRC_SERVER:%.c=%.o)
OBJ_CLIENT = $(SRC_CLIENT:%.c=%.o)
OBJ_SERVER_BONUS = $(SRC_SERVER_BONUS:%.c=%.o)
OBJ_CLIENT_BONUS = $(SRC_CLIENT_BONUS:%.c=%.o)

.PHONY: all bonus re re_bonus clean fclean

all: $(NAME_SERVER) $(NAME_CLIENT)

$(NAME_SERVER): $(OBJ_SERVER)
	@$(CC) $(FLAGS) $(OBJ_SERVER) -o $(NAME_SERVER)
	@echo $(NAME_SERVER) has been compiled.

$(NAME_CLIENT): $(OBJ_CLIENT)
	@$(CC) $(FLAGS) $(OBJ_CLIENT) -o $(NAME_CLIENT)
	@echo $(NAME_CLIENT) has been compiled.

bonus: $(NAME_SERVER_BONUS) $(NAME_CLIENT_BONUS)

$(NAME_SERVER_BONUS): $(OBJ_SERVER_BONUS)
	@$(CC) $(FLAGS) $(OBJ_SERVER_BONUS) -o $(NAME_SERVER_BONUS)
	@echo $(NAME_SERVER_BONUS) has been compiled.

$(NAME_CLIENT_BONUS): $(OBJ_CLIENT_BONUS)
	@$(CC) $(FLAGS) $(OBJ_CLIENT_BONUS) -o $(NAME_CLIENT_BONUS)
	@echo $(NAME_CLIENT_BONUS) has been compiled.

%.o: %.c
	@$(CC) -c $< -o $@

clean:
	@rm -rf $(OBJ_SERVER) $(OBJ_CLIENT)
	@rm -rf $(OBJ_SERVER_BONUS) $(OBJ_CLIENT_BONUS)

fclean: clean
	@rm -rf $(NAME_SERVER) $(NAME_CLIENT)
	@rm -rf $(NAME_SERVER_BONUS) $(NAME_CLIENT_BONUS)

re: clean fclean all

re_bonus: clean fclean bonus
