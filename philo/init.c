/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbazart <gbazart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 16:22:36 by gbazart           #+#    #+#             */
/*   Updated: 2024/01/06 17:46:38 by gbazart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_data_init(t_data *data)
{
	int	i;

	data->start = get_time();
	data->end = false;
	data->done = 0;
	data->wait = true;
	data->philo = malloc(sizeof(t_philo) * data->nb_philo);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->philo || !data->forks)
		return (printf("Malloc error\n"), 1);
	i = -1;
	while (++i < data->nb_philo)
		pthread_mutex_init(&data->forks[i], NULL);
	i = -1;
	while (++i < data->nb_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].nb_meal = 0;
		data->philo[i].full = false;
		data->philo[i].left_fork = &data->forks[i];
		data->philo[i].right_fork = &data->forks[(i + 1) % data->nb_philo];
		data->philo[i].data = data;
		data->philo[i].is_eating = false;
	}
	return (0);
}

int	ft_parse(t_data *data, int argc, char **argv)
{
	int	i;

	i = 0;
	while (++i < argc)
	{
		if (!ft_isdigit(argv[i]))
			return (printf("Arguments must be positive numbers\n"), 1);
	}
	if (ft_atol(argv[1]) > 200)
		return (printf("Too many philosophers\n"), 1);
	if (ft_atol(argv[2]) < 60 || ft_atol(argv[3]) < 60 || ft_atol(argv[4]) < 60)
		return (printf("Time must be at least 60ms\n"), 1);
	data->nb_philo = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		data->max_meal = ft_atol(argv[5]);
	else
		data->max_meal = -1;
	return (0);
}
