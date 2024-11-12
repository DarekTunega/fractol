NAME = fractol
CFLAGS = -Wall -Wextra -Werror
CC = cc
SRC_PATH = srcs/
LIBMLX	= ./include/MLX42
LDFLAGS = -Linclude/MLX42/build -lmlx42 -lglfw -ldl -lm -lpthread
SRC = main.c
SRCS = $(addprefix $(SRC_PATH), $(SRC))
OBJ_PATH = objects/
SRCS	= $(addprefix $(SRC_PATH), $(SRC))
OBJ		= $(SRC:.c=.o)
OBJS	= $(addprefix $(OBJ_PATH), $(OBJ))

INC		= -I ./include/

all: libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -Iinclude/MLX42/include -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

clean:
	rm -rf $(OBJ_PATH)
	@rm -rf $(LIBMLX)/build

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all re clean fclean libmlx
