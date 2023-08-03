/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 14:34:47 by thibnguy          #+#    #+#             */
/*   Updated: 2023/07/24 17:15:22 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	ft_parsing(int argc, char *argv[])
{
	int	i;
	int	j;

	i = 0;
	if (argc < 5 || argc >= 7)
	{
		printf(GREEN"[USING] : ./philo [nb_philo] [time_to_die] \
[time_to_eat] [time_to_sleep] [(nb_of_times_each_philo_must_eat)] \n"EOC);
		return (0);
	}
	while (++i < argc)
	{
		j = -1;
		while (++j < ft_strlen(argv[i]))
		{
			if (ft_strlen(argv[i]) > 11 || ft_atoi(argv[i])
				> INT_MAX || !ft_isdigit(argv[i][j])
				|| argv[i][j] == '-')
			{
				printf(GREEN"[USING] : ./philo [nb_philo] [time_to_die] \
[time_to_eat] [time_to_sleep] [(nb_of_times_each_philo_must_eat)] \n"EOC);
				return (0);
			}
		}
	}
	return (1);
}
