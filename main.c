/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:11:35 by yoyohann          #+#    #+#             */
/*   Updated: 2022/07/01 05:28:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_myatoi(char *nbr)
{
	int	i;
	int	result;

	i = 0;
	result = 0;

	if (nbr[0] == '+')
		i++;
	while (nbr[i])
	{
		result = (result * 10) + ((int )nbr[i] - 48);
		i++;
	}
	return (result);
}
int ft_isvalid(int argc, char **argv)
{
    int i = 1;

    while (i < argc)
    {
        if(!(ft_isnum(argv[i])) || !(ft_isinrange(ft_myatoi(argv[i]))))
            return (0);
        i++;
    }
    return (1);
}

int	main(int argc, char **argv)
{
	t_rules	rules;
	t_philo phi;

	if (argc != 5 && argc != 6)
		return (ft_error_message(1));
	if (!ft_isvalid(argc, argv))
		return (ft_error_message(2));
	if (ft_rules_init(&rules, &phi, argv))
		return (1);
	if (ft_thread_create(&rules))
		return (1);
	return (0);
}
