/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timestamp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:50:38 by gde-souz          #+#    #+#             */
/*   Updated: 2024/08/14 14:51:05 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

size_t    get_current_time(void)
{
    struct  timeval tval;
    size_t  total;
    
    if (gettimeofday(&tval, NULL) != 0)
    {
        printf("Error getting timestamp.\n");
        return (0);
    }
    total = (tval.tv_sec * 1000000) + tval.tv_usec;
    return (total);
}

size_t  get_dinner_time(t_dinner **dinner, size_t time)
{
    return ((time - (*dinner)->init_time) / 1000);
}
