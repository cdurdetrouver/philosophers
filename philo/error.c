/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbazart <gabriel.bazart@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 18:55:21 by gbazart           #+#    #+#             */
/*   Updated: 2023/12/19 19:34:19 by gbazart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error(const char *str)
{
	printf("%s\n", str);
	exit(1);
}

void	*ft_safe_malloc(size_t size)
{
	void	*ret;

	ret = malloc(size);
	if (NULL == ret)
		ft_error("Error with the malloc");
	return (ret);
}
