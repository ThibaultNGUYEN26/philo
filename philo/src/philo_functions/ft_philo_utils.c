/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 18:19:51 by thibnguy          #+#    #+#             */
/*   Updated: 2023/08/15 00:58:05 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	ft_check_eat_enough(t_data *data, t_philo *philo, int sec_fork, int id)
{
	ft_usleep(data->t_eat);
	pthread_mutex_lock(&(philo->after_food));
	philo->times_eaten++;
	philo->time_after_food = get_time();
	pthread_mutex_unlock(&(philo->after_food));
	pthread_mutex_unlock(&(data->forks[id]));
	pthread_mutex_unlock(&(data->forks[sec_fork]));
	if (data->max_eat != -1)
	{
		pthread_mutex_lock(&(data->enough_eaten_mut));
		if (philo->times_eaten == data->max_eat)
			data->enough_eaten++;
		if (data->enough_eaten == data->nb_philo)
		{
			pthread_mutex_lock(&(data->is_dead_mut));
			data->is_dead = 1;
			pthread_mutex_unlock(&(data->is_dead_mut));
		}
		pthread_mutex_unlock(&(data->enough_eaten_mut));
	}
	if (philo_death(philo))
		return ;
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
	i = -1;
	while (++i < data->nb_philo)
		pthread_join(data->thread_id[i], NULL);
	ft_end_mutex(data);
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
	pthread_mutex_destroy(&(data->enough_eaten_mut));
	free(data->forks);
	free(data->thread_id);
	free(data->philos);
	free(data);
}
