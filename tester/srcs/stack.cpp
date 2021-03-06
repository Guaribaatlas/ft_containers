/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehaenec <jehaenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 21:48:04 by vneirinc          #+#    #+#             */
/*   Updated: 2022/02/07 15:36:08 by jehaenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack/test.hpp"

int	stack(void)
{
	std::cout << std::setw(48) << std::string(PURPLE) + "stack" + EOC << std::endl;
	n_stack::member_type();
	n_stack::test_push_pop();
	n_stack::constructor();
	n_stack::empty();
	n_stack::all_operator();
	return 0;
}

