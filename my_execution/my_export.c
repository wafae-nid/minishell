/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 21:53:41 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/05/18 15:21:39 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// static	void	loop_copying_s2(const char *s2, char **ptr, int count)
// {
// 	int	i;

// 	i = 0;
// 	while (s2[i])
// 	{
// 		(*ptr)[count] = s2[i];
// 		i++;
// 		count++;
// 	}
// 	(*ptr)[count] = '\0';
// }

// static char	*ft_strjoin(const char *s1, const char *s2)
// {
// 	char	*ptr;
// 	size_t	i;
// 	size_t	count;

// 	if (s1 == NULL && s2 == NULL)
// 		return (NULL);
// 	if (!s1)
// 		return (ft_strdup(s2));
// 	if (!s2)
// 		return (ft_strdup(s1));
// 	ptr = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
// 	if (ptr == NULL)
// 		return (NULL);
// 	i = 0;
// 	while (s1[i])
// 	{
// 		ptr[i] = s1[i];
// 		i++;
// 	}
// 	count = i;
// 	loop_copying_s2(s2, &ptr, count);
// 	return (ptr);
// }

static int ft_is_a_numb(char c)
{
    if(c >= '0' && c <= '9')
        return(1);
    else
        return(0);
}
static int is_while_space(char c)
{
    if((c > 8 && c <= 13) || c == ' ')
        return(1);
    return(0);
}


static int valid_position_export(char *str)
{
    int i;

    i = 0;
    
    if(!str)
        return(-1);
    while(str[i])
    {
        if(((str[i] == '=') && ((i == 0) || is_while_space(str[i-1])) )|| ((str[i] =='+') && ((i ==0) || is_while_space(str[i-1]))))
            return(0);
        i++; 
    }
    return(1);
}


// static int allowed_special_char(char c)
// {
//     if(c == '$' || c == '+' || c == '_' || c == '=')
    
// }

// static int valid_name_char(char *str)
// {
//     int i;

//     i = 0;
//     if(!str)
    
//         return(-1);
//     while(str[i])
//     {
// 		if(!(ft_isalpha(str[i]) == 1 || str[i] == '_' || str[i] == '=' || ft_is_a_numb(str[i]))) 
//             return(0);
//         i++;
//     }
//         return(0);
// }
static int var_name_end(char *str) // to know the end of my variable name;
{
    int i;
    
    int count;

    i = 0;
    if(!str)
        return(-1);
    while(str[i])
    {
        if(str[i]=='+' && str[i+1] == '=' && i!=1)
        {
            i--;
            return(i);
        }
        else if(str[i] == '=' && i!= 1)
        {
            i--;
            return(i);
        }
        i++;
    }
    return(0);
}
static int valid_var_name(char *str, int count)
{
    int i;
    i = 0;
    
    if(!str)
        return(-1);
    while(i < count)
    {
        if(!(ft_isalpha(str[i]) == 1 || str[i] == '_' || str[i] == '=' || ft_is_a_numb(str[i]))) 
            return(0);
        if((ft_is_a_numb(str[i])) && i == 0)
            return(0);
        i++;
    }
    return(1);
    
}
static void start_of_arguments(t_com *command,char **oldpromt)
{
    int i;
    
    i = 0;

     while((*oldpromt) && is_while_space((*oldpromt)[0]))
    {
        (*oldpromt)++;
    }
    while((*oldpromt)[0] && (command->command[0] && (command->command)[0][0] == (*oldpromt)[0]))
    {
        (command->command[0])++;
        (*oldpromt)++;
    }
    while((*oldpromt) && is_while_space((*oldpromt)[0]))
    {
        (*oldpromt)++;
    }
}
static int count_lengh_value_str_export(char *str)
{
    int i;

    int count;
    
    i = 0;
    count = 0;
    if(!str)
        return(-1);
    if(str[i] && (str[i] == '=' || str[i] == '+'))
    {
        if(str[i] && str[i]=='=')
            i++;
        i++; 
    }
    while(str[i])
    {
        i++;
        count++;
    }
    return(count);
   
    
}

static int count_lengh_var_str_export(char *str)
{
    int i ;
    
    i = 0;
    while(str[i] &&(str[i] != '=' && str[i]!= '+'))
    {
        i++;
    }
    return (i);  
}
 static void fill_in_environ(char *str,char ***splited_export_char)
{
    int i;
    int j;
    
    i = 0;
    while(str[i] && str[i] != '=' && str[i] != '+')
    {
        
        (*splited_export_char)[0][i] = str[i];
        i++;
    }
    (*splited_export_char)[0][i] = '\0';
    j = 0;
    if(str[i] == '=' || str[i] == '+')
    {
        if(str[i] == '+')
        {
            (*splited_export_char)[1][j]='+';
            i++;
            j++;
        }
        (*splited_export_char)[1][j]='=';
        i++;
        j++;
    }
    if((*splited_export_char)[1])
        (*splited_export_char)[1][j]='\0';
    j = 0;
    while(str[i])
    {
        (*splited_export_char)[2][j]=str[i];
        j++;
        i++;
    }
    if((*splited_export_char)[2])
        (*splited_export_char)[2][j] = '\0';
}


