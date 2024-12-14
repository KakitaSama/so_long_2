/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jazo <sel-jazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 09:41:51 by sel-jazo          #+#    #+#             */
/*   Updated: 2024/12/04 13:53:41 by sel-jazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_search(char *buf)
{
	int	i;

	i = 0;
	while (buf[i])
	{
		if (buf[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int	ft_prework(char **buf, char **str, char **ans, char *tmp)
{
	char	*tmp0;
	int		p;

	if (tmp == NULL && ft_fr(&(*str)) && ft_fr(&(*buf)))
		return (1);
	p = ft_search((*str));
	if (p != -1)
	{
		tmp0 = ft_substr((*str), 0, p + 1);
		if (tmp0 == NULL && ft_fr(&tmp) && ft_fr(&(*str)) && ft_fr(&(*buf)))
			return (1);
		(*ans) = ft_strjoin(tmp, tmp0);
		ft_fr(&tmp);
		tmp = (*str);
		if (ft_fr(&tmp0) && (*ans) == NULL && ft_fr(&(*str)) && ft_fr(&(*buf)))
			return (1);
		(*str) = ft_substr((*str), p + 1, BUFFER_SIZE);
		if (ft_fr(&tmp) && (*str) == NULL && ft_fr(&(*ans)) && ft_fr(&(*buf)))
			return (1);
		if (ft_fr(&(*buf)) && (*str)[0] == '\0')
			ft_fr(&(*str));
		return (1);
	}
	(*ans) = ft_strjoin(tmp, (*str));
	return (ft_fr(&tmp) && (*ans) == NULL && ft_fr(&(*buf)) && ft_fr(&(*str)));
}

int	ft_res(char **buf, char **str, char **ans, int p)
{
	char	*tmp;
	char	*tmp0;

	if ((*ans) == NULL)
	{
		(*ans) = ft_strdup("");
		if ((*ans) == NULL)
			return (0);
	}
	tmp = (*ans);
	tmp0 = ft_substr((*buf), 0, p + 1);
	if (tmp0 == NULL && ft_fr(&(*ans)) && ft_fr(&(*buf)))
		return (1);
	(*ans) = ft_strjoin((*ans), tmp0);
	if (ft_fr(&tmp) && ft_fr(&tmp0) && (*ans) == NULL)
		return (0);
	*str = ft_substr((*buf), p + 1, BUFFER_SIZE);
	if (*str == NULL && ft_fr(&(*ans)) && ft_fr(&(*buf)))
		return (1);
	return (!(ft_fr(&(*buf)) && (*str)[0] == '\0'));
}

int	ft_looping(char **buf, char **str, char **ans, int fd)
{
	int		i;
	char	*tmp;
	int		p;

	while (1)
	{
		i = read(fd, (*buf), BUFFER_SIZE);
		if (i < 0 && ft_fr(&(*ans)))
			return (0);
		(*buf)[i] = '\0';
		p = ft_search((*buf));
		if (p == -1 && i != 0)
		{
			if ((*ans) == NULL)
				(*ans) = ft_strdup("");
			tmp = (*ans);
			(*ans) = ft_strjoin((*ans), (*buf));
			if (ft_fr(&tmp) && !(*ans))
				return (0);
		}
		else if (i != 0)
			return (ft_res(buf, str, ans, p));
		if (i < BUFFER_SIZE)
			return (0);
	}
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*ans;
	char		*buf;

	buf = (char *)malloc((size_t)BUFFER_SIZE + 1);
	ans = NULL;
	if (buf == NULL && ft_fr(&str))
		return (ans);
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, buf, 0) < 0)
	{
		ft_fr(&str);
		ft_fr(&buf);
		return (ans);
	}
	if (str != NULL && ft_prework(&buf, &str, &ans, ft_strdup("")))
		return (ans);
	ft_fr(&str);
	if (ft_looping(&buf, &str, &ans, fd))
		return (ans);
	ft_fr(&str);
	ft_fr(&buf);
	return (ans);
}
