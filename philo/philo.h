/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbazart <gabriel.bazart@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 17:01:01 by gbazart           #+#    #+#             */
/*   Updated: 2023/12/19 19:31:25 by gbazart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data	t_data;

typedef struct s_fork
{
	int					id;
	pthread_mutex_t		fork;
}						t_fork;

typedef struct s_philo
{
	int					id;
	long				nb_meal;
	long				last_meal;
	bool				full;
	t_fork				*left_fork;
	t_fork				*right_fork;
	pthread_t			thread;
	t_data				*data;
}						t_philo;

struct					s_data
{
	long				nb_philo;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				max_meal;
	long				start;
	bool				end;
	t_philo				*philo;
	t_fork				*forks;
};

void					ft_error(const char *str);
long					ft_atol(const char *str);
void					ft_parse(t_data *data, int argc, char **argv);

#endif
