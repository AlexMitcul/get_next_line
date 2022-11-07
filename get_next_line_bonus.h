/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 01:45:35 by alexmitcul        #+#    #+#             */
/*   Updated: 2022/11/07 04:39:20 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

#include <string.h>
#include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct	s_fd_item
{
	int					fd;
	char				*amount;
	struct s_fd_item	*next;
}				t_fd_item;

char	*get_next_line(int fd);

char	*ft_strjoin(char *s1, char *s2);
int		ft_strlen(char *str);
char	*ft_strchr(char *s, int c);
void	ft_bzero(void *s, size_t n);


#endif
