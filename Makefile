# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bgolding <bgolding@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/02 09:48:10 by bgolding          #+#    #+#              #
#    Updated: 2024/01/03 17:22:51 by bgolding         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	fdf

LIB				=	lib/
INC				=	inc/
SRC_DIR			=	src/
OBJ_DIR			=	obj/
INC_DIR			=	inc/
LIBFT_DIR 		=	$(LIB)libft/
MINILIBX_DIR	=	$(LIB)mlx/

SRC_FILES		=	main hooks draw map map_utils draw_utils draw_settings rotate controls

STATIC_LIBS		=	$(LIBFT_DIR)libft.a \
					$(MINILIBX_DIR)libmlx.a
					
SRCS			=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJS			=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror
RM				=	rm -f
AR				=	ar -r

DEF_COLOR		=	\033[0;39m
GREEN			=	\033[0;92m
YELLOW			=	\033[0;93m

all:			$(STATIC_LIBS) $(NAME)

$(STATIC_LIBS):
				@echo "$(YELLOW)Creating archives...$(DEF_COLOR)"
				@make -C $(LIBFT_DIR)
				@make -C $(MINILIBX_DIR)
				@echo "$(GREEN)Minilibx ready! $(DEF_COLOR)"

$(NAME):		$(OBJ_DIR) $(OBJS) $(STATIC_LIBS)
				$(CC) $(CFLAGS) -L$(LIBFT_DIR) -lft -L$(MINILIBX_DIR) -lmlx -framework OpenGL -framework AppKit $(OBJS) -o $@
				@echo "$(GREEN)Successfully created program: $(NAME) $(DEF_COLOR)"

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c | $(OBJ_DIR)
				@$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(OBJ_DIR):
				@mkdir -p $@

clean:			
				@$(RM) -rf $(OBJ_DIR)
				@make clean -C $(LIBFT_DIR)
				@make clean -C $(MINILIBX_DIR)
				@echo "$(GREEN)clean complete $(DEF_COLOR)"

fclean:			clean
				@$(RM) $(NAME)
				@make fclean -C $(LIBFT_DIR)
				@echo "$(GREEN)fclean complete $(DEF_COLOR)"

re:				fclean all

.PHONY:			all clean fclean re