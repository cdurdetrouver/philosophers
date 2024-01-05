/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbazart <gabriel.bazart@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 16:21:13 by gbazart           #+#    #+#             */
/*   Updated: 2024/01/05 00:38:36 by gbazart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start1(t_data *data)
{
	printf("0 1 is thinking\n");
	printf("0 1 has taken a fork\n");
	printf("%ld 1 died\n", data->time_to_die);
}

void	print_status(t_philo *philo, char *status)
{
	if (!philo->data->end)
	{
		printf("%ld %d %s\n", get_time() - philo->data->start, philo->id,
			status);
		if (!ft_strcmp(status, "died"))
			philo->data->end = true;
	}
}
