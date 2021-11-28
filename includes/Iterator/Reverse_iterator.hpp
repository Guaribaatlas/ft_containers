/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehaenec <jehaenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 23:15:27 by jehaenec          #+#    #+#             */
/*   Updated: 2021/11/25 23:29:21 by jehaenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "Iterator.hpp"

namespace ft
{
    template <typename T, class not_const_T =T>
    class reverse_iterator : public iterator<random_access_iterator_tag>
    {
        public:
            typename typedef iterator<random_access_iterator_tag, T>::iterator_category     iterator_category;
            typename typedef iterator<random_access_iterator_tag, T>::pointer               pointer;
            typename typedef iterator<random_access_iterator_tag, T>::reference             reference;
            typename typedef iterator<random_access_iterator_tag, T>::value_type            value_type;
            typename typedef iterator<random_access_iterator_tag, T>::difference_type       difference_type;
        //
        //CONSTRUCTOR + DESTRUCTOR + ASSIGNATION OVERLOAD
        //
        reverse_iterator():_ptr(nullptr){
        }
        
        reverse_iterator(const reverse_iterator<not_const_T> &origin):_ptr(origin->getPtr()){
        }
        
        reverse_iterator(pointer pointer): _ptr(pointer){
        }
        
        virtual ~random_access_iterator(){}
        
        reverse_iterator & operator=(const reverse_iterator<not_const_T> &origin){
            this->_ptr = origin.getPtr();
            return (*this)
        }
        
        reverse_iterator & operator-=(difference_type n){
            this->_ptr += n;
            return (*this)
        }
        
        reverse_iterator & operator+=(difference_type n){
            this->_ptr -= n;
            return (*this)
        }
        
        pointer base() const{
            return (this->_ptr);
        }
        
        pointer operator->(){
            return (this->_ptr);
        } 

        reference operator*(){
            return (--(*this->_ptr));
        }
        reference operator[](int i){
            return(this->ptr[i]);
        }
        //
        //INCREMENT + DECREMENT
        //
        reverse_iterator& operator++(){
            this->_ptr--;
            return (*this);
        }
        reverse_iterator operator++(int){
            reverse_iterator tmp = *this;
            this->ptr--;
            return (tmp);
        }
        reverse_iterator& operator--(){
            this->_ptr++;
            return (*this);
        }
        reverse_iterator operator--(int){
            reverse_iterator tmp = *this;
            this->ptr++;
            return (tmp);
        }
        //
        //OVERLOAD COMPARE OPERATOR
        //
        
        private:
            pointer _ptr;   
    };

    
    template <class Iterator1, class Iterator2>
    bool operator!=(const reverse_iterator<Iterator1> &a, const reverse_iterator<Iterator2> &b){
            return (a.base() != b.base());
            }
    template <class Iterator1, class Iterator2>
    bool operator==(const reverse_iterator<Iterator1> &a, const reverse_iterator<Iterator2> &b){
            return (a.base() == b.base());
        }
    template <class Iterator1, class Iterator2>
    bool operator>=(const reverse_iterator<Iterator1> &a, const reverse_iterator<Iterator2> &b){
            return (a.base() <= b.base());
        }
    template <class Iterator1, class Iterator2>
    bool operator<=(const reverse_iterator<Iterator1> &a, const reverse_iterator<Iterator2> &b){
            return (a.base() >= b.base());
        }
    template <class Iterator1, class Iterator2>
    bool operator<(const reverse_iterator<Iterator1> &a, const reverse_iterator<Iterator2> &b){
            return (a.base() < b.base());
        }
    template <class Iterator1, class Iterator2>
    bool operator>(const reverse_iterator<Iterator1> &a, const reverse_iterator<Iterator2> &b){
            return (a.base() > b.base());
        }
        //
        // ADDITION + SOUSTRACTION OVERLOAD
        //

    template <class Iterator>
    reverse_iterator<Iterator> operator+(const reverse_iterator<Iterator> &a, typename reverse_iterator<Iterator>::difference_type b){
            return (random_access_iterator<Iterator1>(a.base() + b));
        }
    template <class Iterator1, class Iterator2>
    typename reverse_iterator<Iterator1>::difference_type operator-(const reverse_iterator<Iterator1> &a, const reverse_iterator<Iterator2> &b){
            return (a.base() - b.base());
            
        }
}

#endif
