/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 18:41:11 by edescoin          #+#    #+#             */
/*   Updated: 2017/08/21 18:32:51 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>

typedef enum			e_gbc_action
{
	ADD,
	REMOVE,
	CLEAR
}						t_gbc_action;

typedef struct			s_garbage
{
	void				*ptr;
	void				(*delete_)();
	struct s_garbage	*next;
	struct s_garbage	*prev;
}						t_garbage;

void					exit_error(char *prog, char *err);
void					exit_custom_error(char *prog, char *err);
int						forint(int *i, int reset, int cond);
int						fordbl(double *d, double reset, int cond);
int						forptr(void **p, void *reset, int cond);
int						ft_atoi(const char *nptr);
int						ft_atoi_base(const char *nptr, int base);
void					ft_bzero(void *s, size_t n);
void					*garbage_collector(t_gbc_action action, void *ptr,
											void (*fct)());
int						ft_intlen(int n);
int						ft_isalnum(int c);
int						ft_isalpha(int c);
int						ft_isascii(int c);
int						ft_isdigit(int c);
int						is_number(char *str);
int						ft_isprint(int c);
int						ft_isspace(int c);
char					*ft_itoa(int n);
char					*ft_itoa_base(int n, int base);
void					*ft_memalloc(size_t size);
void					*ft_memccpy(void *dest, const void *src, int c,
									size_t n);
int						ft_memccnt(const char *s, int c, size_t n);
void					*ft_memchr(const void *s, int c, size_t n);
int						ft_memcmp(const void *s1, const void *s2, size_t n);
void					*ft_memcpy(void *dest, const void *src, size_t n);
void					ft_memdel(void **ap);
void					*ft_memmove(void *dest, const void *src, size_t n);
void					*ft_memset(void *s, int c, size_t n);
int						ft_max(int i1, int i2);
int						ft_min(int i1, int i2);
void					dbg_pause(void);
long					ft_pow(long n, int p);
void					ft_putnbr(int n);
void					ft_putnbr_fd(int n, int fd);
void					ft_putstr(char const *s);
void					ft_putstr_fd(char const *s, int fd);
void					*return_free(void *ret, void *ptr);
int						ft_sqrt(int nb);
char					*ft_strcat(char *s1, const char *s2);
char					*ft_strcdup(const char *s, char c);
char					*ft_strchr(const char *s, int c);
size_t					ft_strclen(const char *s, char c);
void					ft_strclr(char *s);
int						ft_strcmp(const char *s1, const char *s2);
char					*ft_strcpy(char *dst, const char *src);
void					ft_strdel(char **as);
char					*ft_strdup(const char *s1);
int						ft_strequ(char const *s1, char const *s2);
void					ft_striter(char *s, void (*f)(char *));
void					ft_striteri(char *s, void (*f)(unsigned int, char *));
char					*ft_strjoin(char const *s1, char const *s2);
size_t					ft_strlcat(char *dst, const char *src, size_t size);
size_t					ft_strlen(const char *s);
char					*ft_strncat(char *s1, const char *s2, size_t n);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
char					*ft_strncpy(char *dst, const char *src, size_t len);
int						ft_strnequ(char const *s1, char const *s2, size_t n);
char					*ft_strnew(size_t size);
char					*ft_strnstr(const char *big, const char *little,
									size_t l);
char					*ft_strrchr(const char *s, int c);
char					*ft_strrealloc(char *src, size_t new_size);
char					*ft_strrev(char *s);
char					*ft_strspc(char *s);
char					**ft_strsplit(char const *s, char c);
char					*ft_strstr(const char *big, const char *little);
char					*ft_strsub(char const *s, unsigned int start,
									size_t len);
char					*ft_strtrim(char const *s);
double					ft_to_deg(double rad);
int						ft_tolower(int c);
double					ft_to_rad(double deg);
int						ft_toupper(int c);

#endif
