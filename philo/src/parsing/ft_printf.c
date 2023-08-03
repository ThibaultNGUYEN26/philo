/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 17:33:16 by thibnguy          #+#    #+#             */
/*   Updated: 2023/07/24 18:41:11 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	ft_printf(t_data *data, char *msg, long long int arg1, int arg2)
{
	pthread_mutex_lock(&(data->print));
	if (!data->is_dead)
	{
		printf(WHITE"%lld %d "EOC, arg1, arg2);
		if (ft_strstr(msg, "eating"))
			printf(RED);
		else if (ft_strstr(msg, "forks"))
			printf(GRAY);
		else if (ft_strstr(msg, "thinking"))
			printf(GREEN);
		else if (ft_strstr(msg, "sleeping"))
			printf(BLUE);
		printf("%s\n"EOC, msg);
	}
	pthread_mutex_unlock(&(data->print));
}
