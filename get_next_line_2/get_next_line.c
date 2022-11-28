

#include "get_next_line.h"


char	*clear(char *amount, char *bf)
{
	char	*tmp;

	tmp = ft_strjoin(amount, bf);
	free(bf);
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

char	*get_line(char *amount)
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
		amount = malloc(sizeof(char));
	bf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	readen = BUFFER_SIZE;
	while (readen > 0)
	{
		readen = read(fd, bf, BUFFER_SIZE);
		if (readen == -1)
		{
			free(bf);
			return (NULL);
		}
		bf[readen] = '\0';
		amount = clear(amount, bf);
		if (strchr(bf, '\n'))
			break ;
	}
	free(bf);
	return (amount);
}

char	*get_next_line(int fd)
{
	static char	*amount;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	amount = read_and_join(fd, amount);
	if (amount == NULL)
		return (NULL);
	line = get_line(amount);
	amount = remove_extra(amount);
	return (line);
}

#include <fcntl.h>
#include <stdio.h>
int main(void)
{
	int fd;
	char	*line;

	fd = open("nl", O_RDONLY);

	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}

	return (0);
}
