/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 01:45:39 by alexmitcul        #+#    #+#             */
/*   Updated: 2022/11/07 05:50:00 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

void	free_item(t_fd_item **lst, t_fd_item *item)
{
	t_fd_item	*tmp;
	t_fd_item	*del;

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
		del = tmp->next;
		tmp->next = tmp->next->next;
		del->next = NULL;
		free(del->amount);
		free(del);
	}
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
