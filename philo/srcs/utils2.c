/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numussan <numussan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 03:11:26 by numussan          #+#    #+#             */
/*   Updated: 2022/11/23 22:35:56 by numussan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_free_after_split(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		s[i] = NULL;
		i++;
	}
	free(s);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*result;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	if (!s1 && !s2)
		return (NULL);
	result = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 2) * sizeof(char));
	if (!result)
		return (NULL);
	while (*s1)
		result[i++] = *s1++;
	result[i++] = ' ';
	while (*s2)
		result[i++] = *s2++;
	result[i] = '\0';
	return (result);
}

char	*ft_pull_the_word(const char *s, char c)
{
	char	*word;
	int		i;

	i = 0;
	while (*s && *s == c)
		s++;
	while (s[i] && s[i] != c)
		i++;
	word = (char *)malloc((i + 1) * sizeof(char));
	if (!word)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

int	ft_counting_words(const char *s, char c)
{
	int	num;

	num = 0;
	while (*s)
	{
		if (*s && *s == c)
			s++;
		else
		{
			num++;
			while (*s && *s != c)
				s++;
		}
	}
	return (num);
}

char	**ft_split(const char *s, char c)
{
	int		number_of_words;
	char	**result;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	number_of_words = ft_counting_words(s, c);
	result = (char **)malloc(sizeof(char *) * (number_of_words + 1));
	if (!result)
		return (NULL);
	while (number_of_words--)
	{
		while (*s && *s == c)
			s++;
		result[i] = ft_pull_the_word(s, c);
		while (*s && *s != c)
			s++;
		i++;
	}
	result[i] = NULL;
	return (result);
}
