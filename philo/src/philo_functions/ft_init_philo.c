/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 17:22:34 by thibnguy          #+#    #+#             */
/*   Updated: 2023/07/24 18:40:51 by thibnguy         ###   ########.fr       */
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
	data->is_dead = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
		return (NULL);
	i = -1;
	while (++i < data->nb_philo)
		pthread_mutex_init(&data->forks[i], NULL);
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->death, NULL);
	data->start = get_time();
	return (data);
}

static int	philo_death(t_philo philo)
{
	t_data	*data;
	int		i;

	data = philo.data;
	pthread_mutex_lock(&(data->death));
	if (data->is_dead == 1)
	{
		pthread_mutex_unlock(&(data->death));
		return (data->is_dead);
	}
	if (data->nb_philo == 1)
	{
		pthread_mutex_lock(&(data->print));
		printf("%lld Philosopher %d is dead\n", get_time() - data->start, philo.id);
		pthread_mutex_unlock(&(data->print));
		data->is_dead = 1;
	}
	else if ((philo.times_eaten != data->max_eat) && (get_time() - philo.time_after_food) >= data->t_die)
	{
		data->is_dead = 1;
		pthread_mutex_lock(&(data->print));
		printf("%lld Philosopher %d is dead\n", get_time() - data->start, philo.id);
		pthread_mutex_unlock(&(data->print));
		i = -1;
		while (++i < data->nb_philo)
			pthread_mutex_unlock(&(data->forks[i]));
	}
	else
		data->is_dead = 0;
	pthread_mutex_unlock(&(data->death));
	return (data->is_dead);
}

static int	philo_food(t_philo philo, t_data *data, int id)
{
	int	second_fork;

	if (id == 0)
		second_fork = data->nb_philo - 1;
	else
		second_fork = id - 1;
	pthread_mutex_lock(&(data->forks[id]));
	pthread_mutex_lock(&(data->print));
	printf("%lld %d took his first fork\n", get_time() - data->start, id);
	pthread_mutex_unlock(&(data->print));
	if (philo_death(philo))
		return (0);
	pthread_mutex_lock(&(data->forks[second_fork]));
	pthread_mutex_lock(&(data->print));
	printf("%lld %d took his second fork\n", get_time() - data->start, id);
	printf("%lld %d is eating\n", get_time() - data->start, id);
	pthread_mutex_unlock(&(data->print));
	if (philo_death(philo))
		return (0);
	ft_usleep(data->t_eat);
	philo.time_after_food = get_time();
	pthread_mutex_unlock(&(data->forks[id]));
	pthread_mutex_unlock(&(data->forks[second_fork]));
	philo.times_eaten++;
	return (1);
}

static void	*thread_function(void *args)
{
	int			id;
	t_philo		philo;
	t_data		*data;

	philo = *((t_philo *)args);
	data = philo.data;
	id = philo.id;
	if (id % 2 == 0)
		ft_usleep(50);
	philo.time_after_food = get_time();
	philo.times_eaten = 0;
	while (1)
	{
		if (((data->max_eat != -1) && (philo.times_eaten < data->max_eat)) || data->max_eat == -1)
			if (philo_food(philo, data, id) == 0)
				break;
		ft_printf(data, "is sleeping", get_time() - data->start, id);
		ft_usleep(data->t_sleep);
		if (philo_death(philo))
			break;
		pthread_mutex_lock(&(data->print));
		printf("%lld %d is thinking\n", get_time() - data->start, id);
		pthread_mutex_unlock(&(data->print));
	}
	return (NULL);
}

void	ft_philo_maker(t_data *data)
{
	int		i;
	t_philo	*philo;

	philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!philo)
		return ;
	data->thread_id = malloc(sizeof(pthread_t) * data->nb_philo);
	if (!data->thread_id)
		return ;
	data->philos = philo;
	i = -1;
	while (++i < data->nb_philo)
	{
		philo[i].data = data;
		philo[i].id = i;
		pthread_create(&(data->thread_id[i]), NULL, &thread_function, &(philo[i]));
	}
	i = -1;
	while (++i < data->nb_philo)
		pthread_join(data->thread_id[i], NULL);
	ft_finish(data);
}