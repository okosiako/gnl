/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okosiako <okosiako@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/28 15:26:35 by okosiako          #+#    #+#             */
/*   Updated: 2017/04/01 18:41:55 by okosiako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdbool.h>

bool		change_list(t_descript *l, char **line)
{
	char	*tmp_line;
	char	*tmp_buff;
	int		len;

	len = ft_strchr(l->buff, '\n') ? ft_strchr(l->buff, '\n') - l->buff : -1;
	tmp_line = *line;
	*line = ft_strsub(l->buff, 0, len != -1 ? (size_t)len : ft_strlen(l->buff));
	ft_strdel(&tmp_line);
	tmp_buff = l->buff;
	l->buff = len != -1 ? ft_strdup(&(l->buff[(size_t)(len + 1)])) :
						ft_strnew(0);
	ft_strdel(&tmp_buff);
	return (len != -1 ? true : false);
}

void		add_list(t_descript **memory, const char *str, const int fd)
{
	t_descript *temp;

	temp = NULL;
	if (!(temp = (t_descript *)malloc(sizeof(t_descript))))
		return ;
	temp->fd = fd;
	temp->buff = ft_strdup(str);
	temp->next = *memory;
	*memory = temp;
}

t_descript	*was(t_descript *list, const int fd)
{
	while (list)
	{
		if (!(list->fd ^ fd))
			return (list);
		list = list->next;
	}
	return (0);
}

int			get_next_line(const int fd, char **line)
{
	static t_descript	*memory;
	char				*b;
	char				*ta;
	t_descript			*temp;
	bool				get_a_line;

	if (!line || BUFF_SIZE < 1 || (read(fd, (b = ft_strnew(BUFF_SIZE)), 0)))
		return (-1);
	get_a_line = false;
	*line = ft_strnew(0);
	if ((temp = was(memory, fd)) && temp->buff)
		get_a_line = change_list(temp, line);
	while (!get_a_line && read(fd, b, BUFF_SIZE))
	{
		ta = *line;
		*line = ft_strjoin(ta, b);
		ft_strdel(&ta);
		if (ft_strchr(b, '\n'))
		{
			temp ? temp->buff = ft_strdup(&b[ft_strchr(b, '\n') - b + 1]) :
				add_list(&memory, &b[ft_strchr(b, '\n') - b + 1], fd);
			(*line)[ft_strchr((*line), '\n') - (*line)] = '\0';
			break ;
		}
		ft_bzero(b, ft_strlen(b));
	}
	ft_strdel(&b);
	return ((*line)[0] || get_a_line ? 1 : 0);
}
