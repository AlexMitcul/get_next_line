/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 09:27:24 by amitcul           #+#    #+#             */
/*   Updated: 2022/11/28 10:01:47 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

typedef struct s_fd_item
{
	int		fd;
	char	*amount;
	struct s_fd_item	*next;
}	t_fd_item;

void	add_front(t_fd_item **lst, int fd);
void	free_item(t_fd_item **lst, t_fd_item *item);
char	*get_next_line(int fd);
t_fd_item	*get_file_by_fd(t_fd_item *lst, int fd);
int		ft_strlen(char *str);
void	*ft_calloc(size_t elementCount, size_t elementSize);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char *s1, char *s2);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

#endif
