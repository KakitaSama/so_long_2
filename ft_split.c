/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jazo <sel-jazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 23:28:07 by sel-jazo          #+#    #+#             */
/*   Updated: 2024/12/04 15:36:21 by sel-jazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	ft_cnt(char const *str, char c)
{
	int	cnt;
	int	i;
	int	k;

	cnt = 0;
	i = 0;
	k = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		if (c == str[i])
		{
			cnt += k;
			k = 0;
		}
		else
			k = 1;
		i++;
	}
	cnt += k;
	return (cnt);
}

static char	*ft_create(char const *str, int j, int k)
{
	int		i;
	char	*arr;

	i = 0;
	arr = (char *)malloc(k + 1);
	if (arr == NULL)
		return (arr);
	while (i < k)
	{
		arr[i] = str[j];
		i++;
		j++;
	}
	arr[i] = '\0';
	return (arr);
}

static char	*ft_first_word(char const *str, char c, int *i)
{
	int		k;
	int		j;
	char	*arr;
	int		l;

	k = 0;
	j = 0;
	l = 0;
	while (str[*i])
	{
		if (c != str[*i])
		{
			if (k == 0)
				j = *i;
			k++;
		}
		else if (k != 0)
			break ;
		(*i)++;
	}
	arr = ft_create(str, j, k);
	return (arr);
}

static void	ft_free_mem(char **ans, int k)
{
	k--;
	while (k >= 0)
	{
		free(ans[k]);
		k--;
	}
}

char	**ft_split(char const *str, char c)
{
	int		i;
	int		j;
	char	**ans;
	int		cnt;

	i = 0;
	cnt = 0;
	j = ft_cnt(str, c);
	ans = (char **)malloc (sizeof(char *) * (j + 1));
	if (ans == 0)
		return (ans);
	while (cnt < j)
	{
		ans[cnt] = ft_first_word(str, c, &i);
		if (ans[cnt] == 0)
		{
			ft_free_mem(ans, cnt);
			free(ans);
			return (0);
		}
		cnt++;
	}
	ans[j] = 0;
	return (ans);
}
