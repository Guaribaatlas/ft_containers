/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   speed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehaenec <jehaenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 16:05:06 by vneirinc          #+#    #+#             */
/*   Updated: 2022/02/07 11:17:46 by jehaenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "srcs/vector/test.hpp"
#include "srcs/map_set/map_set.hpp"
#include <chrono>

int	getSize(int ac, char** av)
{
	if (ac > 1)
		try { return std::stoi(av[1]); } catch (...) {}
	return -1;
}

int	main(int ac, char** av)
{
	long long tmp;
	int	size = getSize(ac, av);

	std::cout << "size: " << size << std::endl;
		//
	//				VECTOR
		//
	std::cout << std::setw(48) << std::string(PURPLE) + "vector" + EOC << std::endl;

	tmp = std::chrono::system_clock::now().time_since_epoch().count();
	n_vec::insert(size);
	std::cout << "insert: " << (std::chrono::system_clock::now().time_since_epoch().count()) - tmp << std::endl;

	tmp = std::chrono::system_clock::now().time_since_epoch().count();
	n_vec::erase(size);
	std::cout << "erase: " << (std::chrono::system_clock::now().time_since_epoch().count()) - tmp << std::endl;

	tmp = std::chrono::system_clock::now().time_since_epoch().count();
	n_vec::resize(size);
	std::cout << "resize: " << (std::chrono::system_clock::now().time_since_epoch().count()) - tmp << std::endl;

	tmp = std::chrono::system_clock::now().time_since_epoch().count();
	n_vec::assign(size);
	std::cout << "assign: " << (std::chrono::system_clock::now().time_since_epoch().count()) - tmp << std::endl;
		//
	//				SET/MAP
		//

	tmp = std::chrono::system_clock::now().time_since_epoch().count();
	n_map_set::insert<NAMESPACE::map<int, int> >(size);
	std::cout << "insert: " << (std::chrono::system_clock::now().time_since_epoch().count()) - tmp << std::endl;

	tmp = std::chrono::system_clock::now().time_since_epoch().count();
	std::cout << "erase: " << (std::chrono::system_clock::now().time_since_epoch().count()) - tmp << std::endl;

	tmp = std::chrono::system_clock::now().time_since_epoch().count();
	n_map_set::find_count<NAMESPACE::map<int, int> >(size);
	std::cout << "find_count: " << (std::chrono::system_clock::now().time_since_epoch().count()) - tmp << std::endl;
	return 1;
}
