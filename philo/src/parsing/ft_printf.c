/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 17:33:16 by thibnguy          #+#    #+#             */
/*   Updated: 2023/08/16 11:51:57 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	ft_printf(t_data *data, char *msg, long long int arg1, int arg2)
{
	pthread_mutex_lock(&(data->print));
	if (ft_strstr(msg, "eating"))
	{
		printf(WHITE"%lld\t%d\t"YELLOW"has taken a fork\n", arg1, arg2 + 1);
		printf(WHITE"%lld\t%d\t"RED"is eating", arg1, arg2 + 1);
	}
	else
	{
		printf(WHITE"%lld\t%d\t", arg1, arg2 + 1);
		if (ft_strstr(msg, "fork"))
			printf(YELLOW"%s", msg);
		else if (ft_strstr(msg, "thinking"))
			printf(GREEN"%s", msg);
		else if (ft_strstr(msg, "sleeping"))
			printf(BLUE"%s", msg);
		else if (ft_strstr(msg, "dead"))
			printf(WHITERED"%s", msg);
	}
	printf("\n"EOC);
	pthread_mutex_unlock(&(data->print));
}
