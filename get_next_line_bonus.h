/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 01:45:35 by alexmitcul        #+#    #+#             */
/*   Updated: 2022/11/07 05:50:29 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_fd_item
{
	int					fd;
	char				*amount;
	struct s_fd_item	*next;
}				t_fd_item;

char		*get_next_line(int fd);

char		*ft_strjoin(char *s1, char *s2);
int			ft_strlen(char *str);
void		ft_lstadd_front(t_fd_item **lst, int fd);
void		free_item(t_fd_item **lst, t_fd_item *item);
t_fd_item	*get_file_by_fd(t_fd_item *lst, int fd);

#endif
