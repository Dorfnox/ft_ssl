# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bpierce <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/25 10:27:14 by bpierce           #+#    #+#              #
#    Updated: 2018/03/20 18:04:46 by bpierce          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ssl

FILES = main \
		error \
		flags \
		input \
		output \
		endian \
		execute \
		md5_flags 	  md5_init     md5_execute \
		sha256_flags  sha256_init  sha256_execute  sha256_execute2

C_FLAGS = -Wall -Wextra -Werror

C_LOC = src/
C_NAM = $(addsuffix .c, $(FILES))
C_SRC = $(addprefix $(C_LOC), $(C_NAM))

O_LOC = obj/
O_NAM = $(addsuffix .o, $(FILES))
O_SRC = $(addprefix $(O_LOC), $(O_NAM))

LIB_LOC = libft/
LIB_NAM = libft.a
LIB_SRC = $(addprefix $(LIB_LOC), $(LIB_NAM))

H_LOCS = -I inc -I libft/inc
HEADERS = inc/ft_ssl.h inc/ft_ssl_macros.h

RED = [31m
GREEN = [32m
BLUE = [34m
YELLOW = [33m
MAGENTA = [35m
GREY = [37m
GREEN_LIGHT = [92m
YELLOW_LIGHT = [93m
YELLOW_BOLD = [1;33m
MAGENTA_LIGHT = [95m
BLINK = [5m
END_COLOUR = [0m

COUNTER = 0

all: $(NAME)

$(NAME): $(LIB_SRC) $(O_SRC)
	@echo "$(YELLOW_BOLD)Compiling executable... $@$(END_COLOUR)"
	@gcc $(C_FLAGS) $^ -o $@
	@echo
	@echo "$(GREEN_LIGHT)     xxXXXXXXXXxx     $(END_COLOUR)"
	@echo "$(GREEN_LIGHT)  xXX------------XXx  $(END_COLOUR)"
	@echo "$(GREEN_LIGHT)xXX--- $(GREEN_LIGHT_BLINK)COMPLETE$(END_COLOUR) $(GREEN_LIGHT)---XXx$(END_COLOUR)"
	@echo "$(GREEN_LIGHT)xXX---- $(GREEN_LIGHT_BLINK)YIPPEE$(END_COLOUR) $(GREEN_LIGHT)----XXx$(END_COLOUR)"
	@echo "$(GREEN_LIGHT)  xXX------------XXx  $(END_COLOUR)"
	@echo "$(GREEN_LIGHT)     XXxxxxxxxxXX     $(END_COLOUR)"
	@echo

$(O_LOC)%.o: $(C_LOC)%.c $(HEADERS)
	@echo "$(GREY)Re-compiling src file... $(END_COLOUR)$(YELLOW)$<$(END_COLOUR)"
	@gcc $(C_FLAGS) $(H_LOCS) -o $@ -c $<

$(LIB_SRC): force
	@echo "$(YELLOW)----------- Checking Libft Library -----------$(END_COLOUR)"
	@printf "$(YELLOW_LIGHT)$@ re-compile status: $(END_COLOUR)"
	@make -C $(LIB_LOC)
	@echo "$(YELLOW)----------- Library Check Complete -----------$(END_COLOUR)"

force:
	@true

clean:
	@/bin/rm -rf $(O_SRC)
	@make clean -C $(LIB_LOC)
	@echo "$(GREEN)clean complete!$(END_COLOUR)"

fclean: clean
	@/bin/rm -f $(NAME)
	@make fclean -C $(LIB_LOC)
	@echo "$(GREEN)fclean complete!$(END_COLOUR)"

re: fclean all

test:
	@make && echo "yo" | ./$(NAME) md5

.PHONY: all force clean fclean re