static char  **split_environ(char *str)
{
    char **splited_export_char;
    int  lengh_of_var_str;
    int lengh_of_var_value;
    
    if(!str)
        return(NULL);

    lengh_of_var_str = count_lengh_var_str_export(str);
    lengh_of_var_value = count_lengh_value_str_export((str + lengh_of_var_str));
    splited_export_char = (char **)malloc(4*sizeof(char *));
    if(!splited_export_char)
        return(NULL);
    splited_export_char[0] =(char *)malloc((size_t)(lengh_of_var_str + 1));
    if(str[lengh_of_var_str] == '=')
        splited_export_char[1] = (char *)malloc((size_t)(2));
    else if(str[lengh_of_var_str] == '+')
        splited_export_char[1] = (char *)malloc((size_t)(3));
    else
    {
        splited_export_char[1] = NULL;
        splited_export_char[2] = NULL;
        fill_in_environ(str,&splited_export_char);
        return(splited_export_char);
    }
    splited_export_char[2]= (char *)malloc((size_t)(lengh_of_var_value + 10));
    splited_export_char[3] = NULL ;
    if(!splited_export_char[0] || !splited_export_char[1] || !splited_export_char[2])
        return(NULL);
    fill_in_environ(str,&splited_export_char);
     return(splited_export_char);
}
t_environ  *ft_lstnew_environ(char *str)
{
	t_environ	*newnode;
    char       **splited_export;

	newnode = (t_environ *)malloc(sizeof(t_environ));
	if (!newnode)
		return (NULL);
    // if(!strcmp(str, ""))
    // {
    //     newnode->var =NULL;
    //     newnode->operator= NULL;
    //     newnode->value= NULL;
    //     newnode->next = NULL;
    // }
    // else
    // {
    splited_export = split_environ(str);
    if(!splited_export)
        return(NULL);
	newnode->var =splited_export[0];
    newnode->operator= splited_export[1];
    newnode->value= splited_export[2];
	newnode->next = NULL;
    return(newnode);
}
void	ft_lstadd_back_environ(t_environ **lst, t_environ *new)
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

static int is_the_var_in_environ(char *variable, t_environ *environ)
{
    t_environ *current = environ;
   while(current)
   {
       if(!strcmp(current->var ,variable))
           return(1);
       current = current->next;
   }
   return(0);
}

static void replace_node(t_environ **new, t_environ **environ)
{
    t_environ *tmp;
    t_environ *current;
    
    char *new_value;
    
    tmp = (*environ);
    while(tmp->next)
    {
        if(!strcmp((tmp->next)->var, (*new)->var))
        {
            current = tmp;
            if((tmp->next)->next)
            tmp = (tmp->next)->next;
            if(!strcmp((*new)->operator, "+="))
            {   
                new_value = ft_strjoin((current->next)->value, (*new)->value, GLOBAL);
                if(!new_value)
                    return;
                (*new)->value = new_value;
            }
            (*new)->next = tmp;
            current->next = *new;
        }
        tmp=tmp->next;     
    }
}

static void handling_new_changes(t_environ **new, t_environ **environ)
{
    char *new_value;
    char *new_operator;
    

    if(!((*new)->value))
        return;
    else if(!ft_strcmp((*new)->operator, "+=") && !strcmp((*new)->value,""))
        return;
    replace_node(new, environ);     
}

static t_environ *make_export_struct(char **splited_arg)
{
    static t_environ *environ;
    t_environ *new;
    int count ;
    int i;
    
    
    environ = making_the_environ_struct();
   (1&& (count = 0), (i = 0 ));
    if(splited_arg)
    {
        while(splited_arg[i])
        {
            new = ft_lstnew_environ(splited_arg[i]);
            if(is_the_var_in_environ(new->var, environ))
            {
                handling_new_changes(&new, &environ);
            }
            else
            {
                ft_lstadd_back_environ(&environ, new);
            }
            i++;
        }
        // while(environ)
        // {
        //     printf("%s\n", environ->var);
        //     environ= environ->next;
        // }  
        return(environ);
    }
    else 
        return(NULL);
}
static t_environ *input_struct_handling(char *oldpromt)
{
    char **splited_arg;
    int var_name_end_;
    int i;
    
    if(!ft_strcmp(oldpromt, ""))
        return(NULL);
    else
    {
        splited_arg = cstm_split(oldpromt, " ");
        if(!splited_arg)
            return(NULL);
        i = 0;
        while(splited_arg[i])
        {
            var_name_end_=(var_name_end(splited_arg[i]));
            if(!valid_var_name(splited_arg[i], var_name_end_))
            {
                printf("syntax error!");
                    return(NULL);
            }
            i++;
        }
            return(make_export_struct(splited_arg));
    }
}
// static change_the_var_value(t_environ *s_export, t_environ **environ)
// {
//     t_environ *tmp;
//     t_environ *new;

//     tmp=(*environ);

//     while(tmp)
//     {
//         if(!strcmp(s_export->var, tmp->var))
//         {
//             new = ft_lstnew_environ();
//         }
            
//     }
// }

// static void new_environ(t_environ *s_export, t_environ **environ)
// {
    
//     if(!s_export || !environ)
//         return;
//     while(s_export)
//     {
//         if(is_the_var_in_environ(s_export->var, *environ))
//             if(s_export->value)
//                 change_the_var_value(s_export, &environ);
//         s_export=s_export->next;    
//     }
    
// } 
    
int export_parssing(t_com *command, char *oldpromt)
{
    int i;
    t_environ *environ;
    
        
    if(command->command)
    {
        start_of_arguments(command,&oldpromt);
        if(valid_position_export(oldpromt))
        {
            environ = input_struct_handling(oldpromt);
            if(environ == NULL)
                printf("oooo\n");
            else 
            {
                while(environ)
                {
                    printf("%s", environ->var);
                    if(environ->operator)
                         printf("=");
                    if(environ->value)
                        printf("\"%s\"",environ->value );
                    printf("\n");
                    environ = environ->next;
                }
                return (1);
            }
        }
        else 
        {
            printf("syntax error!");
            return(0); 
        }          
    }
    else 
        return(-1);
}

