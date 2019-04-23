/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 20:28:19 by lkaser            #+#    #+#             */
/*   Updated: 2019/04/17 11:43:07 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define ASSERT_FAIL return(-1)
#include "libft.h"

static t_fileinfo	*new_fi(const int fd)
{
	t_fileinfo *fi;

	fi = malloc(sizeof(t_fileinfo));
	fi->fd = fd;
	fi->i = 0;
	fi->fill = 0;
	ft_bzero(fi->buff, GNL_BUFF + 1);
	return (fi);
}

static bool			is_fd(const void *a, const void *b)
{
	return (((t_fileinfo*)a)->fd == *(const int*)b);
}

static int			fill_line(t_fileinfo *fi, char **line)
{
	long	ret;
	long	end;
	char	*tmp;

	while ((ret = read(fi->fd, fi->buff, GNL_BUFF)) > 0)
	{
		fi->fill = ret;
		fi->buff[ret] = '\0';
		if ((end = ft_strchr(fi->buff, '\n') - fi->buff) >= 0)
		{
			fi->buff[end] = '\0';
			fi->i = end + 1;
			ASSERT(tmp = ft_strjoin(*line, fi->buff));
			free(*line);
			*line = tmp;
			return (1);
		}
		ASSERT(tmp = ft_strjoin(*line, fi->buff));
		free(*line);
		*line = tmp;
		fi->fill = 0;
	}
	ASSERT(ret >= 0);
	return (*line != NULL);
}

int					get_next_line(const int fd, char **line)
{
	static t_list	*fdlst = NULL;
	t_fileinfo		*fi;
	t_list			*node;
	long			end;

	ASSERT(line && fd >= 0);
	*line = NULL;
	if (!(node = ft_lstfind(fdlst, is_fd, &fd)))
		node = ft_lstpush(&fdlst, new_fi(fd), sizeof(t_fileinfo));
	fi = (t_fileinfo*)node->content;
	if (fi->fill - fi->i > 0)
	{
		end = ft_strchr(fi->buff + fi->i, '\n') - (fi->buff + fi->i);
		end = end >= 0 ? fi->i + end : fi->fill;
		fi->buff[end] = '\0';
		ASSERT(*line = ft_strdup(fi->buff + fi->i));
		fi->i = end + 1;
		if (end < fi->fill)
			return (1);
	}
	if ((end = fill_line(fi, line)) <= 0)
		ft_lstrm(&fdlst, node);
	return (end);
}
