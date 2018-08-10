/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_room.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iosypenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 17:03:23 by iosypenk          #+#    #+#             */
/*   Updated: 2018/03/15 17:03:25 by iosypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_room				*link_new(void const *content)
{
	t_room	*new;

	if (!(new = (t_room *)malloc(sizeof(t_room))))
		return (NULL);
	if (!content)
		new->link = NULL;
	else
	{
		new->link = (void *)content;
		new->next = NULL;
	}
	return (new);
}

static void			make_link(t_room *room, t_room *link)
{
	g_s.link = 1;
	if (room->link != NULL)
		ft_add_list_back(&room->link, link_new(link));
	else if (room->link == NULL)
		room->link = link_new(link);
	if (link->link != NULL)
		ft_add_list_back(&link->link, link_new(room));
	else if (link->link == NULL)
		link->link = link_new(room);
	if (room->name == g_s.start && link->name == g_s.end)
		g_s.start_end = 1;
}

static int			find_link(t_room *head, char *link_name, t_room **link)
{
	*link = head;
	while (*link)
	{
		if (!ft_strcmp((*link)->name, link_name))
		{
			return (1);
		}
		*link = (*link)->next;
	}
	return (0);
}

static void			name(char *line, int len, char **tmp)
{
	int		i;

	i = 0;
	*tmp = ft_strnew(len - 1);
	while (i < len - 1)
	{
		(*tmp)[i] = line[i];
		i++;
	}
}

int					get_link(char *line, t_room **head)
{
	int		i;
	int		len;
	t_room	*room;
	t_room	*link;
	char	*tmp;

	room = *head;
	link = NULL;
	len = ft_strlen(line);
	i = 0;
	while (--len > 0 && line[len] != '-')
		i++;
	len = ft_strlen(line) - i;
	name(line, len, &tmp);
	while (room)
	{
		if (!ft_strcmp(tmp, room->name) && find_link(*head, line + len, &link))
		{
			make_link(room, link);
			i = -42;
		}
		room = room->next;
	}
	ft_strdel(&tmp);
	return (i == -42 ? 1 : 0);
}
