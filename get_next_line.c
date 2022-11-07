/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 02:15:19 by alexmitcul        #+#    #+#             */
/*   Updated: 2022/11/07 01:49:39 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	read_and_join(int fd, char **amount)
{
	int		bytes_readen;
	char	bf[BUFFER_SIZE + 1];
	char	*tmp;

	ft_bzero(bf, BUFFER_SIZE + 1);
	bytes_readen = read(fd, bf, BUFFER_SIZE);
	if (bytes_readen <= 0)
		return (bytes_readen);
	tmp = ft_strjoin(*amount, bf);
	free(*amount);
	*amount = tmp;
	return (bytes_readen);
}

static int	find_first_newline(char *str, char c)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (i);
}

static void	extract_result(char **amount, char **result)
{
	int		index;
	int		i;

	index = find_first_newline(*amount, '\n');
	*result = malloc(sizeof(char) * (index + 1 + 1));
	if (result == NULL)
		return ;
	i = 0;
	while (i <= index)
	{
		(*result)[i] = (*amount)[i];
		i++;
	}
	(*result)[i] = '\0';
}

static void	remove_extracted_symbols(char **amount)
{
	int		index;
	int		i;
	int		j;
	int		amount_length;
	char	*new_amount;

	index = find_first_newline(*amount, '\n');
	amount_length = ft_strlen(*amount);
	new_amount = malloc(sizeof(char) * (amount_length - index + 1));
	i = 0;
	j = index + 1;
	while (j < amount_length)
	{
		new_amount[i] = (*amount)[j];
		i++;
		j++;
	}
	new_amount[i] = '\0';
	free(*amount);
	*amount = new_amount;
}

char	*get_next_line(int fd)
{
	static char	*amount = NULL;
	char		*result;

	if (read(fd, 0, 0) < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (ft_strchr(amount, '\n') == NULL && read_and_join(fd, &amount) > 0)
		;
	if (ft_strlen(amount) == 0)
		return (NULL);
	extract_result(&amount, &result);
	remove_extracted_symbols(&amount);
	if (*amount == 0)
	{
		free(amount);
		amount = NULL;
	}
	return (result);
}
