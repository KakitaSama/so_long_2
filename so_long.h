#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <mlx.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

char	**ft_split(char const *str, char c);
int		ft_fr(char **s);
char	*get_next_line(int fd);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_strdup(char *s1);
char	*ft_strjoin(char *s1, char *s2);
int		ft_search(char *buf);
int		ft_strlen(char *s);
char	*get_next_line(int fd);
int		ft_prework(char **buf, char **str, char **ans, char *tmp);
int		ft_res(char **buf, char **str, char **ans, int p);
int		ft_looping(char **buf, char **str, char **ans, int fd);
#endif
