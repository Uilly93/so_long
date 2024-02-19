/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:10:05 by wnocchi           #+#    #+#             */
/*   Updated: 2024/02/19 09:38:00 by wnocchi          ###   ########.fr       */
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
	ft_bzero(&check, sizeof(check));
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
	else
		write(2, "Error:\nInvalid arguments\n", 25);
	return (0);
}
