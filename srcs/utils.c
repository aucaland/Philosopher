/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucaland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 11:13:58 by aucaland          #+#    #+#             */
/*   Updated: 2023/02/27 14:13:43 by aucaland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philosophers.h"

static int	is_space(const char str)
{
	if (str == '\t' || str == '\n' || str == '\v' \
		|| str == '\f' || str == '\r' || str == ' ')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int long long		n;
	int long long		sign;
	int					i;

	n = 0;
	sign = 1;
	i = 0;
	while (is_space(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		n = n * 10 + (str[i++] - '0');
	return ((int)(n * sign));
}

void	ft_bzero(void *s, size_t n)
{
	memset(s, 0, n);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	tot;

	if (size && count > SIZE_MAX / size)
		return (0);
	tot = size * count;
	ptr = malloc(sizeof(char) * tot);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, tot);
	return (ptr);
}

void	*ft_free(void *ptr)
{
	if (ptr)
		free(ptr);
	return (NULL);
}