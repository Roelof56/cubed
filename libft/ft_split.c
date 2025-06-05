/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhol <rhol@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/07 13:35:17 by rhol          #+#    #+#                 */
/*   Updated: 2025/06/02 16:58:31 by rhol          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_clean(char **arr, int index)
{
	while (index >= 0)
	{
		index--;
		free(arr[index]);
	}
	free(arr);
}

static int	ft_wordcount(const char *s1, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s1[i] != '\0')
	{
		if (i == 0 && s1[i] != c)
			count++;
		else if (s1[i] == c && s1[i + 1] != c && s1[i + 1] != '\0')
			count++;
		i++;
	}
	return (count);
}

static void	ft_fill(char **arr, const char *s1, char c)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (s1[i + j])
	{
		while (s1[i + j] != c && s1[i + j] != '\0')
			j++;
		if (j > 1 || (j == 1 && s1[i + j - 1] != c))
		{
			arr[k] = ft_substr(s1, i, j);
			if (arr[k] == NULL)
			{
				ft_clean(arr, k);
				return ;
			}
			i += j - 1;
			k++;
		}
		i++;
		j = 0;
	}
}

char	**ft_split(const char *s1, char c)
{
	int		rows;
	char	**result;

	if (!s1)
		return (NULL);
	rows = ft_wordcount(s1, c);
	result = malloc(sizeof(char *) * (rows + 1));
	if (result == NULL)
		return (NULL);
	ft_fill(result, s1, c);
	result[rows] = NULL;
	return (result);
}
