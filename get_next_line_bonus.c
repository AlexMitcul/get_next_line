/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 01:45:37 by alexmitcul        #+#    #+#             */
/*   Updated: 2022/11/07 05:49:31 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	return (-1);
}

static int	read_and_join(int fd, t_fd_item **curr_file)
{
	int		bytes_readen;
	char	bf[BUFFER_SIZE + 1];
	char	*tmp;
	int		i;

	i = 0;
	while (i < BUFFER_SIZE + 1)
	{
		bf[i] = 0;
		i++;
	}
	bytes_readen = read(fd, bf, BUFFER_SIZE);
	if (bytes_readen <= 0)
		return (bytes_readen);
	tmp = ft_strjoin((*curr_file)->amount, bf);
	free((*curr_file)->amount);
	(*curr_file)->amount = tmp;
	return (bytes_readen);
}

static void	extract_result(t_fd_item *curr_file, char **result)
{
	int	index;
	int	i;

	index = find_first_newline(curr_file->amount, '\n');
	if (index == -1)
		index = ft_strlen(curr_file->amount);
	*result = malloc(sizeof(char) * (index + 2));
	if (*result == NULL)
		return ;
	i = 0;
	while (i <= index)
	{
		(*result)[i] = curr_file->amount[i];
		i++;
	}
	(*result)[i] = '\0';
}

static void	remove_extracted_symbols(t_fd_item **item)
{
	int		index;
	int		i;
	int		j;
	int		amount_length;
	char	*new_amount;

	index = find_first_newline((*item)->amount, '\n');
	if (index == -1)
		index = ft_strlen((*item)->amount);
	amount_length = ft_strlen((*item)->amount);
	new_amount = malloc(sizeof(char) * (amount_length - index + 1));
	i = 0;
	j = index + 1;
	while (j < amount_length)
	{
		new_amount[i] = (*item)->amount[j];
		i++;
		j++;
	}
	new_amount[i] = '\0';
	free((*item)->amount);
	(*item)->amount = new_amount;
}

char	*get_next_line(int fd)
{
	static t_fd_item	*fd_list = NULL;
	t_fd_item			*curr_file;
	char				*result;

	if (read(fd, 0, 0) < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	curr_file = get_file_by_fd(fd_list, fd);
	if (curr_file == NULL)
		ft_lstadd_front(&fd_list, fd);
	curr_file = get_file_by_fd(fd_list, fd);
	while (find_first_newline(curr_file->amount, '\n') == -1
		&& read_and_join(fd, &curr_file) > 0)
		;
	if (ft_strlen(curr_file->amount) == 0)
	{
		free(curr_file);
		return (NULL);
	}
	extract_result(curr_file, &result);
	remove_extracted_symbols(&curr_file);
	if (curr_file->amount && curr_file->amount[0] == 0)
		free_item(&fd_list, curr_file);
	return (result);
}
