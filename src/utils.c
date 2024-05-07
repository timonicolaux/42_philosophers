/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolau <tnicolau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:18:51 by tnicolau          #+#    #+#             */
/*   Updated: 2024/05/07 10:15:38 by tnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_msg(t_philos *philos, char *message)
{
	pthread_mutex_lock(&philos->global->mutex);
	if (philos->global->stop == false)
	{
		pthread_mutex_lock(&philos->global->print);
		printf("%zu %d %s\n", (get_current_time() - philos->global->start_time),
			philos->id, message);
		pthread_mutex_unlock(&philos->global->print);
	}
	pthread_mutex_unlock(&philos->global->mutex);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

void	destroy_all_threads(t_philos *philos, t_global *global)
{
	t_philos	*philos_cpy;

	philos_cpy = philos;
	if (philos)
	{
		while (philos)
		{
			pthread_mutex_destroy(&philos->fork_mutex);
			philos = philos->next;
		}
	}
	philos = philos_cpy;
	pthread_mutex_destroy(&global->mutex);
	pthread_mutex_destroy(&global->print);
	pthread_mutex_destroy(&global->num_meals_mutex);
}
