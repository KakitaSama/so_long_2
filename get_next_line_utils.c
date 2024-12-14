/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jazo <sel-jazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 09:42:25 by sel-jazo          #+#    #+#             */
/*   Updated: 2024/12/04 13:53:36 by sel-jazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_fr(char **s)
{
	free(*s);
	*s = NULL;
	return (1);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(char *s1)
{
	char	*ans;
	int		i;

	ans = 0;
	i = 0;
	if (s1 == NULL)
		return (NULL);
	while (s1[i])
		i++;
	ans = (char *)malloc(i + 1);
	if (ans == 0)
		return (ans);
	i = 0;
	while (s1[i])
	{
		ans[i] = s1[i];
		i++;
	}
	ans[i] = '\0';
	return (ans);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*ans;
	int		k;

	k = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	ans = (char *)malloc(i + j + 1);
	if (ans == 0)
		return (ans);
	while (k < i)
	{
		ans[k] = s1[k];
		k++;
	}
	while (k < i + j)
	{
		ans[k] = s2[k - i];
		k++;
	}
	ans[i + j] = '\0';
	return (ans);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char			*ans;
	size_t			i;
	unsigned int	j;

	if (s == NULL)
		return (NULL);
	j = ft_strlen(s);
	if (j <= start)
		len = 0;
	else if (len + start >= j)
		len = j - start;
	i = 0;
	ans = (char *)malloc(len + 1);
	if (ans == 0)
		return (ans);
	while (i < len && s[start + i])
	{
		ans[i] = s[start + i];
		i++;
	}
	ans[i] = '\0';
	return (ans);
}
