/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 14:36:18 by thibnguy          #+#    #+#             */
/*   Updated: 2023/07/08 16:42:15 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

// int	ft_strlen(char *s)
// {
// 	int	i;

// 	i = -1;
// 	while (s[++i])
// 		;
// 	return (i);
// }

int	ft_strlen(char *s)
{
	char	*tab;
	char	*dup;
	int		i;

	i = -1;
	while (s[++i])
		;
	dup = malloc(sizeof(char) * (i + 1));
	if (!dup)
		return (0);
	i = -1;
	while (s[++i])
		dup[i] = s[i];
	dup[i] = '\0';
	tab = malloc(sizeof(char) * (i + 1));
	if (!tab)
		return (free(dup), 0);
	i = -1;
	while (dup[++i])
		tab[i] = dup[i];
	tab[i] = '\0';
	i = -1;
	while (tab[++i])
		;
	return (free(dup), free(tab), i);
}
