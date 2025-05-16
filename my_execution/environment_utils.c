/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 12:08:56 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/05/14 11:54:06 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int count_lengh_value_str(char *str)
{
    int i;
    
    i = 0;
    if(str[0] == '=')
    {
        i++; 
    }
    while(str[i])
    {
        i++;
    }
    return(i - 1);
    
}

int count_lengh_var_str(char *str)
{
    int i ;
    
    i = 0;
    while(str[i] != '=')
    {
        i++;
    }
    return (i);  
}

static void fill_in_(char *str,char ***splited_environ_char)
{
    int i;
    int start;
    
    i = 0;
    while(str[i] != '=')
    {
        (*splited_environ_char)[0][i] = str[i];
        i++;
    }
    (*splited_environ_char)[0][i] = '\0';
    i++;
    start = i;
    i = 0;
    while(str[start])
    {
        (*splited_environ_char)[1][i]  = str[start];
        i++;
        start++;
    }
    (*splited_environ_char)[1][i]='\0';
    
}

char  **split_environ(char *str)
{
    char **splited_environ_char;
    int  lengh_of_var_str;
    int lengh_of_var_value;

    if(str == NULL)
        return(NULL);
    lengh_of_var_str = count_lengh_var_str(str);
    lengh_of_var_value = count_lengh_value_str((str + count_lengh_var_str(str)));
    splited_environ_char = (char **)malloc(3*sizeof(char *));
    if(!splited_environ_char)
        return(NULL);

    splited_environ_char[0] =(char *)malloc((size_t)(count_lengh_var_str + 1));
    splited_environ_char[1]= (char *)malloc((size_t)(lengh_of_var_value + 1));
    splited_environ_char[2] = NULL ;
    if(!splited_environ_char[0] || !splited_environ_char[1])
        return(NULL);
    fill_in_(str,&splited_environ_char);
    return(splited_environ_char);
}
t_environ  *ft_lstnew_environ( char *environ)
{
	t_environ	*newnode;
    char       **splited_environ;

	newnode = (t_environ *)malloc(sizeof(t_environ));
	if (!newnode)
		return (NULL);
    splited_environ = split_environ(environ);
    if(!splited_environ)
        return(NULL);
	newnode->var =splited_environ[0];
    newnode->value= splited_environ[1];
	newnode->next = NULL;
	return (newnode);
}
