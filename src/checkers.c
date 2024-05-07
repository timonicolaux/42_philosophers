/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolau <tnicolau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:15:10 by tnicolau          #+#    #+#             */
/*   Updated: 2024/05/07 10:05:51 by tnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_num_meals(t_philos *philos)
{
	if (philos->args->num_of_meals == -1)
		return (0);
	pthread_mutex_lock(&philos->global->num_meals_mutex);
	if (philos->global->num_meals == philos->args->philosophers)
	{
		pthread_mutex_unlock(&philos->global->num_meals_mutex);
		pthread_mutex_lock(&philos->global->mutex);
		philos->global->stop = true;
		pthread_mutex_unlock(&philos->global->mutex);
		return (1);
	}
	pthread_mutex_unlock(&philos->global->num_meals_mutex);
	return (0);
}

int	check_if_dead(t_philos *philos, size_t param, size_t last_meal, size_t time)
{
	if (((time + param) - last_meal) > (philos->args->time_to_die))
	{
		usleep(param);
		pthread_mutex_lock(&philos->global->mutex);
		if (philos->global->stop == false)
		{
			pthread_mutex_lock(&philos->global->print);
			printf("%zu %d died\n", (philos->args->time_to_die
					+ last_meal - philos->global->start_time),
				philos->id);
			philos->global->stop = true;
			pthread_mutex_unlock(&philos->global->mutex);
			pthread_mutex_unlock(&philos->global->print);
			return (0);
		}
		pthread_mutex_unlock(&philos->global->mutex);
		return (0);
	}
	return (1);
}

int	check_if_ready(t_philos *philos)
{
	pthread_mutex_lock(&philos->global->mutex);
	if (philos->global->ready == true)
		return (pthread_mutex_unlock(&philos->global->mutex), 1);
	pthread_mutex_unlock(&philos->global->mutex);
	return (0);
}

int	check_if_stop(t_philos *philos)
{
	if (check_num_meals(philos))
		return (0);
	pthread_mutex_lock(&philos->global->mutex);
	if (philos->global->stop == true)
		return (pthread_mutex_unlock(&philos->global->mutex), 0);
	pthread_mutex_unlock(&philos->global->mutex);
	return (1);
}
