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
#endif //CUB3D_GC_H