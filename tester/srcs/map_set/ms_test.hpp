/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_test.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehaenec <jehaenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 14:53:14 by vneirinc          #+#    #+#             */
/*   Updated: 2022/02/07 11:18:22 by jehaenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_TEST_HPP
# define MS_TEST_HPP
# include "../common_shared.hpp"
#include <list>
# include <map>
# include "../../../includes/map/Map.hpp"

namespace	n_map_set
{

template <class T>
void	ms_insert(NAMESPACE::map<int, int, T>& c, typename NAMESPACE::map<int, int, T>::iterator it, int val)
{ c.insert(it, NAMESPACE::pair<int, int>(val, val)); }

template <class T>
void	ms_insert(NAMESPACE::map<int, int, T>& c, int val)
{ c.insert(NAMESPACE::pair<int, int>(val, val)); }

void	ms_lst_push(std::list<int>& lst, int value);
void	ms_lst_push(std::list<NAMESPACE::pair<const int, int> >& lst, int value);

void	ms_print_it(NAMESPACE::map<int, int>::const_iterator it);
void	ms_print_it(NAMESPACE::map<int, int>::iterator it);

template <class Cont>
void	ms_erase(Cont& c)
{ c.erase(c.begin()); }

}

#endif