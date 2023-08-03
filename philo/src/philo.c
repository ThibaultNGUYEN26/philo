/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 17:16:59 by thibnguy          #+#    #+#             */
/*   Updated: 2023/07/24 17:38:50 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char *argv[])
{
	t_data	*data;

	if (!ft_parsing(argc, argv))
		return (EXIT_FAILURE);
	data = ft_init_philo(argc, argv);
	if (!data)
		return (EXIT_FAILURE);
	return (0);
	ft_philo_maker(data);
}
