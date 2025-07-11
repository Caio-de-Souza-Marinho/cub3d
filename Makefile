NAME		= cub3D
CC		= cc
CFLAGS		= -Wall -Wextra -Werror
RM		= rm -rf

SRC_DIR		= src/
OBJ_DIR		= obj/
LIBFT_DIR	= lib/libft/
LIBFT_LIB	= ${LIBFT_DIR}bin/libft.a
MLX_DIR		= lib/minilibx-linux/
MLX_LIB		= ${MLX_DIR}libmlx_Linux.a
INCLUDE		= -I include -I ${LIBFT_DIR} -I ${MLX_DIR}
LDFLAGS		= -lm -lXext -lX11
TEST_FILE	?= maps/map1.cub

MAP_VAL_DIR	= ${SRC_DIR}map_validation

SRCS		= $(SRC_DIR)main.c \

OBJS		= ${SRCS:${SRC_DIR}/%.c=${OBJ_DIR}/%.o}

# Colors
RED	= \033[1;31m
GREEN	= \033[1;32m
YELLOW	= \033[1;33m
BLUE	= \033[1;34m
MAG	= \033[1;35m
CYAN	= \033[1;36m
RESET	= \033[0m

all:		${NAME}

run:		re
		./${NAME}

${NAME}:	${OBJS} ${LIBFT_LIB} ${MLX_LIB}
			@echo "${CYAN}[  COMPILING ]${RESET} Compiling source files..."
			@${CC} ${CFLAGS} ${OBJS} ${LIBFT_LIB} ${MLX_LIB} ${LDFLAGS} -o ${NAME}
			@echo "${GREEN}Build complete!${RESET}"

${OBJ_DIR}/%.o:	${SRC_DIR}/%.c
			@mkdir -p ${@D}
			@${CC} ${CFLAGS} ${INCLUDE} -c $< -o $@

${LIBFT_LIB}:
			@echo "${BLUE}[  BUILDING  ]${RESET} Building libft..."
			@make -s -C ${LIBFT_DIR} --no-print-directory

${MLX_LIB}:
			@echo "${BLUE}[  BUILDING  ]${RESET} Building mlx..."
			@make -s -C ${MLX_DIR} --no-print-directory > /dev/null 2>&1

leak:
			valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./${NAME} ${TEST_FILE}

clean:
			@echo "${RED}[  CLEANING  ]${RESET} Removing object files..."
			@${RM} ${OBJ_DIR}
			@echo "${RED}[  CLEANING  ]${RESET} Removing libft object files..."
			@make -s -C ${LIBFT_DIR} clean --no-print-directory
			@echo "${RED}[  CLEANING  ]${RESET} Removing mlx object files..."
			@make -s -C ${MLX_DIR} clean --no-print-directory > /dev/null 2>&1

fclean:		clean
			@echo "${RED}[  CLEANING  ]${RESET} Removing binary and libraries..."
			@${RM} ${NAME}
			@make -s -C ${LIBFT_DIR} fclean --no-print-directory
			@${RM} ${MLX_LIB}

re:		fclean all

.PHONY:		all clean fclean re leak
