/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 10:31:40 by wnocchi           #+#    #+#             */
/*   Updated: 2024/02/18 10:33:13 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_input(char c)
{
	if (c != '1' && c != '0' && c != 'E' && c != 'C' && c != 'P' && c != '\n')
		return (1);
	return (0);
}

int	check_map(t_utils *params)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (params->map[i])
	{
		j = 0;
		while (params->map[i][j])
		{
			if (check_input(params->map[i][j]) == 1)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
int	check_walls(t_utils *params)
{
	int i;
	
	i = 0;
	while (i < params->map_width)
	{
		if (params->map[0][i] != '1')
			return (1);
		i++;
	}
	i = 0;
	while (i < params->map_width)
	{
		if (params->map[params->map_height - 1][i] != '1')
			return (1);
		i++;
	}
	return (0);
}

int	check_map_edges(t_utils *params)
{
	int i;

	i = 0;
	while (i < params->map_height)
	{
		if(params->map[i][0] != '1' || 
				params->map[i][ft_strlen(params->map[i]) - 2] != '1')
			return (1);
		i++;
	}
	return (0);
}

int	check_line(t_utils *params)
{
	int i;

	i = 0;
	if (!params->map)
		return (1);
	while (i < params->map_height)
	{
		if ((int)ft_strlen(params->map[i]) - 1 == params->map_width)
		{
			if(params->map[i][ft_strlen(params->map[i]) - 1] != '\n')
				return (1);
			i++;
		}
		else
			return (1);
	}
	if (check_walls(params) || check_map_edges(params))
		return (1);
	return (0);
}
