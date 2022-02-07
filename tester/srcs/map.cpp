/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehaenec <jehaenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 19:48:05 by vneirinc          #+#    #+#             */
/*   Updated: 2022/02/07 15:42:26 by jehaenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_set/map_set.hpp"
#include "ms_main.hpp"
#include <map>
#include <utility>
#include "../../includes/map/Map.hpp"
#include "../../includes/utils.hpp"

int	map(void)
{
#ifndef NOPRINT
	std::cout << std::setw(48) << std::string(PURPLE) + "map" + EOC << std::endl;
#endif
	map_set<NAMESPACE::map<int, int> >();
#ifndef NOPRINT
	std::cout << std::endl << std::setw(48) << "compare:" << std::endl;
#endif
	n_map_set::insert<NAMESPACE::map<int, int, std::greater<int> > >(-1);
	return 0;
}