# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: logan  <logan@42.us.org>                   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/13 10:03:24 by logan             #+#    #+#              #
#    Updated: 2019/04/17 12:04:50 by lkaser           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIST_ASM = main

LIST_COREWAR = main

OBJ_DIR = obj
VPATH = assembler:virtual_machine

OBJ_ASM = $(addsuffix .o, $(addprefix $(OBJ_DIR)/, $(LIST_ASM)))
OBJ_COREWAR = $(addsuffix .o, $(addprefix $(OBJ_DIR)/, $(LIST_COREWAR)))
DEP = $(OBJ_ASM:%.o=%.d) $(OBJ_COREWAR:%.o=%.d)

INCLUDES = -I libft/include -I src

MAKEOPTS=-j4

#OPT = -flto=full -O3

CPPFLAGS = -Wall -Wextra -Werror $(OPT) -march=native \
$(INCLUDES) \
-fsanitize=address -fsanitize=undefined -g

LDFLAGS =  -flto=full -pipe \
-fsanitize=address -fsanitize=undefined

all: asm corewar

asm: $(OBJ_ASM)
	#make -sC libft
	@printf "\e[32;1mLinking.. \e[0m\n"
	$(CC) $^ $(LDFLAGS) -o $@
	@printf "\e[32;1mCreated:\e[0m %s\n" $@

corewar: $(OBJ_COREWAR)
	#make -sC libft
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
	make -sC libft clean
	@printf "\e[31;1mCleaning..\e[0m\n"
	@rm -rf $(OBJ_DIR)

fclean: clean
	make -sC libft fclean
	@printf "\e[31;1mFull Cleaning..\e[0m\n"
	@rm -f asm corewar
	@rm -rf asm.dSYM corewar.dSYM

re:	fclean all

.PHONY: clean fclean all re
