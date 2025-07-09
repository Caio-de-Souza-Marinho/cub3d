NAME		= cub3D
CC		= cc
CFLAGS		= -Wall -Wextra -Werror -g
RM		= rm -rf

SRC_DIR		= src/
OBJ_DIR		= obj/
INCLUDE		= -I include -lm -lXext -lX11
LIBFT_DIR	= lib/libft/
LIBFT_LIB	= ${LIBFT_DIR}bin/libft.a
MLX_DIR		= lib/minilibx-linux/
MLX_LIB		= ${MLX_DIR}libmlx_Linux.a
TEST_FILE	?= maps/map1.cub

# DIRS
PARSE_DIR	= $(SRC_DIR)parse/

SRCS		= $(SRC_DIR)main.c \
		  $(PARSE_DIR)parse.c \
		  $(PARSE_DIR)is_line_function.c \

OBJS		= ${SRCS:${SRC_DIR}%.c=${OBJ_DIR}%.o}

all:		${OBJ_DIR} ${NAME}

${NAME}:	${OBJS} ${LIBFT_LIB} ${MLX_LIB}
			${CC} ${CFLAGS} ${OBJS} ${LIBFT_LIB} ${MLX_LIB} ${INCLUDE} -o ${NAME}

${OBJ_DIR}:
			@mkdir -p ${OBJ_DIR}

${OBJ_DIR}%.o:	${SRC_DIR}%.c
			@mkdir -p ${dir $@}
			${CC} ${CFLAGS} -I . -I ${LIBFT_DIR} -I ${MLX_DIR} -c $< -o $@

${LIBFT_LIB}:
			@echo "Building libft..."
			make -C ${LIBFT_DIR}

${MLX_LIB}:
			@echo "Building mlx..."
			make -C ${MLX_DIR}

leak:
			valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./${NAME} ${TEST_FILE}

clean:
			@echo "Cleaning object files..."
			${RM} ${OBJ_DIR}
			@echo "Cleaning libft and mlx objects..."
			make clean -C ${LIBFT_DIR}
			make clean -C ${MLX_DIR}

fclean:		clean
			@echo "Removing binary and libraries..."
			${RM} ${NAME}
			make fclean -C ${LIBFT_DIR}
			${RM} ${MLX_LIB}

re:		fclean all

.PHONY:		all clean fclean re
