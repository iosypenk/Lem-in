/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iosypenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 12:40:30 by iosypenk          #+#    #+#             */
/*   Updated: 2018/03/28 12:40:33 by iosypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		ft_add_list_back(t_room **head, t_room *new)
{
	t_room	*list;

	list = *head;
	if (!new)
		return ;
	if (list)
	{
		while (list->next)
			list = list->next;
		list->next = new;
	}
	else
		*head = new;
}

int			ft_intlen(int nb)
{
	int		cnt;

	cnt = 0;
	if (nb <= 0)
		cnt = 1;
	while (nb != 0)
	{
		nb = nb / 10;
		cnt++;
	}
	return (cnt);
}

void		save_map(char *line, t_room **head)
{
	t_room	*tmp;

	if (!line || !(tmp = malloc(sizeof(t_room))))
		return ;
	tmp->name = ft_strdup(line);
	tmp->next = NULL;
	ft_add_list_back(head, tmp);
}

void		print_map(t_room *head)
{
	t_room	*list;

	if (!head)
		error();
	list = head;
	while (list)
	{
		ft_printf("%s\n", list->name);
		list = list->next;
	}
	write(1, "\n", 1);
}

void		error(void)
{
	ft_printf(RED"ERROR\n"RC);
	exit(0);
}
