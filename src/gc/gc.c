//
// Created by corecaps on 23/08/23.
//

#include "./../../inc/cub3d.h"
#include "./../../inc/gc.h"
#include <limits.h>
void	*ft_memset(void *s, int c, size_t n)
{
    char	*ptr;
    size_t	pos;

    ptr = (char *)s;
    pos = 0;
    while (pos < n)
    {
        ptr[pos] = c;
        pos ++;
    }
    return (s);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
    void	*r_ptr;

    if ((size == 0) || (nmemb == 0))
        return (malloc(0));
    if ((size >= INT_MAX / nmemb) || (nmemb >= INT_MAX / size))
        return (NULL);
    r_ptr = malloc(size * nmemb);
    if (r_ptr == NULL)
        return (NULL);
    ft_memset(r_ptr, 0, nmemb * size);
    return ((char *)r_ptr);
}


int	gc_check_double(t_garbage *gc, void *ptr)
{
    t_garbage	*tmp;

    tmp = gc;
    while (tmp)
    {
        if (tmp->ptr == ptr)
            return (1);
        tmp = tmp->next;
    }
    return (0);
}

t_garbage **gc_add(t_garbage *ptr)
{
    static t_garbage *garbage = NULL;
    t_garbage *new;

    if (ptr == NULL)
        return (&garbage);
    if (garbage && gc_check_double(garbage, ptr))
        return (&garbage);
    new = malloc(sizeof(t_garbage));
    if (!new)
        return (NULL);
    new->ptr = ptr;
    if (garbage)
        new->next = garbage;
    else
        new->next = NULL;
    garbage = new;
    return (&garbage);
}
void	gc_free(void)
{
    t_garbage	*tmp;
    t_garbage	**garbage;
    t_garbage	*cursor;

    garbage = gc_add(NULL);
    if (!(*garbage))
        return ;
    cursor = *garbage;
    while (cursor)
    {
        tmp = cursor;
        cursor = cursor->next;
        free(tmp->ptr);
        free(tmp);
    }
    (*garbage) = NULL;
}

int	gc_del(void *ptr)
{
    t_garbage	*cursor;
    t_garbage	**gc;
    t_garbage	*prev;

    gc = gc_add(NULL);
    cursor = *gc;
    if (!cursor)
        return (0);
    prev = NULL;
    while (cursor)
    {
        if (cursor->ptr == ptr)
        {
            if (prev)
                prev->next = cursor->next;
            else
                (*gc) = cursor->next;
            free(cursor->ptr);
            free(cursor);
            return (1);
        }
        prev = cursor;
        cursor = cursor->next;
    }
    return (0);
}

void	*gc_alloc(size_t nmemb, size_t size)
{
    void	*ptr;

    ptr = ft_calloc(nmemb, size);
    if (!ptr)
        return (NULL);
    gc_add(ptr);
    return (ptr);
}