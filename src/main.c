/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:10:05 by wnocchi           #+#    #+#             */
/*   Updated: 2024/02/18 16:33:01 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdlib.h>
#include <unistd.h>

int	main(int ac, char **av)
{
	t_utils	params;
	t_check	check;

	ft_bzero(&params, sizeof(params));
	ft_bzero(&check, sizeof(params));
	if (ac == 2)
	{
		if (parsing_map(&params, av[1]))
		{
			write(2, "Error:\nInvalid map.\n", 20);
			return (1);
		}
		if (!params.map)
			return (1);
		if (init_window_hooks(&params, &check))
		{
			destroy_images_map(&params, &check);
			exit(0);
		}
		else
			destroy_images_map(&params, &check);
	}
	return (0);
}
