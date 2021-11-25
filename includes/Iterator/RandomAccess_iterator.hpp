/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RandomAccess_iterator.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehaenec <jehaenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:29:16 by jehaenec          #+#    #+#             */
/*   Updated: 2021/11/25 14:56:22 by jehaenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP

#include "Iterator.hpp"

namespace ft{
    template <typename T, class not_const_T =T>
    class random_access_iterator : public ft::iterator<random_access_iterator_tag>
    {
        public:
            typename typedef ft::iterator<random_access_iterator_tag, T>::iterator_category     iterator_category;
            typename typedef ft::iterator<random_access_iterator_tag, T>::pointer               pointer;
            typename typedef ft::iterator<random_access_iterator_tag, T>::reference             reference;
            typename typedef ft::iterator<random_access_iterator_tag, T>::value_type            value_type;
            typename typedef ft::iterator<random_access_iterator_tag, T>::difference_type       difference_type;
        //
        //CONSTRUCTOR + DESTRUCTOR + ASSIGNATION OVERLOAD
        //
        random_access_iterator():_ptr(nullptr){
        }
        
        random_access_iterator(const random_access_iterator<not_const_T> &origin):_ptr(origin->getPtr()){
        }
        
        random_access_iterator(pointer pointer): _ptr(pointer){
        }
        
        virtual ~random_access_iterator(){}
        
        random_access_iterator & operator=(const random_access_iterator<not_const_T> &origin){
            this->_ptr = origin.getPtr();
            return (*this)
        }

        const pointer getPtr()const{
            return (this->ptr);
        }
        //
        //INCREMENT + DECREMENT
        //
        random_access_iterator operator++(){
            this->_ptr++;
            return (*this);
        }
        random_access_iterator operator++(int){
            random_access_iterator tmp = *this;
            this->ptr++;
            return (tmp);
        }
        random_access_iterator operator--(){
            this->_ptr--;
            return (*this);
        }
        random_access_iterator operator--(int){
            random_access_iterator tmp = *this;
            this->ptr--;
            return (tmp);
        }
        //
        //OVERLOAD COMPARE OPERATOR
        //
        bool operator!=(const random_access_iterator<not_const_T> &other){
            return (this->getPtr() != other.getPtr());
        }
        bool operator==(const random_access_iterator<not_const_T> &other){
            return (this->getPtr() == other.getPtr());
        }
        bool operator>(const random_access_iterator<not_const_T> &other){
            return (this->getPtr() > other.getPtr());
        }
        bool operator<(const random_access_iterator<not_const_T> &other){
            return (this->getPtr() < other.getPtr());
        }
        bool operator>=(const random_access_iterator<not_const_T> &other){
            return (this->getPtr() >= other.getPtr());
        }
        bool operator<=(const random_access_iterator<not_const_T> &other){
            return (this->getPtr() <= other.getPtr());
        }
        //
        // ADDITION + SOUSTRACTION OVERLOAD
        //
        private:
            pointer _ptr;   
    };
};

#endif
