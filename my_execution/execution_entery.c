/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_entery.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 03:56:06 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/05/20 19:53:16 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../minishell.h"


 static int  is_built_in(char **command)
{
    
    if(command)
    {
        if(!command[0])
            return(0);
        if((!ft_strcmp(command[0], "echo")) || 
            (!ft_strcmp(command[0], "cd")) || (!ft_strcmp(command[0], "pwd")) ||
                (!ft_strcmp(command[0], "export")) || (!ft_strcmp(command[0], "unset") 
                    || (!ft_strcmp(command[0], "env")) || (!ft_strcmp(command[0], "exit"))))
            return (1);
        else
            return (0);       
    }
    else
        return(0);
        
}
static void execute_the_builtin(t_com *command, char *PWD, char *oldprompt, t_environ **s_environ)
{
    if(!ft_strcmp(command->command[0], "echo"))
    {
        echo_execution(command);
    }
    else if(!ft_strcmp(command->command[0], "cd"))
        cd_execution(command, PWD);
    else if(!ft_strcmp(command->command[0], "pwd"))
        pwd_execution(command);
    else if(!ft_strcmp(command->command[0], "export"))
        export_parssing(command, oldprompt, s_environ);
    else if(!ft_strcmp(command->command[0], "env"))
        executing_env(s_environ);
    else if(!ft_strcmp(command->command[0], "unset"))
        unset_executing(command, s_environ);
    else if(!ft_strcmp(command->command[0], "exit"))
        printf("execute exit");   
}
void execution_entery(t_com *command, char *PWD, char *oldprompt)
{
    
    int built_in;
    static t_environ *environ;

    if(!environ)
        environ = making_the_environ_struct();
    built_in = 0;
    if(!command)
        return;
    while(command)
    {
        built_in = is_built_in(command->command) ;
        if(built_in == 1) {
            execute_the_builtin(command, PWD, oldprompt,&environ);
        }
        else
            printf("execute with childY");
        command = command->next;
    }
}
// int main()
// {
//     int built;
//     t_com *command;

//     built = is_built_in(command->command);
    
// }