/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 17:16:59 by thibnguy          #+#    #+#             */
/*   Updated: 2023/08/15 00:40:51 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char *argv[])
{
	t_data	*data;

	if (!ft_parsing(argc, argv))
		return (1);
	data = ft_init_philo(argc, argv);
	if (!data)
		return (1);
	ft_philo_maker(data);
	return (0);
}
