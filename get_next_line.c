/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okosiako <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/28 15:26:35 by okosiako          #+#    #+#             */
/*   Updated: 2016/12/30 12:43:09 by okosiako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void		change_list(t_descript *list)
{
	char	*temp;

	temp = list->buff;
	if (ft_strchr(temp, '\n'))
		list->buff = ft_strsub(temp, ft_strchr(temp, '\n') - temp + 1,
				(size_t)(ft_strlen(list->buff) - (ft_strchr(temp, '\n') - temp)
					+ 1));
	ft_memdel((void **)&temp);
}

void		add_list(t_descript **memory, char *str, int fd)
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

t_descript	*was(t_descript *list, int fd)
{
	while (list)
	{
		if (!(list->fd ^ fd))
			return (list);
		list = list->next;
	}
	return (0);
}

int			smt(int fd, char **line, t_descript **memory)
{
	char		b[BUFF_SIZE + 1];
	int			ret;
	t_descript	*temp;
	char		*ta[2];

	while ((ret = read(fd, b, BUFF_SIZE)))
	{
		b[ret] = '\0';
		ta[0] = *line;
		if (ft_strchr(b, '\n'))
		{
			ta[1] = ft_strsub(b, 0, (ft_strchr(b, '\n') - b));
			*line = ft_strjoin(ta[0], ta[1]);
			ft_memdel((void **)&ta[1]);
			if ((temp = was(*memory, fd)))
				temp->buff = ft_strdup((b + (ft_strchr(b, '\n') - b) + 1));
			else
				add_list(memory, (b + (ft_strchr(b, '\n') - b) + 1), fd);
			ft_memdel((void **)&ta[0]);
			return (1);
		}
		*line = ft_strjoin(ta[0], b);
		ft_memdel((void **)&ta[0]);
	}
	return ((*line[0]) ? 1 : 0);
}

int			get_next_line(const int fd, char **line)
{
	char				b[BUFF_SIZE + 1];
	char				*ta[2];
	t_descript			*temp;
	static t_descript	*memory = NULL;

	if (!line || (read(fd, b, 0)) || BUFF_SIZE < 1)
		return (-1);
	*line = ft_strnew(0);
	if ((temp = was(memory, fd)) && temp->buff)
	{
		ta[0] = *line;
		if (ft_strchr(temp->buff, '\n'))
		{
			*line = ft_strjoin(ta[0], ft_strsub(temp->buff, 0,
						ft_strchr(temp->buff, '\n') - temp->buff));
			change_list(temp);
			ft_memdel((void **)&ta[0]);
			return (1);
		}
		*line = ft_strjoin(ta[0], temp->buff);
		ft_memdel((void **)&temp->buff);
	}
	return (smt(fd, line, &memory));
}
