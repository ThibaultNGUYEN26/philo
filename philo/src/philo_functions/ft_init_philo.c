/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 17:22:34 by thibnguy          #+#    #+#             */
/*   Updated: 2023/08/16 14:12:51 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

t_data	*ft_init_philo(int argc, char *argv[])
{
	int		i;
	t_data	*data;

	data = malloc(sizeof(t_data) * 1);
	if (!data)
		return (NULL);
	data->nb_philo = ft_atoi(argv[1]);
	data->t_die = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
	if (argc == 5)
		data->max_eat = -1;
	else
		data->max_eat = ft_atoi(argv[5]);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
		return (NULL);
	i = -1;
	while (++i < data->nb_philo)
		pthread_mutex_init(&data->forks[i], NULL);
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->is_dead_mut, NULL);
	pthread_mutex_init(&data->enough_eaten_mut, NULL);
	data->start = get_time();
	return (data);
}

int	philo_death(t_philo *philo)
{
	t_data	*data;
	int		is_dead;

	data = philo->data;
	pthread_mutex_lock(&(data->is_dead_mut));
	if (data->is_dead != 1)
	{
		pthread_mutex_lock(&(philo->after_food));
		if ((philo->times_eaten != data->max_eat)
			&& (get_time() - philo->time_after_food) > data->t_die)
		{
			data->is_dead = 1;
			ft_printf(data, "is dead", get_time() - data->start, philo->id);
		}
		pthread_mutex_unlock(&(philo->after_food));
	}
	is_dead = data->is_dead;
	pthread_mutex_unlock(&(data->is_dead_mut));
	return (is_dead);
}

static int	ft_eating(t_philo *philo, t_data *data, int id)
{
	int	second_fork;

	second_fork = 0;
	if (id == 0)
		second_fork = data->nb_philo - 1;
	else
		second_fork = id - 1;
	pthread_mutex_lock(&(data->forks[id]));
	if (philo_death(philo))
		return (pthread_mutex_unlock(&(data->forks[id])));
	ft_printf(data, "has taken a fork", get_time() - data->start, philo->id);
	if (data->nb_philo == 1)
		return (pthread_mutex_unlock(&(data->forks[id])));
	pthread_mutex_lock(&(data->forks[second_fork]));
	if (philo_death(philo))
	{
		pthread_mutex_unlock(&(data->forks[second_fork]));
		pthread_mutex_unlock(&(data->forks[id]));
		return (0);
	}
	ft_printf(data, "is eating", get_time() - data->start, philo->id);
	ft_check_eat_enough(data, philo, second_fork, id);
	return (1);
}

void	*ft_thread(void *args)
{
	int			id;
	t_philo		*philo;
	t_data		*data;

	philo = (t_philo *)args;
	data = philo->data;
	id = philo->id;
	if (id % 2 == 0)
		ft_usleep(50);
	pthread_mutex_lock(&(philo->after_food));
	philo->times_eaten = 0;
	pthread_mutex_unlock(&(philo->after_food));
	while (1)
	{
		if (ft_eating(philo, data, id) == 0)
			break ;
		if (philo_death(philo))
			return (0);
		ft_printf(data, "is sleeping", get_time() - data->start, id);
		ft_usleep(data->t_sleep);
		if (philo_death(philo))
			return (0);
		ft_printf(data, "is thinking", get_time() - data->start, philo->id);
	}
	return (NULL);
}

void	ft_philo_maker(t_data *data)
{
	int		i;
	t_philo	*philo;

	data->is_dead = 0;
	philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!philo)
		return ;
	data->thread_id = malloc(sizeof(pthread_t) * data->nb_philo);
	if (!data->thread_id)
		return ;
	data->philos = philo;
	printf(WHITE"[TIME]  [ID]\t[MESSAGE]\n\n"EOC);
	i = -1;
	while (++i < data->nb_philo)
	{
		pthread_mutex_init(&philo[i].after_food, NULL);
		philo[i].time_after_food = get_time();
		philo[i].data = data;
		philo[i].id = i;
		pthread_create(&(data->thread_id[i]), NULL, &ft_thread, &(philo[i]));
	}
	ft_check_death_status(data, philo);
}
