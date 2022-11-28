/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 20:13:23 by alexmitcul        #+#    #+#             */
/*   Updated: 2022/11/27 18:14:57 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_bzero(void *s, size_t n)
{
	while (n > 0)
	{
		*(char *)s = 0;
		s += 1;
		n -= 1;
	}
}

char	*ft_strchr(const char *s, int character)
{
	char	c;

	if (!s)
		return (NULL);
	c = character;
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

int	ft_strlen(char *str)
{
	int	size;

	size = 0;
	if (str == NULL)
		return (0);
	while (str[size])
		size++;
	return (size);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*res;
	int		length;
	size_t	i;

	length = ft_strlen(s1) + ft_strlen(s2);
	res = (char *)malloc(sizeof(char) * (length + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (s1 && *s1)
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
