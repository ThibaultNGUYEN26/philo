/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 18:19:51 by thibnguy          #+#    #+#             */
/*   Updated: 2023/08/08 15:55:32 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	ft_check_eat_enough(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&(philo->after_food));
	philo->times_eaten++;
	if (philo->times_eaten == data->max_eat)
		data->enough_eaten++;
	if (data->enough_eaten == data->nb_philo)
	{
		pthread_mutex_lock(&(data->is_dead_mut));
		data->is_dead = 1;
		pthread_mutex_unlock(&(data->is_dead_mut));
	}
	pthread_mutex_unlock(&(philo->after_food));
}

void	ft_check_death_status(t_data *data, t_philo *philo)
{
	int	i;
	int	is_dead;

	while (1)
	{
		i = -1;
		while (++i < data->nb_philo)
		{
			is_dead = philo_death(&philo[i]);
			if (is_dead)
				break ;
		}
		if (is_dead)
			break ;
	}
}

void	ft_end_mutex(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
		pthread_mutex_destroy(&(data->forks[i]));
	pthread_mutex_destroy(&(data->print));
	pthread_mutex_destroy(&(data->is_dead_mut));
	pthread_mutex_destroy(&(data->philos->after_food));
	free(data->forks);
	free(data->thread_id);
	free(data->philos);
	free(data);
}
