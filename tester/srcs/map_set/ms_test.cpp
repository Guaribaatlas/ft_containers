/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_test.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehaenec <jehaenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 15:31:40 by vneirinc          #+#    #+#             */
/*   Updated: 2022/02/07 11:24:07 by jehaenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_test.hpp"

namespace	n_map_set
{


void	ms_lst_push(std::list<int>& lst, int value)
{
	lst.push_back(value);
}

void	ms_lst_push(std::list<NAMESPACE::pair<const int, int> >& lst, int value)
{
	lst.push_back(NAMESPACE::pair<const int, int>(value, value));
}

void	ms_print_it(NAMESPACE::map<int, int>::const_iterator it)
{
#ifndef NOPRINT
	std::cout << it->first << " . " << it->second << std::endl;
#endif
	(void)it;
}

void	ms_print_it(NAMESPACE::map<int, int>::iterator it)
{
#ifndef NOPRINT
	std::cout << it->first << " . " << it->second << std::endl;
#endif
	(void)it;
}

}