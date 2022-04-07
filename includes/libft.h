/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrianofaus <adrianofaus@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 19:11:12 by roaraujo          #+#    #+#             */
/*   Updated: 2022/04/07 17:38:32 by adrianofaus      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>

# define BUFFER_SIZE	50

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int			contains_nl(char *string);
long int	ft_atoli(const char *nptr);
int			ft_atoi(const char *nptr);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
void		ft_close_pipe_fds(int *pipe);
void		ft_free_arr(void ***ptr);
void		ft_free_ptr(void **ptr);
char		*ft_get_next_line(int fd);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isnumeric_s(char *str);
int			ft_isprint(int c);
char		*ft_itoa(int n);
void		ft_lst_add_back(t_list **lst, t_list *new);
void		ft_lst_add_front(t_list **lst, t_list *new);
void		ft_lst_clear(t_list **lst, void (*del)(void *));
void		ft_lst_delone(t_list *lst, void (*del)(void *));
void		ft_lst_iter(t_list *lst, void (*f)(void *));
t_list		*ft_lst_last(t_list *lst);
t_list		*ft_lst_new(void *content);
void		ft_lst_remove_node(t_list **lst_head, t_list *node_to_delete);
int			ft_lst_size(t_list *lst);
t_list		*ft_lst_map(t_list *lst, void *(*f)(void *), void (*del)(void *));
void		*ft_memccpy(void *dest, const void *src, int c, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		*ft_memset(void *s, int c, size_t n);
void		ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_putstr_fd(char *s, int fd);
char		**ft_split(char const *s, char c);
char		*ft_strchr(const char *s, int c);
char		*ft_strdup(const char *s);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strjoin_3(char *str1, char *str2, char *str3);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
size_t		ft_strlcpy(char *dst, const char *src, size_t dest_size);
size_t		ft_strlen(const char *s);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		*ft_strrchr(const char *s, int c);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			ft_tolower(int c);
int			ft_toupper(int c);
char		*ft_uitoa(unsigned int n);
char		*ft_uitohex(unsigned int n, char *base_str);
char		*ft_ulitohex(unsigned long int n, char *base_str);
void		ft_free_pipe_arr(int ***pipe_arr, int n);
int			**ft_make_pipes(int total_pipes);

#endif 