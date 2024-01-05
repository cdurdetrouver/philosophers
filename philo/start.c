/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbazart <gabriel.bazart@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:29:16 by gbazart           #+#    #+#             */
/*   Updated: 2024/01/05 03:41:43 by gbazart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	philo->last_meal = get_time();
	philo->nb_meal++;
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	sleeping(t_philo *philo)
{
	print_status(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->data->wait)
		;
	philo->last_meal = get_time();
	if (philo->id % 2 == 0 || philo->id == philo->data->nb_philo)
	{
		print_status(philo, "is thinking");
		ft_usleep((philo->data->time_to_eat * 2 - philo->data->time_to_sleep)
			* 0.42);
	}
	while (!philo->data->end && !philo->full)
	{
		eat(philo);
		sleeping(philo);
		print_status(philo, "is thinking");
		ft_usleep((philo->data->time_to_eat * 2 - philo->data->time_to_sleep)
			* 0.42);
	}
	return (NULL);
}

void	*check(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (data->wait)
		;
	while (!data->end)
	{
		i = -1;
		while (++i < data->nb_philo && !data->end)
		{
			if (get_time() - data->philo[i].last_meal > data->time_to_die)
				return (print_status(&data->philo[i], "died"), data->end = true,
					NULL);
			if (data->philo[i].nb_meal == data->max_meal
				&& !data->philo[i].full)
			{
				data->done++;
				data->philo[i].full = true;
			}
			if (data->done == data->nb_philo)
				return (data->end = true, NULL);
		}
	}
	return (NULL);
}

int	start(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
	{
		if (pthread_create(&data->philo[i].thread, NULL, &routine,
				&data->philo[i]))
			return (printf("Error: pthread_create\n"), 1);
	}
	if (pthread_create(&data->check, NULL, &check, data))
		return (printf("Error: pthread_create\n"), 1);
	data->start = get_time();
	data->wait = false;
	i = -1;
	while (++i < data->nb_philo)
	{
		if (pthread_join(data->philo[i].thread, NULL))
			return (printf("Error: pthread_join\n"), 1);
	}
	if (pthread_join(data->check, NULL))
		return (printf("Error: pthread_join\n"), 1);
	return (0);
}
