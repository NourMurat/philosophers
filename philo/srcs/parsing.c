/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numussan <numussan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 18:13:14 by numussan          #+#    #+#             */
/*   Updated: 2022/11/28 23:26:07 by numussan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

char	**ft_separate_string(int argc, char **s)
{
	int		i;
	char	*new_arr;
	char	*temp;
	char	**separate_string;

	i = 1;
	new_arr = "";
	temp = NULL;
	while (i < argc)
	{
		temp = new_arr;
		new_arr = ft_strjoin(new_arr, s[i]);
		if (i > 1)
			free(temp);
		i++;
	}
	separate_string = ft_split(new_arr, ' ');
	free(new_arr);
	return (separate_string);
}

int	ft_check_spaces(char **s)
{
	int	i;
	int	j;
	int	sp;

	i = 0;
	while (s[i])
	{
		j = 0;
		sp = 0;
		while (s[i][j])
		{
			if (s[i][j] == ' ' || (s[i][j] >= 9 && s[i][j] <= 13))
				sp++;
			j++;
		}
		if (sp == j)
		{
			printf("<<<<< ERROR! Empty argument OR only spaces! >>>>>\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_parsing(char **s)
{
	int	i;

	i = 0;
	while (s[i] != NULL)
		i++;
	if (i != 4 && i != 5)
	{
		printf("<<<<< ERROR! Input 4 or 5 arguments! >>>>>\n");
		ft_free_after_split(s);
		return (1);
	}
	if (ft_atoi(s[0]) <= 0 || ft_atoi(s[1]) <= 0 || ft_atoi(s[2]) <= 0 \
		|| ft_atoi(s[3]) <= 0 || (i == 5 && ft_atoi(s[4]) <= 0))
	{
		printf("<<<<< ERROR! Wrong arguments! >>>>>\n");
		ft_free_after_split(s);
		return (1);
	}
	return (0);
}
