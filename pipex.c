/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahmane <dahmane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 00:54:28 by dahmane           #+#    #+#             */
/*   Updated: 2025/02/13 18:15:50 by dahmane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    find_path_line(char **path_line, char *env)
{
      while (env) {
        if (ft_strnstr(env, "PATH=") != 0)
        {
            *path_line = ft_strnstr(env, "PATH=");
            return ;
        }
        env++;
    }
}

void    join_paths(char ***paths, char *command)
{
    int i;

    i = 0;
    while ((*paths)[i])
    {
        (*paths)[i] = ft_strjoin((*paths)[i], command);
        i++;
    }
}

int main (int argc, char **argv, char **env)
{
    int id = 0;
    int id2 = 0;
    int fd[2];
    char    buffer[100];
    int     fd2[2];
    char    *path_line;
    char    command[] = "ls";
    char    **paths;
    int i = 0;
    
    // USE EXECVE //////////////////////////////////////////////////////////////
    
    find_path_line(&path_line, *env);
    ft_printf("%s\n", path_line);

    paths = ft_split(path_line + 5, ':');
    if (!paths)
        return (0);
    join_paths(&paths, command);
    // ft_print(paths);
    while (paths[i])
    {
        ft_printf("%d\n", access(paths[i], F_OK));
        i++;
    }
    
    
    // char    pathname[] = "/bin/ls";
    // char    *args[] = {"/bin/ls", "-a", NULL};
    // char    **envp = NULL;
    // execve(pathname, args, envp);

    // DOUBLE PIPE ////////////////////////////////////////////////////////////
    // pipe(fd);
    // pipe(fd2);
    // id = fork();
    // if (id == 0)
    // {
    //     int nb = 5;
    //     close(fd[0]);
    //     write(fd[1], &nb, sizeof(int));
    //     close(fd[1]);

    //     close(fd2[1]);
    //     read(fd2[0], &nb, sizeof(int));
    //     close(fd2[0]);
    //     printf("%d\n", nb);
    // }
    // if (id != 0)
    // {
    //     int nb2;
    //     close(fd[1]);
    //     read(fd[0], &nb2, sizeof(int));
    //     close(fd[0]);
    //     // printf("%d\n", nb2);
    //     nb2 *= 2;

    //     close(fd2[0]);
    //     write(fd2[1], &nb2, sizeof(int));
    //     close(fd2[1]);
    // }
    
    // TEST PROCESS ID //////////////////////////////////////////////////////
    // id = fork();
    // id2 = fork();
    // if (id == 0)
    // {
    //     if (id2 == 0)
    //     {
    //         printf("child2\n");
    //     }
    //     else
    //     {
    //         // wait(NULL);
    //         printf("parent\n");
    //     }
    // }
    // else 
    // {
    //     if (id2 == 0)
    //     {
    //         printf("child1\n");
    //     }
    //     else
    //     {
    //         printf("main\n");
    //     }
    // }
}
