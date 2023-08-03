/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 17:33:16 by thibnguy          #+#    #+#             */
/*   Updated: 2023/08/03 18:50:50 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	ft_printf(t_data *data, char *msg, long long int arg1, int arg2)
{
	pthread_mutex_lock(&(data->print));
	printf(WHITE"%lld\t%d\t", arg1, arg2);
	if (ft_strstr(msg, "second"))
		printf(YELLOW"%s\n"WHITE"%lld\t%d\t"RED"is eating", msg, arg1, arg2);
	else if (ft_strstr(msg, "fork"))
		printf(YELLOW"%s", msg);
	else if (ft_strstr(msg, "thinking"))
		printf(GREEN"%s", msg);
	else if (ft_strstr(msg, "sleeping"))
		printf(BLUE"%s", msg);
	else if (ft_strstr(msg, "dead"))
		printf(WHITERED"%s", msg);
	printf("\n"EOC);
	pthread_mutex_unlock(&(data->print));
}
