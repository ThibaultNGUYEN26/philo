/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 18:19:51 by thibnguy          #+#    #+#             */
/*   Updated: 2023/08/03 13:06:48 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

uint64_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
	{
		printf("gettimeofday() FAILURE\n");
		exit(EXIT_FAILURE);
	}
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

int	ft_usleep(suseconds_t time)
{
	uint64_t	start;

	start = get_time();
	while ((get_time() - start) < (long unsigned int)time)
		usleep(time / 10);
	return (0);
}

void	ft_finish(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
		pthread_mutex_destroy(&(data->forks[i]));
	pthread_mutex_destroy(&(data->print));
	pthread_mutex_destroy(&(data->death));
	free(data->forks);
	free(data->thread_id);
	free(data->philos);
	free(data);
}
