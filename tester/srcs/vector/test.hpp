/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehaenec <jehaenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 09:32:46 by vneirinc          #+#    #+#             */
/*   Updated: 2022/02/07 11:16:23 by jehaenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_HPP
# define TEST_HPP

# define GREEN "\e[92m"
# define YELLOW "\e[93m"
# define PURPLE "\e[95m"
# define EOC "\e[0m"

# include "../../../includes/vector/Vector.hpp"
# include "../common_shared.hpp"
# include <vector>

# define TYPE int
# define CONT vector<TYPE>

namespace	n_vec
{

int	member_type(void);
int	constructor(void);
int	capacity(void);
int	iterator(void);
int	r_iterator(void);
int	test_clear(void);
int access(void);
int	all_operator(void);

int	test_push_pop(int size);
int	assign(int size);
int	erase(int size);
int	insert(int size);
int	insert2(int size);
int	resize(int size);
}
#endif