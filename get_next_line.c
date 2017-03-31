/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okosiako <okosiako@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/28 15:26:35 by okosiako          #+#    #+#             */
/*   Updated: 2017/03/31 17:32:53 by okosiako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdbool.h>

bool		change_list(t_descript *list, char **line)
{
	char	*temp;
	size_t	len;

	temp = list->buff;
	len = ft_strchr(temp, '\n') ? ft_strchr(temp, '\n') - temp : 0;
	*line = ft_strsub(temp, 0, len ? len : ft_strlen(temp));
	list->buff = ft_strdup(&temp[len ? len + 1 : ft_strlen(temp)]);
	ft_memdel((void **)&temp);
	return (len ? true : false);
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

/*int			smt(int fd, char **line, t_descript **memory)
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
*/
int			get_next_line(const int fd, char **line)
{
	static t_descript	*memory;
	char				*b;
	char				*ta[2];
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
		ta[0] = *line;
		*line = ft_strjoin(ta[0], b);
		ft_strdel(&ta[0]);
		if (ft_strchr(b, '\n'))
		{
			*line[ft_strchr((*line), '\n') - (*line)] = '\0';
			temp ? temp->buff = ft_strdup(&b[ft_strchr(b, '\n') - b + 1]) :
				add_list(&memory, &b[ft_strchr(b, '\n') - b + 1], fd);
		}
	}
	return (**line ? 1 : 0);
}
