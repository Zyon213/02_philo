/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:17:44 by yoyohann          #+#    #+#             */
/*   Updated: 2022/06/30 16:21:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_error_message(int n)	
{
	if (n == 1)
		printf("Error Invalid number of arguments.\n");
	else if (n == 2)
		printf("Error one of the argument is invalid.\n");
	else if (n == 3)
		printf("Error philosopher initializing.\n");
	else if (n == 4)
		printf("Error Mutex initializing.\n");
	else if (n == 5)
		printf("Error creating thread.\n");	
	return (1);
}

void	ft_display_message(t_rules *rules, int id, char *msg)
{
	pthread_mutex_lock(&(rules->message));
	if (!(rules->died))
	{
		printf("%lld ", ft_current_time() - rules->time_start);
		printf("%d ", id + 1);
		printf("%s\n", msg);
	}
	pthread_mutex_unlock(&(rules->message));
	return ;
}

int	ft_isnum(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_isinrange(int num)
{
	if (num < 1 || num > 2147483647)
		return (0);
	return (1);
}