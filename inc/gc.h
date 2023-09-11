//
// Created by corecaps on 23/08/23.
//

#ifndef GC_H
#define GC_H
typedef struct s_garbage
{
    void			*ptr;
    struct s_garbage	*next;
}	t_garbage;
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memset(void *s, int c, size_t n);
#endif //CUB3D_GC_H