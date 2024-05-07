/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolau <tnicolau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:58:23 by tnicolau          #+#    #+#             */
/*   Updated: 2024/05/07 10:21:56 by tnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_fork_availability(t_philos *philos)
{
	pthread_mutex_lock(&philos->fork_mutex);
	if (philos->fork == true)
	{
		philos->fork = false;
		pthread_mutex_unlock(&philos->fork_mutex);
		philos->has_fork = true;
		pthread_mutex_lock(&philos->global->mutex);
		if (philos->global->stop == false)
		{
			pthread_mutex_lock(&philos->global->print);
			printf("%zu %d %s\n",
				(get_current_time() - philos->global->start_time),
				philos->id, "has taken a fork");
			pthread_mutex_unlock(&philos->global->print);
		}
		pthread_mutex_unlock(&philos->global->mutex);
	}
	else
		pthread_mutex_unlock(&philos->fork_mutex);
	return (0);
}

int	check_prev_fork_availability(t_philos *philos)
{
	pthread_mutex_lock(&philos->prev->fork_mutex);
	if (philos->prev->fork == true)
	{
		philos->prev->fork = false;
		pthread_mutex_unlock(&philos->prev->fork_mutex);
		philos->has_prev_fork = true;
		pthread_mutex_lock(&philos->global->mutex);
		if (philos->global->stop == false)
		{
			pthread_mutex_lock(&philos->global->print);
			printf("%zu %d %s\n",
				(get_current_time() - philos->global->start_time),
				philos->id, "has taken a fork");
			pthread_mutex_unlock(&philos->global->print);
		}
		pthread_mutex_unlock(&philos->global->mutex);
	}
	else
		pthread_mutex_unlock(&philos->prev->fork_mutex);
	return (0);
}

int	release_forks(t_philos *philos)
{
	pthread_mutex_lock(&philos->fork_mutex);
	philos->fork = true;
	philos->has_fork = false;
	pthread_mutex_unlock(&philos->fork_mutex);
	pthread_mutex_lock(&philos->prev->fork_mutex);
	philos->prev->fork = true;
	philos->has_prev_fork = false;
	pthread_mutex_unlock(&philos->prev->fork_mutex);
	return (0);
}
