# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/13 10:03:24 by logan             #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2019/04/25 17:52:06 by jbeall           ###   ########.fr        #
=======
#    Updated: 2019/04/25 10:48:40 by jbeall           ###   ########.fr        #
>>>>>>> d63eafbe29a298e81ad28cff8791652640504f65
#                                                                              #
# **************************************************************************** #

NAME = asm
<<<<<<< HEAD
LIST = main asm_parse_helper asm_parse_header op
=======
LIST = main asm_parse_helper asm_parse_header
>>>>>>> d63eafbe29a298e81ad28cff8791652640504f65

OBJ_DIR = obj
VPATH = src

OBJ = $(addsuffix .o, $(addprefix $(OBJ_DIR)/, $(LIST)))
DEP = $(OBJ:%.o=%.d)

INCLUDES = -I ../libft/include -I src -I ../include -I ./include

MAKEOPTS=-j4

#OPT = -O3 -flto=full

CPPFLAGS = -Wall -Wextra -Werror $(OPT) -g -march=native \
$(INCLUDES) \
-fsanitize=address -fsanitize=undefined

LDFLAGS = -L ../libft -lft -pipe \
-fsanitize=address -fsanitize=undefined

all: $(NAME)

$(NAME): $(OBJ)
	make -sC ../libft
	@printf "\e[32;1mLinking.. \e[0m\n"
	$(CC) $^ $(LDFLAGS) -o $@
	@printf "\e[32;1mCreated:\e[0m %s\n" $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

-include $(DEP)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@printf "\e[34;1mCompiling: \e[0m%s\n" $<
	$(CC) $(CPPFLAGS) -MMD -c $< -o $@

clean:
	make -sC ../libft clean
	@printf "\e[31;1mCleaning..\e[0m\n"
	@rm -rf $(OBJ_DIR)

fclean: clean
	make -sC ../libft fclean
	@printf "\e[31;1mFull Cleaning..\e[0m\n"
	@rm -f $(NAME)
	@rm -rf $(NAME).dSYM

re:	fclean all

.PHONY: clean fclean all re
