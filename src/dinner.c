/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolau <tnicolau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:16:48 by tnicolau          #+#    #+#             */
/*   Updated: 2024/05/07 10:10:33 by tnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*dine(void *pointer)
{
	t_philos	*philos;

	philos = (t_philos *)pointer;
	while (!check_if_ready(philos))
		;
	if (!philos->last_meal)
		philos->last_meal = philos->global->start_time;
	if (philos->id % 2)
	{
		think(philos);
		usleep(30 * philos->args->philosophers);
	}
	while (42)
	{
		if (!eat(philos))
			break ;
		if (!check_if_stop(philos))
			break ;
		if (!sleeping(philos))
			break ;
		think(philos);
	}
	return (pointer);
}

void	think(t_philos *philos)
{
	print_msg(philos, "is thinking");
}

int	sleeping(t_philos *philos)
{
	size_t	time;

	print_msg(philos, "is sleeping");
	time = get_current_time();
	if (!check_if_dead(philos, philos->args->time_to_sleep,
			philos->last_meal, time))
		return (0);
	time = (get_current_time() - time);
	ft_usleep(philos->args->time_to_sleep - time);
	return (1);
}

int	eat(t_philos *philos)
{
	size_t	time;

	if (grab_forks(philos))
		return (release_forks(philos), 0);
	print_msg(philos, "is eating");
	time = get_current_time();
	if (!check_if_dead(philos, philos->args->time_to_eat,
			philos->last_meal, time))
		return (release_forks(philos), 0);
	if (philos->args->num_of_meals > 0)
	{
		pthread_mutex_lock(&philos->global->num_meals_mutex);
		philos->meals += 1;
		if (philos->meals == philos->args->num_of_meals)
			philos->global->num_meals += 1;
		pthread_mutex_unlock(&philos->global->num_meals_mutex);
	}
	time = (get_current_time() - time);
	ft_usleep(philos->args->time_to_eat - time);
	philos->last_meal = (get_current_time());
	release_forks(philos);
	return (1);
}

int	grab_forks(t_philos *philos)
{
	while (philos->has_fork == false || philos->has_prev_fork == false)
	{
		if (philos->id % 2)
		{
			if (philos->has_fork == false)
				check_fork_availability(philos);
			if (philos->has_fork == true && philos->has_prev_fork == false)
				check_prev_fork_availability(philos);
		}
		else
		{
			if (philos->has_prev_fork == false)
				check_prev_fork_availability(philos);
			if (philos->has_prev_fork == true && philos->has_fork == false)
				check_fork_availability(philos);
		}
		if (!check_if_stop(philos))
			return (1);
		usleep(10 * philos->args->philosophers);
	}
	return (0);
}
