/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:00:03 by yoyohann          #+#    #+#             */
/*   Updated: 2022/07/01 05:55:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_rules_init(t_rules *rules, t_philo *phi, char **argv)
{
//	t_philo *phi;
	rules->num_philo = ft_myatoi(argv[1]);
	rules->time_die = ft_myatoi(argv[2]);
	rules->time_eat = ft_myatoi(argv[3]);
	rules->time_sleep = ft_myatoi(argv[4]);
	rules->meal_count = 0;
	rules->died = 0;
	if (rules->num_philo < 1 || rules->time_die < 60
		|| rules->time_eat < 60 || rules->time_sleep < 60
		|| rules->num_philo > 200)
		return (1);
	if (argv[5])
	{
		rules->num_eat = ft_myatoi(argv[5]);
		if (rules->num_eat <= 0)
			return (1);
	}
	else
		rules->num_eat = -1;
	if (ft_philo_init(rules, phi))
		return (1);
	return (0);
}


int	ft_philo_init(t_rules *rules, t_philo *phi)
{
	int	i;

	i = rules->num_philo;
	while (--i >= 0)
	{
		rules->philosopher[i].id = i;
		rules->philosopher[i].x_ate = 0;
		rules->philosopher[i].left_fork = i;
		rules->philosopher[i].right_fork = (i + 1) % rules->num_philo;
		rules->philosopher[i].time_end = 0;
		rules->philosopher[i].rules = rules;
	}
	if (ft_mutex_init(rules, phi))
		return (1);
	return (0);
}

int	ft_mutex_init(t_rules *rules, t_philo *phi)
{
	int	i;

	i = rules->num_philo;
	while (--i >= 0)
	{
		if (pthread_mutex_init(&(rules->fork[i]), NULL))
			return (1);
	}
	if (pthread_mutex_init(&(rules->message), NULL))
		return (1);
	if (pthread_mutex_init(&(rules->meal), NULL))
		return (1);
	if (pthread_mutex_init(&(phi->mxate), NULL))
		return (1);
	return (0);
}
