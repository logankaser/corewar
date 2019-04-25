# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/06 20:20:41 by lkaser            #+#    #+#              #
#    Updated: 2019/04/23 14:22:39 by lkaser           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
LIST = ft_atof ft_atoi ft_bzero ft_isalnum ft_isalpha \
ft_isascii ft_isdigit ft_isprint ft_itoa ft_itoa_base ft_lstadd \
ft_lstdel ft_lstdelone ft_lstfind ft_lstiter ft_lstlen ft_lstmap ft_lstnew \
ft_lstpush ft_lstpop ft_lstrm ft_memalloc ft_memccpy ft_memchr ft_memcmp ft_memcpy \
ft_memdel ft_memmove ft_memset ft_min_max ft_putchar ft_putchar_fd ft_putendl \
ft_putendl_fd ft_puterror ft_putnbr ft_putnbr_fd \
ft_putstr ft_putstr_fd ft_qsort ft_strcat ft_strchr ft_strclr \
ft_strcmp ft_strcpy ft_strdel ft_strdup ft_strequ ft_string ft_striter \
ft_striteri ft_strjoin ft_strlcat ft_strlen ft_strmap ft_strmapi ft_strncat \
ft_strncmp ft_strncpy ft_strnequ ft_strnew ft_strnstr ft_strrchr ft_strsplit \
ft_strstr ft_strsub ft_strtrim ft_str_has_only ft_strprepend ft_strappend \
ft_tolower ft_toupper ft_utoa_base ft_wchar_utf8 \
ft_vector ft_uvector ft_fnv ft_map ft_map_internal ft_queue \
format ft_fprintf ft_strf ft_printf \
get_next_line \
ft_byteswap

VPATH = src:src/map:src/vector:src/list:src/str

SRC_DIR = .
OBJ_DIR = obj

OBJ = $(addsuffix .o, $(addprefix $(OBJ_DIR)/, $(LIST)))
DEP = $(OBJ:%.o=%.d)

MAKEOPTS=-j4

#OPT = -O3 -flto=full

CPPFLAGS = -Wall -Wextra -Werror -g \
-I include -march=native $(OPT) \
-fsanitize=address -fsanitize=undefined


all: $(OBJ_DIR) $(NAME)

$(NAME): $(OBJ)
	@printf "\e[32;1mLinking.. \e[0m\n"
	@ar -rcs $@ $^
	@printf "\e[32;1mCreated:\e[0m %s\n" $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

-include $(DEP)

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CPPFLAGS) -MMD -c $< -o $@

clean:
	@printf "\e[31;1mCleaning..\e[0m\n"
	@rm -f $(OBJ) $(DEP)

fclean:
	@printf "\e[31;1mFull Cleaning %s..\e[0m\n" $(NAME)
	@rm -rf $(OBJ_DIR)
	@rm -f $(NAME)

re:	fclean all

.PHONY: clean fclean all re
