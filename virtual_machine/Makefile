# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/13 10:03:24 by logan             #+#    #+#              #
#    Updated: 2019/05/23 15:07:49 by lkaser           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar
LIST = main \
instruction_dispatch \
option_parse \
virtual_machine \
load_player \
process \
op_tab \
decode \
live \
st_sti \
ldi_lldi \
and_or_xor \
aff \
sub_add \
zjmp \
ld_lld \
fork_lfork \
visual \
visual2 \

OBJ_DIR = obj
VPATH = src:src/op

OBJ = $(addsuffix .o, $(addprefix $(OBJ_DIR)/, $(LIST)))
DEP = $(OBJ:%.o=%.d)

INCLUDES = -I ../libft/include -I src -I ../include -I include \
 $(shell pkg-config --cflags ncurses)

MAKEOPTS=-j4

OPT = -O3 -flto=full

CPPFLAGS = -Wall -Wextra -Werror $(OPT) -g -march=native \
$(INCLUDES) -Wno-error=unused-result \
#-fsanitize=address -fsanitize=undefined

LDFLAGS = -L ../libft -lft -lncurses -pipe \
#-fsanitize=address -fsanitize=undefined

all: $(NAME)

$(NAME): $(OBJ)
	@make -sC ../libft
	@printf "\e[32;1mLinking.. \e[0m\n"
	$(CC) $^ $(LDFLAGS) -o $@
	@printf "\e[32;1mCreated:\e[0m %s\n" $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

-include $(DEP)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@printf "\e[34;1mCompiling: \e[0m%s\n" $<
	@$(CC) $(CPPFLAGS) -MMD -c $< -o $@

clean:
	@make -sC ../libft clean
	@printf "\e[31;1mCleaning..\e[0m\n"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@make -sC ../libft fclean
	@printf "\e[31;1mFull Cleaning..\e[0m\n"
	@rm -f $(NAME)
	@rm -rf $(NAME).dSYM

re:	fclean all

.PHONY: clean fclean all re
