/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing_lengh.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:28:31 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/11/02 17:28:32 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../cub3D.h"

int  lengh(int len)
{
    static int llen;

    if(len > llen)
    {
        llen = len;
    }
    return(llen); 
}

int no_tex_len(int len)
{
    static int no;
    
    if(len >0)
    {
        no = len;
    }
    return(no);
}

int we_tex_len(int len)
{
    static int we;
    
    if(len >0)
    {
        we = len;
    }
    return(we);
}

int so_tex_len(int len)
{
    static int so;
    
    if(len >0)
    {
        so = len;
    }
    return(so);
}

int ea_tex_len(int len)
{
    static int ea;
    
    if(len >0)
    {
        ea = len;
    }
    return(ea);
}
