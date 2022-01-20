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
     
   
        struct forward_iterator_tag{};
        struct random_access_iterator_tag{};
        struct reverse_iterator_tag{};
        struct bidirectional_iterator_tag{};

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
            typedef std::ptrdiff_t             Difference_type;
            typedef T*                         pointer;
            typedef T&                         reference;
            typedef random_access_iterator_tag     iterator_category;
    };

    template< class T >
    struct iterator_traits<const T*>
    {
            typedef std::ptrdiff_t             Difference_type;
            typedef T*                         pointer;
            typedef T&                         reference;
            typedef random_access_iterator_tag    iterator_category;
    };
}

#endif