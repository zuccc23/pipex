/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahmane <dahmane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 00:54:46 by dahmane           #+#    #+#             */
/*   Updated: 2025/02/13 18:10:42 by dahmane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h> 
# include <string.h>
# include "printf/ft_printf.h"

// UTILS /////////////////////////////////////////////////////////////////////////
char	*ft_strnstr(const char *big, const char *little);

// SPLIT n stuff /////////////////////////////////////////////////////////////////////////
char	**ft_split(char const *s, char c);
void    ft_print(char **strs);
char	*ft_strjoin(char *s1, char *s2);


#endif