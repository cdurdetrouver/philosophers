/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbazart <gabriel.bazart@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 17:01:01 by gbazart           #+#    #+#             */
/*   Updated: 2024/01/05 01:38:59 by gbazart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int					id;
	long				nb_meal;
	size_t				last_meal;
	bool				full;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_t			thread;
	t_data				*data;
}						t_philo;

struct					s_data
{
	int					nb_philo;
	int					done;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	long				max_meal;
	size_t				start;
	bool				end;
	bool				wait;
	t_philo				*philo;
	pthread_mutex_t		*forks;
	pthread_t			check;
};

// print
void					print_status(t_philo *philo, char *status);
void					start1(t_data *data);

// init
int						ft_parse(t_data *data, int argc, char **argv);
int						ft_data_init(t_data *data);

// thread
int						start(t_data *data);

// utils
long int				ft_atol(char *str);
size_t					get_time(void);
bool					ft_isdigit(char *str);
int						ft_strcmp(const char *s1, const char *s2);
int						ft_usleep(size_t milliseconds);

// clean
void					clean(t_data *data);

#endif
