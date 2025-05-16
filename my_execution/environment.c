/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 11:21:33 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/05/14 11:55:14 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


static void	ft_lstadd_back_environ(t_environ **lst, t_environ *new)
{
	t_environ	*temp;

	if (new == NULL)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while ((temp)->next != NULL)
	{
		(temp) = (temp)->next;
	}
	(temp)->next = new;
}


t_environ *making_the_environ_struct(void)
{
    extern char **environ;
    t_environ *s_environ;
    t_environ *new;
    
    s_environ = NULL;
    
    int count ;
    
    int i;
    count = 0;
    
    if(environ)
    {
        i = 0;
        while(environ[i])
        {
            new = ft_lstnew_environ(environ[i]);
            ft_lstadd_back_environ(&s_environ, new);
            i++;
        }
        return(s_environ);
    }
    else 
        return(NULL);
}
void executing_env(void)
{
    t_environ *s_environ;
    
    s_environ = making_the_environ_struct();
    if (s_environ == NULL)
        return;
    while(s_environ)
    {
        printf("%s", s_environ->var);
        printf("=");
        printf("%s", s_environ->value);
        printf("\n");
        s_environ= s_environ->next;
    }
    
}
