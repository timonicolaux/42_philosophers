/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolau <tnicolau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:17:11 by tnicolau          #+#    #+#             */
/*   Updated: 2024/05/07 10:12:20 by tnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	launch_threads(t_philos *philos, t_global *global)
{
	if (!create_threads(philos))
		return (-1);
	pthread_mutex_lock(&global->mutex);
	usleep(15 * global->args->philosophers);
	global->start_time = get_current_time();
	global->ready = true;
	pthread_mutex_unlock(&global->mutex);
	if (!join_threads(philos))
		return (-1);
	return (0);
}

void	*create_threads(t_philos *philos)
{
	t_philos	*philos_cpy;

	philos_cpy = philos;
	while (philos)
	{
		if (pthread_create(&philos->thread, NULL, &dine, philos) != 0)
		{
			printf("Error during thread creation\n");
			return (NULL);
		}
		philos = philos->next;
	}
	philos = philos_cpy;
	return (philos);
}

void	*join_threads(t_philos *philos)
{
	t_philos	*philos_cpy;

	philos_cpy = philos;
	while (philos)
	{
		if (pthread_join(philos->thread, NULL) != 0)
		{
			printf("Error during thread join\n");
			return (NULL);
		}
		usleep(150);
		philos = philos->next;
	}
	philos = philos_cpy;
	return (philos);
}
