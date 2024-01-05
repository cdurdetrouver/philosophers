/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbazart <gabriel.bazart@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 17:00:35 by gbazart           #+#    #+#             */
/*   Updated: 2024/01/05 00:49:30 by gbazart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (printf("Wrong number of arguments\n"), 1);
	if (ft_parse(&data, argc, argv))
		return (1);
	if (ft_data_init(&data))
		return (clean(&data), 1);
	if (data.nb_philo > 1)
	{
		if (start(&data))
			return (clean(&data), 1);
	}
	else
		start1(&data);
	return (clean(&data), 0);
}
