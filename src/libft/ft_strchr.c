/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 23:59:30 by sid-bell          #+#    #+#             */
/*   Updated: 2019/11/01 06:21:46 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char *ss;

	ss = (char *)s;
	while (*ss != '\0')
	{
		if (*ss == (char)c)
			return (ss);
		ss++;
	}
	if (*ss == (char)(c))
		return (ss);
	return (NULL);
}
