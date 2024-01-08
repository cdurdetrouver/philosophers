/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbazart <gbazart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:29:16 by gbazart           #+#    #+#             */
/*   Updated: 2024/01/06 18:33:09 by gbazart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	philo->is_eating = true;
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	philo->last_meal = get_time();
	philo->nb_meal++;
	philo->is_eating = false;
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
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
		ft_usleep(50);
	}
	while (!philo->data->end && !philo->full)
	{
		eat(philo);
		print_status(philo, "is sleeping");
		ft_usleep(philo->data->time_to_sleep);
		print_status(philo, "is thinking");
	}
	return (NULL);
}

int	foreachphilo(int i, t_data *data)
{
	if (get_time() - data->philo[i].last_meal > data->time_to_die
		&& !data->philo[i].is_eating)
	{
		print_status(&data->philo[i], "died");
		data->end = true;
		return (1);
	}
	if (data->philo[i].nb_meal == data->max_meal && !data->philo[i].full)
	{
		data->done++;
		data->philo[i].full = true;
	}
	if (data->done == data->nb_philo)
	{
		data->end = true;
		return (1);
	}
	return (0);
}

void	*check(void *args)
{
	t_data	*data;
	int		i;

	data = (t_data *)args;
	while (data->wait)
		;
	ft_usleep(50);
	while (!data->end)
	{
		i = -1;
		while (++i < data->nb_philo && !data->end)
		{
			if (foreachphilo(i, data))
				return (NULL);
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
