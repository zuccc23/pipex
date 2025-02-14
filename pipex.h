/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahmane <dahmane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 00:54:46 by dahmane           #+#    #+#             */
/*   Updated: 2025/02/14 16:37:12 by dahmane          ###   ########.fr       */
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
# include <errno.h>
# include "printf/ft_printf.h"

typedef struct	s_var	t_var;
struct s_var
{
	char	*path_line;
	char	**commands;
};


// UTILS /////////////////////////////////////////////////////////////////////////
char	*ft_strnstr(const char *big, const char *little, size_t len);
void    free_strs(char **strs);

// SPLIT n stuff /////////////////////////////////////////////////////////////////////////
char	**ft_split(char const *s, char c);
char	**ft_split1(char const *s, char c);
void    ft_print(char **strs);
char	*ft_strjoin(char *s1, char *s2);

// FIND PATHS //////////////////////////////////////////////////////////////////////////
void    find_path_line(char **path_line, char **env);
int    join_paths(char **paths, char *command, char ***final_paths);

#endif