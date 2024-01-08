/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbazart <gbazart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 18:34:13 by gbazart           #+#    #+#             */
/*   Updated: 2024/01/06 18:34:13 by gbazart          ###   ########.fr       */
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
