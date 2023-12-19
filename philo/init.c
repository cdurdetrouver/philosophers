/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbazart <gabriel.bazart@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 18:57:44 by gbazart           #+#    #+#             */
/*   Updated: 2023/12/19 19:39:03 by gbazart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_parse(t_data *data, int argc, char **argv)
{
	data->nb_philo = ft_atol(argv[1]);
	if (data->nb_philo > 200)
		ft_error("Too many philosophers\n");
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	data->max_meal = -1;
	if (argc == 6)
		data->max_meal = ft_atol(argv[5]);
	if (data->time_to_die < 60 || data->time_to_eat < 60
		|| data->time_to_sleep < 60)
		ft_error("Time must be greater than 60ms\n");
}

void	ft_philo_init(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < data->nb_philo)
	{
		philo = data->philo + i;
		philo->id = i + 1;
		philo->full = false;
		philo->nb_meal = 0;
		philo->data = data;
		assign_forks(philo, data->forks, i);
	};
}

void	ft_data_init(t_data *data)
{
	int	i;

	data->end = false;
	data->philo = safe_malloc(data->nb_philo * sizeof(t_philo));
	data->forks = safe_malloc(data->nb_philo * sizeof(t_fork));
	i = -1;
	while (++i < data->nb_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].nb_meal = 0;
		data->philo[i].last_meal = data->start;
		data->philo[i].full = false;
		data->philo[i].data = data;
		data->philo[i].left_fork = &data->forks[i];
		data->philo[i].right_fork = &data->forks[(i + 1) % data->nb_philo];
		pthread_mutex_init(&data->forks[i].fork, NULL);
	}
}
