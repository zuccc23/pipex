/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahmane <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:49:47 by dahmane           #+#    #+#             */
/*   Updated: 2024/11/18 12:50:49 by dahmane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strnstr(const char *big, const char *little)
{
	size_t			i;
	size_t			j;

	j = 0;
	i = 0;
	if (little[0] == '\0')
		return ((char *)big);
	while (big[i])
	{
		while (big[i + j] == little[j])
		{
			if (little[j + 1] == '\0')
				return ((char *) &big[i]);
			j++;
		}
		i++;
		j = 0;
	}
	return (0);
}
/*
int main(void)
{
    char *str = "bakamario";
    char *strr = "";
    size_t len = 5;
    printf("--%s\n", ft_strnstr("lorem ipsum dolor sit amet", "", 10));

//    printf("%s\n", ft_strnstr(str, strr, len));
//    printf("%s\n", strnstr(str, strr, len));
    return (0);
}*/
