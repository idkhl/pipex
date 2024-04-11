/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 09:59:18 by idakhlao          #+#    #+#             */
/*   Updated: 2024/03/18 11:00:24 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	c;
	char	*str;

	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = -1;
	c = 0;
	if (s1)
		while (s1[++i] != '\0')
			str[i] = s1[i];
	while (s2[c] != '\0')
		str[i++] = s2[c++];
	str[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	free(s1);
	return (str);
}

/*
int	main(void)
{
	char *s1[] = "Hello,";
	char *s2[] = " World";

	 char *res = ft_strjoin(s1, s2);
	printf("%s\n", res);

	if (res != NULL)
		free(res);
	return (0);
}
#include <stdlib.h>
#include <unistd.h>

size_t	ft_strlen( char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static void			ft_print_result(char *s)
{
	int		len;

	len = 0;
	while (s[len])
		len++;
	write(1, s, len);
}

static void			check_strjoin(char *s1, char *s2)
{
	char	*strjoin;

	if (!(strjoin = ft_strjoin(s1, s2)))
		ft_print_result("NULL");
	else
		ft_print_result(strjoin);
	if (strjoin == s1 || strjoin == s2)
		ft_print_result("\nA new string was not returned");
	else
		free(strjoin);
}

int					main(int argc,  char *argv[])
{
	char	s1[] = "lorem ipsum";
	char	s2[] = "dolor sit amet";
	int		arg;

	alarm(5);
	if (argc == 1)
		return (0);
	else if ((arg = atoi(argv[1])) == 1)
	{
		check_strjoin(s1, s2);
	}
	else if (arg == 2)
	{
		s1[0] = '\0';
		check_strjoin(s1, s2);
	}
	else if (arg == 3)
	{
		s2[0] = '\0';
		check_strjoin(s1, s2);
	}
	else if (arg == 4)
	{
		s1[0] = '\0';
		s2[0] = '\0';
		check_strjoin(s1, s2);
	}
	return (0);
}
*/