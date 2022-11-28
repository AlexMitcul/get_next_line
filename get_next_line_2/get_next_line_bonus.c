/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 09:27:02 by amitcul           #+#    #+#             */
/*   Updated: 2022/11/28 10:16:16 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*clear(char *amount, char *bf)
{
	char	*tmp;

	tmp = ft_strjoin(amount, bf);
	free(amount);
	return (tmp);
}

char	*remove_extra(char *amount)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (amount[i] && amount[i] != '\n')
		i++;
	if (!amount[i])
	{
		free(amount);
		return (NULL);
	}
	line = ft_calloc((ft_strlen(amount) - i + 1), sizeof(char));
	i++;
	j = 0;
	while (amount[i])
		line[j++] = amount[i++];
	free(amount);
	return (line);
}


static char	*get_line(char *amount)
{
	char	*line;
	int		i;

	i = 0;
	if (!amount[i])
		return (NULL);
	while (amount[i] && amount[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	i = 0;
	while (amount[i] && amount[i] != '\n')
	{
		line[i] = amount[i];
		i++;
	}
	if (amount[i] && amount[i] == '\n')
		line[i++] = '\n';
	return (line);
}

char	*read_and_join(int fd, char *amount)
{
	char	*bf;
	int		readen;

	if (!amount)
		amount = ft_calloc(1, sizeof(char));
	bf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	readen = BUFFER_SIZE;
	while (readen > 0)
	{
		readen = read(fd, bf, BUFFER_SIZE);
		if (readen == -1)
		{
			free(bf);
			free(amount);
			return (NULL);
		}
		bf[readen] = '\0';
		amount = clear(amount, bf);
		if (ft_strchr(bf, '\n'))
			break ;
	}
	free(bf);
	return (amount);
}

char	*get_next_line(int fd)
{
	static t_fd_item	*fd_list = NULL;
	t_fd_item			*curr_file;
	char	*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	curr_file = get_file_by_fd(fd_list, fd);
	if (curr_file == NULL)
		add_front(&fd_list, fd);
	curr_file = get_file_by_fd(fd_list, fd);
	curr_file->amount = read_and_join(curr_file->fd, curr_file->amount);
	if (curr_file->amount == NULL)
	{
		free_item(&fd_list, curr_file);
		return (NULL);
	}
	line = get_line(curr_file->amount);
	curr_file->amount = remove_extra(curr_file->amount);
	if (curr_file->amount == NULL)
		free_item(&fd_list, curr_file);
	return (line);
}
