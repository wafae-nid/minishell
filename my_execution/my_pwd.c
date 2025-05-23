/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 06:04:08 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/05/21 21:16:56 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int is_valid_pwd(t_com *command)
{
    if (!ft_strcmp(command->command[1],"-p") || !ft_strcmp(command->command[1],"--p" ) || !ft_strcmp(command->command[1],"---p"))
        return(0);
    else
        return(1);
}

void  pwd_execution(t_com   *command)
{
    char *PWD;

    if (command->command[1] && !is_valid_pwd(command))
    {
        printf("error msg");
        return;
    }
    PWD = getcwd(NULL,0);
    if(!PWD )
        perror("problem finding current directory");
    else
        printf("%s\n", PWD);
    
}

 //int main()
// {
//     char *new_path;
//     char *new;
//     char *PWD;
//     char *OLDPWD;
//     char *prompt;
//     char *read_line;

//     //PWD=getcwd(NULL,0);
//     //PWD=getcwd(NULL,0);
//    // if(!PWD)
//        // printf("Current directory has been deleted.\n");

//    // else
//       //  printf("%s", PWD);
//       new = ft_strjoin("\\","\n");
//       printf("%s", new);
// }
