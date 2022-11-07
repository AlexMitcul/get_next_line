/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 01:45:37 by alexmitcul        #+#    #+#             */
/*   Updated: 2022/11/07 05:36:53 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	ft_lstadd_front(t_fd_item **lst, int fd)
{
	t_fd_item	*new_item;

	new_item = malloc(sizeof(t_fd_item));
	if (!new_item)
		return ;
	new_item->amount = NULL;
	new_item->fd = fd;
	new_item->next = NULL;
	if (*lst == NULL)
		*lst = new_item;
	else
	{
		new_item->next = *lst;
		*lst = new_item;
	}
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

t_fd_item	*get_file_by_fd(t_fd_item *lst, int fd)
{
	while (lst)
	{
		if (lst->fd == fd)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

static int	read_and_join(int fd, t_fd_item **curr_file)
{
	int		bytes_readen;
	char	bf[BUFFER_SIZE + 1];
	char	*tmp;

	ft_bzero(bf, BUFFER_SIZE + 1);
	bytes_readen = read(fd, bf, BUFFER_SIZE);
	if (bytes_readen <= 0)
		return (bytes_readen);
	tmp = ft_strjoin((*curr_file)->amount, bf);
	free((*curr_file)->amount);
	(*curr_file)->amount = tmp;
	return (bytes_readen);
}

static void extract_result(t_fd_item *curr_file, char **result)
{
	int	index;
	int	i;

	index = find_first_newline(curr_file->amount, '\n');
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

void	remove_extracted_symbols(t_fd_item **item)
{
	int		index;
	int		i;
	int		j;
	int		amount_length;
	char	*new_amount;

	index = find_first_newline((*item)->amount, '\n');
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

void	free_item(t_fd_item **lst, t_fd_item *item)
{
	t_fd_item	*tmp;

	if (lst == NULL || *lst == NULL || item == NULL)
		return ;
	tmp = *lst;
	if (tmp->fd == item->fd)
	{
		*lst = (*lst)->next;
		tmp->next = NULL;
		free(tmp->amount);
		free(tmp);
	}
	else
	{
		while (tmp->next->fd != item->fd)
			tmp = tmp->next;
		t_fd_item	*del;
		del = tmp->next;
		tmp->next = tmp->next->next;
		del->next = NULL;
		free(del->amount);
		free(del);
	}
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
	while (ft_strchr(curr_file->amount, '\n') == NULL && read_and_join(fd, &curr_file) > 0)
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
