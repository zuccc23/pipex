/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahmane <dahmane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 00:54:46 by dahmane           #+#    #+#             */
/*   Updated: 2025/02/20 18:59:59 by dahmane          ###   ########.fr       */
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

typedef struct s_var	t_pipeto;
struct s_var
{
	int		id;
	int		id2;
	int		ex_cd1;
	int		ex_cd2;
	char	*path_line;
	char	*ok_path;
	char	*ok_path_out;
	char	**commands_in;
	char	**commands_o;
	char	**paths;
	char	**f_path;
	char	**f_patho;
	char	*infile;
	char	*outfile;
	int		fd_in;
	int		fd_out;
};

// PIPEX /////////////////////////////////////////////
int		parent(t_pipeto **pipeto, int *fd);
int		child1(t_pipeto **pipeto, int *fd, char **env);
int		child2(t_pipeto **pipeto, int *fd, char **env);

// INIT ///////////////////////////////////////////////
int		init(t_pipeto **pipeto, char **argv, char **env, int *fd);
int		fork_and_pipe(t_pipeto **pipeto, int *fd);

// FREE ///////////////////////////////////////////////
int		return_error_input(t_pipeto **pipeto, int *fd, int argc);
void	return_error(t_pipeto **pipeto, int *fd);
void	free_strs(char **strs);
void	free_all(t_pipeto **pipeto, int *fd);
void	close_fd(t_pipeto **pipeto, int *fd);

// UTILS /////////////////////////////////////////////////////////
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strjoin(char *s1, char *s2);

// GET PATHS ///////////////////////////////////////////////////
void	find_path_line(char **path_line, char **env);
int		join_paths(char **paths, char *command, char ***f_path);
char	*get_okpath(char **paths);
int		get_paths(t_pipeto **pipeto, char **env);

// GET COMMANDS ///////////////////////////////////////////////
int		get_commands(t_pipeto **pipeto, char **argv);

// SPLIT n stuff ///////////////////////////////////////////////
char	**ft_split(char const *s, char c);
char	**ft_split1(char const *s, char c);
void	ft_print(char **strs);

#endif