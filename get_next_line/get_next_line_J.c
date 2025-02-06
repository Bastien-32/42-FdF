/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_J.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:02:42 by badal-la          #+#    #+#             */
/*   Updated: 2025/02/06 16:47:36 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_J.h"

char	*get_all_file(int fd, char *str)
{
	char	*buf;
	int		oct;

	buf = NULL;
	buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (buf == NULL)
	{
		if (str)
			free(str);
		return (NULL);
	}
	oct = 1;
	while (oct != 0 && in_str(str, '\n') == -1)
	{
		oct = read(fd, buf, BUFFER_SIZE);
		if (oct < 0)
		{
			if (str)
				free(str);
			return (free(buf), NULL);
		}
		buf[oct] = '\0';
		str = ft_strjoin2(str, buf);
	}
	return (free(buf), str);
}

char	*get_lines(char *str, int i)
{
	char	*lign;

	if (i == -1)
		lign = ft_substr_gnl(str, 0, ft_strlen(str));
	else
		lign = ft_substr_gnl(str, 0, i + 1);
	if (!lign[0])
		return (free(lign), NULL);
	else
		return (lign);
}

char	*get_end_file(char *str, int i)
{
	char	*str_new;

	if (!str[0] || i == -1)
		return (free(str), NULL);
	str_new = ft_substr_gnl(str, i + 1, ft_strlen(str));
	free(str);
	return (str_new);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*lign;
	int			i;

	str = get_all_file(fd, str);
	if (str == NULL)
		return (NULL);
	i = in_str(str, '\n');
	lign = get_lines(str, i);
	str = get_end_file(str, i);
	return (lign);
}