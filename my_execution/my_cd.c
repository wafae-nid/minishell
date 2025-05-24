/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 17:20:00 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/05/24 17:11:15 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	int	count_words(const char *s, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if ((s[i] != c)
			&& (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static	int	count_lengh_of_words(const char *s, char c, int i)
{
	int	count;

	count = 0;
	while (s[i] && s[i] != c)
	{
		count++;
		i++;
	}
	return (count);
}

static	char	*next_pointer_word(const char *s, char c, int *i)
{
	while (s[*i] && s[*i] == c)
		(*i)++;
	if (!s[*i])
		return (NULL);
	return ((char *)s + (*i));
}

static	void	fill_in(char **ptr, const char *s, int *i, char c)
{
	int	index;

	index = 0;
	while (s[*i] && s[*i] != c)
	{
		(*ptr)[index] = s[*i];
		(*i)++;
		index++;
	}
	(*ptr)[index] = '\0';
}

static char	**ft_split(const char *s, char c)
{
	int		i;
	int		j;
	char	**ptr;

	if (!s)
		return (NULL);
	ptr = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!ptr)
		return (NULL);
	(1 && (i = 0), (j = 0));
 	while (j < count_words(s, c))
	{
		if (!next_pointer_word(s, c, &i))
			break ;
		ptr[j] = (char *)malloc(count_lengh_of_words(s, c, i) + 1);
		if (!ptr[j])
		{
			while (--j >= 0)
				free(ptr[j]);
			return (free(ptr), NULL);
		}
		fill_in(&ptr[j++], s, &i, c);
	}
	ptr[j] = NULL;
	return (ptr);
}
// int ft_strlen(const char  *str)
// {
//     int i;
    
//     i = 0;
//     if(str == NULL)
//         return(0);
//     while(str[i])
//     {
//         i++;
//     }
//     return(i);
// }
// static void *ft_memcpy(void *dst, const void *src, size_t n)
// {
// 	unsigned char		*ptr;
// 	unsigned const char	*ptr2;
// 	size_t				i;

// 	if (dst == src)
// 	{
// 		return ((void *)src);
// 	}
// 	ptr = (unsigned char *)dst;
// 	ptr2 = (unsigned const char *)src;
// 	i = 0;
// 	while (i < n)
// 	{
// 		ptr[i] = ptr2[i];
// 		i++;
// 	}
// 	return (dst);
// }

// char *ft_strdup(const char	*s1)
// {
// 	char	*ptr;

// 	if (!s1)
// 		return (NULL);
//  	ptr = (char *)malloc(ft_strlen(s1) + 1);
// 	if (ptr == NULL)
// 	{
// 		return (NULL);
// 	}
// 	ptr = ft_memcpy(ptr, s1, ft_strlen(s1));
// 	ptr[ft_strlen(s1)] = '\0';
// 	return (ptr);
// }

static	void	loop_copying_s2(const char *s2, char **ptr, int count)
{
	int	i;

	i = 0;
	while (s2[i])
	{
		(*ptr)[count] = s2[i];
		i++;
		count++;
	}
	(*ptr)[count] = '\0';
}

char	*ft_strjoin_(const char *s1, const char *s2)
{
	char	*ptr;
	size_t	i;
	size_t	count;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	ptr = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	count = i;
	loop_copying_s2(s2, &ptr, count);
	return (ptr);
}

static char *extract_the_cd_path(char *readline)
{
	char **splited;
	

	splited = ft_split(readline, ' ');
	if(!splited)
		return(NULL);
	else 
	{
		if(count_words(readline, ' ') == 2)
			return (splited[1]);
		else
			return(NULL);
	}
}


// int main()
// {
//     char *new_path;
// 	char *new;
//     char *PWD;
// 	char *OLDPWD;
// 	char *prompt;
// 	char *read_line;

// 	// PWD = getenv("PWD");
// 	//prompt = ft_strjoin(PWD, "> ");
// 	//read_line = readline(prompt);
// 	//OLDPWD = getenv("OLDPWD");
// 	//while(1)
// 	//{
// 		//new = extract_the_cd_path(read_line);

// 		//if(!strcmp(new, "-"))
// 		//{
// 		//	prompt = ft_strjoin(OLDPWD, ">");
// 		////	readline(prompt);
// 			//setenv("OLDPWD", PWD,1);
// 			//setenv("PWD", OLDPWD, 1);          
// 			//PWD=getenv("PWD");
// 			//OLDPWD=getenv("OLDPWD");
// 		//}
// 		//else
// 		//{
//    		// 	// if(!chdir(new))
// 		// 	// {
// 		// 	//  	new_path = getcwd(NULL,0) ;
// 		// 	// 	setenv("OLDPWD",PWD,1);
// 		// 	// 	setenv("PWD", new_path, 1);
// 		// 	// 	PWD = getenv("PWD");
// 		// 	// 	OLDPWD = getenv("OLDPWD");
// 		// 	//  	prompt = ft_strjoin(PWD, "> ");
// 		// 	// 	read_line = readline(prompt);
// 		// 	// }()
// 		// }
// 		PWD=getenv("PWD");
// 		prompt= ft_strjoin(PWD,"> ");
// 		read_line=readline(prompt);
// 		while(1)
// 		{
// 			//prompt = ft_strjoin(PWD,"> ");
// 			//read_line=readline(prompt);
// 			new = extract_the_cd_path(read_line);
// 			if(!strcmp(new,"-"))
// 			{
// 				OLDPWD=getenv("OLDPWD");
// 				prompt= ft_strjoin(OLDPWD,"> ");
// 				read_line=readline(prompt);
// 				setenv("OLDPWD",PWD,1);
// 				setenv("PWD",OLDPWD,1);
// 				PWD=getenv("PWD");
// 				OLDPWD=getenv("OLDPWD");
// 			}
// 			else
// 			{
// 				if(!chdir(new))
// 				{
// 					new_path = getcwd(NULL,0);
// 					prompt = ft_strjoin(new_path, "> ");
// 					read_line = readline(prompt);
// 					PWD=getenv("PWD");
// 					setenv("OLDPWD", PWD,1);
// 					setenv("PWD", new_path ,1);
// 				}
// 			}

// 		}
// 	}
		
// // }
// ***
//int main()
//{
  //  char *new_path;
    //char *new;
    //char *PWD;
    //char *OLDPWD;
    //char *prompt;
    //char *read_line;

    //PWD = getenv("PWD");
    //while (1)
    //{
        // Generate prompt with the current PWD
      //  prompt = ft_strjoin(PWD, "> ");
        //if (!prompt)
        //{
          //  perror("Memory allocation failed");
            //return 1;
        //}

        //read_line = readline(prompt);
        //free(prompt); // Free the dynamically allocated prompt
        //if (!read_line)
          //  break; // Exit on EOF (Ctrl+D)

        //new = extract_the_cd_path(read_line);
        //free(read_line); // Free the dynamically allocated read_line
        //if (!new)
        //{
          //  fprintf(stderr, "Invalid command\n");
            //continue;
        //}

        //if (!strcmp(new, "-"))
        //{
          //  OLDPWD = getenv("OLDPWD");
           // if (!OLDPWD)
            //{
              //  fprintf(stderr, "OLDPWD not set\n");
                //continue;
            //}
            //if (chdir(OLDPWD) == 0)
            //{
              //  setenv("OLDPWD", PWD, 1);
                //setenv("PWD", OLDPWD, 1);
                //PWD = getenv("PWD");
            //}
            //else
            //{
              //  perror("chdir");
            //}
        //}
        //else
        //{
          //  if (chdir(new) == 0)
            //{
              //  new_path = getcwd(NULL, 0); // Get current working directory
                //if (new_path)
                //{
                  //  setenv("OLDPWD", PWD, 1);
                    //setenv("PWD", new_path, 1);
                    //free(new_path); // Free the allocated memory for new_path
                    //PWD = getenv("PWD");
                //}
                //else
                //{
                  //  perror("getcwd");
                //}
            //}
            //else
            //{
              //  perror("chdir");
            //}
        //}
    //}
    //return 0;
//}
// static char *cd_telda()
static void  cd_oldpwd(char *PWD)
{
    char *OLDPWD;
    
		OLDPWD=getenv("OLDPWD");
		if(!chdir(OLDPWD))
		{
			setenv("OLDPWD", PWD,1);
			setenv("PWD",OLDPWD,1);
		}
		else
			printf("error!");
}
static void cd_home(char *PWD)
{
    char *HOME;
    
    HOME=getenv("HOME");
	if(!chdir(HOME))
	{
		setenv("OLDPWD", PWD,1);
		setenv("PWD", HOME,1);
	}
		else
		printf("error!");
}
static char *get_deleted_path_gain(char *PWD, char *new)
{
	char *deleted_path;

	char *pwd_for_path;
	pwd_for_path = ft_strjoin(PWD, "/", GLOBAL);
	if(!pwd_for_path)
		return (NULL);
	deleted_path = ft_strjoin(pwd_for_path, new, GLOBAL);
	if(!deleted_path)
		return(NULL);
	else
		return(deleted_path);
}
static void new_path_cd(char *new,char *PWD)
{
    char *new_path;
	char *save_first_gtwcd;
	
	if(!chdir(new))
	{
		new_path = getcwd(NULL,0);
		if(!new_path)
		{
			printf("getcwd cant reach directory \n");
			new_path = get_deleted_path_gain(PWD, new);
		}
		setenv("OLDPWD", PWD,1);
		setenv("PWD", new_path,1);
	}
	else
	{
		printf("chdir error");
		return;
	}
}

static char *telda_full_path(char **telda_path)
{
	char *telda_full_path;
	
	if(!telda_path ||!(*telda_path))
		return(NULL);
	if((*telda_path)[0] == '~')
		(*telda_path)++;
	telda_full_path = ft_strjoin("/home/wnid-hsa", (*telda_path), GLOBAL);
	if(!telda_full_path)
		return(NULL);
	else
		return(telda_full_path);
}
		
void cd_execution(t_com *command, char *PWD)
{
	char *telda_path;
	
    if((command->command)[2])
    {
        printf("too many arguments");
        return;
    }
	if((command->command)[1] &&((command->command)[1],F_OK)!= 0)
	{
		printf("directory not found");
		return;
    }
	else if((command->command)[1] && !strcmp((command->command)[1],"-"))
        cd_oldpwd(PWD);
	else if (((command->command)[1] && !strcmp((command->command)[1], "~")) || (command->command)[1]== NULL)
    	cd_home(PWD);
	else if (command->command[1][0] == '~' )
	{
		telda_path = telda_full_path(&(command->command[1]));
		if(!telda_path)
			return;
		new_path_cd(telda_path,PWD);
	}
	else
        new_path_cd((command->command)[1],PWD);
}
