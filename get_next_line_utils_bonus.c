/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 10:25:42 by amitcul           #+#    #+#             */
/*   Updated: 2022/11/28 10:27:11 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_strlen(char *str)
{
	int	size;

	if (!str)
		return (0);
	size = 0;
	while (*str)
	{
		str++;
		size++;
	}
	return (size);
}

char	*ft_strchr(const char *s, int c)
{
	if (s == NULL)
		return (NULL);
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	if (*s == '\0' && c == '\0')
		return ((char *)s);
	return (NULL);
}

void	*ft_calloc(size_t elementCount, size_t elementSize)
{
	char	*res;
	char	*str;
	size_t	i;

	res = malloc(elementSize * elementCount);
	if (!res)
		return (NULL);
	str = (char *)res;
	i = 0;
	while (i < elementCount * elementSize)
	{
		str[i] = '\0';
		i++;
	}
	return (res);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*res;
	int		length;
	int		i;

	length = ft_strlen(s1) + ft_strlen(s2);
	res = (char *)malloc(sizeof(char) * (length + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (s1 != NULL && *s1 != '\0')
	{
		res[i++] = *s1;
		s1 += 1;
	}
	while (s2 && *s2)
	{
		res[i++] = *s2;
		s2 += 1;
	}
	res[i] = '\0';
	return (res);
}
