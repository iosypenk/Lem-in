/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iosypenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 16:45:37 by iosypenk          #+#    #+#             */
/*   Updated: 2018/03/15 16:45:41 by iosypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int				valid_link_line(char *l)
{
	int		i;

	i = 0;
	if (l && ft_isspace(l[0]) && l[0] != 'L')
		return (0);
	while (l[i] > 32 && l[i] < 127 && l[i] != '-')
		i++;
	if (l[i] == '-')
	{
		i++;
		while (l[i] && l[i] > 32 && l[i] < 127 && l[i] != '-')
			i++;
		if (l[i] == '\0')
			return (1);
	}
	return (0);
}

int				id_ants(char *line)
{
	g_s.nbr_ant = ft_atoi(line);
	if (ft_isspace(line[0]) || g_s.nbr_ant <= 0 ||
		line[ft_intlen(g_s.nbr_ant)] != '\0')
	{
		return (0);
	}
	g_s.ant = 1;
	return (1);
}

int				id_link(char *l)
{
	int	i;

	i = 0;
	while (l && l[i] && l[0] != 'L')
	{
		if (l[i - 1] > 32 && l[i - 1] < 127 && l[i] == '-' &&
				l[i + 1] > 32 && l[i + 1] < 127)
			return (1);
		i++;
	}
	return (0);
}

static int		id_command(char *line)
{
	if (ft_isspace(line[0]))
		return (0);
	if (!ft_strcmp(line, "##start") && g_s.s == 0 && g_s.k == 0)
	{
		g_s.s = 1;
		g_s.k = 1;
		return (1);
	}
	if (!ft_strcmp(line, "##end") && g_s.e == 0 && g_s.k == 0)
	{
		g_s.e = 1;
		g_s.k = 1;
		return (1);
	}
	return (0);
}

int				id_comment(char *line)
{
	if (line && line[1] == '#' && line[2] != '#')
	{
		if ((!ft_strcmp(line, "##start") || !ft_strcmp(line, "##end"))
			&& !id_command(line))
			return (0);
	}
	return (1);
}
