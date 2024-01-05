/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbazart <gabriel.bazart@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:24:59 by gbazart           #+#    #+#             */
/*   Updated: 2024/01/05 01:26:38 by gbazart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean(t_data *data)
{
	int	i;

	i = -1;
	if (data->philo)
		free(data->philo);
	if (!data->forks)
		return ;
	while (++i < data->nb_philo)
		pthread_mutex_destroy(&data->forks[i]);
	free(data->forks);
}
