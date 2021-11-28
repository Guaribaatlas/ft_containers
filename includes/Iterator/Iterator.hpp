/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehaenec <jehaenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 12:10:53 by jehaenec          #+#    #+#             */
/*   Updated: 2021/11/25 23:22:25 by jehaenec         ###   ########.fr       */
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
    template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
    struct iterator
    {
        typedef T         value_type;
        typedef Distance  difference_type;
        typedef Pointer   pointer;
        typedef Reference reference;
        typedef Category  iterator_category;
     };
     
    struct bidirectionnal_iterator_tag{};
    struct forward_iterator_tag{};
    struct randomaccess_iterator_tag{};
    struct reverse_iterator_tag{};


    template< class Iter >
    struct iterator_traits
    {
            typedef typename Iter::Difference_type Difference_type;
            typedef typename Iter::Pointer   pointer;
            typedef typename Iter::Reference reference;
            typedef typename Iter::Category  iterator_category;
    };  

    template< class T >
    struct iterator_traits<T*>
    {
            typedef typename std::ptrdiff_t             Difference_type;
            typedef typename T*                         pointer;
            typedef typename T&                         reference;
            typedef typename Random_access_iterator     iterator_category;
    };

    template< class T >
    struct iterator_traits<const T*>
    {
            typedef typename std::ptrdiff_t             Difference_type;
            typedef typename T*                         pointer;
            typedef typename T&                         reference;
            typedef typename Random_access_iterator     iterator_category;
    };
}

#endif