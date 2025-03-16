/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vaildate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halmuhis <halmuhis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 04:01:08 by halmuhis          #+#    #+#             */
/*   Updated: 2025/03/16 05:06:18 by halmuhis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static long ft_atio(const char *str)
{
	int		i;
	long	nbr;

	i = -1;
	nbr = 0;
	while (str[++i])
	{
		if(ft_isdigit(str[i]) == 0)
		{
			return (-1);
		}
		nbr = nbr * 10 + (str[i] - '0');
	}
	return (nbr);
}

void	vaildate_input(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc != 5 && argc != 6)
	{
		printf("Error: Wrong number of arguments\n");
		exit(1);
	}

	while (argv[++i])
	{
		if (ft_atio(argv[i]) == -1)
		{
			printf("Error: input must be number\n");
			exit(1);
		}
	}
	
	printf("%s\n", argv[1]);
}
