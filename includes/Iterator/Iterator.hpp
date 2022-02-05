/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehaenec <jehaenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 12:10:53 by jehaenec          #+#    #+#             */
/*   Updated: 2022/02/05 15:33:13 by jehaenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iostream>
#include <string>
#include <memory>
#include <iterator>

namespace ft
{
    template< class Iter >
    struct iterator_traits
    {
        public:
            typedef typename Iter::difference_type      difference_type;
            typedef typename Iter::pointer              pointer;
            typedef typename Iter::reference            reference;
            typedef typename Iter::iterator_category    iterator_category;
            typedef typename Iter::value_type           value_type;
    };  

    template< class T >
    struct iterator_traits<T*>
    {
        public:
            typedef std::ptrdiff_t                      difference_type;
            typedef T                                   value_type;
            typedef T*                                  pointer;
            typedef T&                                  reference;
            typedef std::random_access_iterator_tag     iterator_category;
    };
 template <class Category, class Pointer, class Distance = ptrdiff_t>
    struct iterator : public iterator_traits<Pointer>
    {
        typedef Distance  difference_type;
        typedef Category iterator_category;
     };
}

#endif