NAME		= cub3D
CC		= cc
CFLAGS		= -Wall -Wextra -Werror -g
RM		= rm -rf

SRC_DIR		= src/
OBJ_DIR		= obj/
LIBFT_DIR	= lib/libft/
LIBFT_LIB	= ${LIBFT_DIR}bin/libft.a
MLX_DIR		= lib/minilibx-linux/
MLX_LIB		= ${MLX_DIR}libmlx_Linux.a
INCLUDE		= -I include -I ${LIBFT_DIR} -I ${MLX_DIR}
LDFLAGS		= -lm -lXext -lX11
TEST_FILE	?= maps/good/square_map.cub

# DIRS
INIT_DIR	= ${SRC_DIR}init/
PARSE_DIR	= $(SRC_DIR)parse/
MAP_DIR		= ${SRC_DIR}map/
ERROR_DIR	= $(SRC_DIR)error/
DEBUG_DIR	= $(SRC_DIR)debug/
FREE_DIR	= $(SRC_DIR)free/
RENDER_DIR	= $(SRC_DIR)render/
MOVE_DIR	= $(SRC_DIR)move/

SRCS		= $(SRC_DIR)main.c \
		  $(INIT_DIR)init_game.c \
		  $(PARSE_DIR)parse.c \
		  $(PARSE_DIR)is_line_function.c \
		  $(PARSE_DIR)color_parser.c \
		  $(PARSE_DIR)cub_check.c \
		  $(PARSE_DIR)map_builder.c \
		  $(PARSE_DIR)texture_parser.c \
		  $(PARSE_DIR)parse_utils.c \
		  $(PARSE_DIR)get_player.c \
		  ${MAP_DIR}map_validation.c \
		  ${MAP_DIR}map_validation_utils.c \
		  $(ERROR_DIR)error.c \
		  $(DEBUG_DIR)print_config.c \
		  $(FREE_DIR)free_all.c \
		  $(FREE_DIR)free_utils.c \
		  $(RENDER_DIR)render.c \
		  $(RENDER_DIR)render_utils.c \
		  $(RENDER_DIR)raycast.c \
		  $(RENDER_DIR)draw.c \
		  $(RENDER_DIR)minimap.c \
		  $(RENDER_DIR)minimap_grid.c \
		  $(RENDER_DIR)minimap_player.c \
		  $(RENDER_DIR)load_texture.c \
		  $(RENDER_DIR)draw_texture.c \
		  $(RENDER_DIR)sprite.c \
		  $(RENDER_DIR)sprite_utils.c \
		  $(MOVE_DIR)movements.c \
		  $(MOVE_DIR)move_player.c \
		  $(MOVE_DIR)actions.c \

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
		./${NAME} ${TEST_FILE}

${NAME}:	${OBJS} ${LIBFT_LIB} ${MLX_LIB}
			@echo "${CYAN}[  COMPILING ]${RESET} Compiling source files..."
			@${CC} ${CFLAGS} ${OBJS} ${LIBFT_LIB} ${MLX_LIB} ${LDFLAGS} -o ${NAME}
			@echo "${GREEN}Build complete!${RESET}"

${OBJ_DIR}/%.o:	${SRC_DIR}/%.c
			@mkdir -p ${@D}
			@${CC} ${CFLAGS} ${INCLUDE} -c $< -o $@

${OBJ_DIR}:
			@mkdir -p ${OBJ_DIR}

${LIBFT_LIB}:
			@echo "${BLUE}[  BUILDING  ]${RESET} Building libft..."
			@make -s -C ${LIBFT_DIR} --no-print-directory

${MLX_LIB}:
			@echo "${BLUE}[  BUILDING  ]${RESET} Building mlx..."
			@make -s -C ${MLX_DIR} --no-print-directory > /dev/null 2>&1

leak:		re
			valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./${NAME} ${TEST_FILE}

leakfile:	re
			valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind.log ./${NAME} ${TEST_FILE}

leaksup:	re
			valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=suppression.sup ./${NAME} ${TEST_FILE}

leakfilesup:	re
			valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=suppression.sup --log-file=valgrind.log ./${NAME} ${TEST_FILE}

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
