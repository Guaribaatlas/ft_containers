/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RandomAccess_iterator.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehaenec <jehaenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:29:16 by jehaenec          #+#    #+#             */
/*   Updated: 2021/11/25 23:23:42 by jehaenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP

#include "Iterator.hpp"

namespace ft
{
    template <typename T, class not_const_T =T>
    class random_access_iterator : public ft::iterator<random_access_iterator_tag, T>
    {
        public:
            typedef typename ft::iterator<random_access_iterator_tag, T>::iterator_category     iterator_category;
            typedef typename ft::iterator<random_access_iterator_tag, T>::pointer               pointer;
            typedef typename ft::iterator<random_access_iterator_tag, T>::reference             reference;
            typedef typename ft::iterator<random_access_iterator_tag, T>::value_type            value_type;
            typedef typename ft::iterator<random_access_iterator_tag, T>::difference_type       difference_type;
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
            return (*this);
        }
        random_access_iterator & operator-=(difference_type n){
            this->_ptr -= n;
            return (*this);
        }
        random_access_iterator & operator+=(difference_type n){
            this->_ptr += n;
            return (*this);
        }

        pointer base() const{
            return (this->_ptr);
        }
        
        pointer operator->(){
            return (this->_ptr);
        } 

        reference operator*(){
            return (*this->_ptr);
        }
        reference operator[](int i){
            return(this->ptr[i]);
        }
        //
        //INCREMENT + DECREMENT
        //
        random_access_iterator & operator++(){
            this->_ptr++;
            return (*this);
        }
        random_access_iterator operator++(int){
            random_access_iterator tmp = *this;
            this->ptr++;
            return (tmp);
        }
        random_access_iterator  & operator--(){
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
        
        private:
            pointer _ptr;   
    };

    
    template <class Iterator1, class Iterator2>
    bool operator!=(const random_access_iterator<Iterator1> &a, const random_access_iterator<Iterator2> &b){
            return (a.base() != b.base());
            }
    template <class Iterator1, class Iterator2>
    bool operator==(const random_access_iterator<Iterator1> &a, const random_access_iterator<Iterator2> &b){
            return (a.base() == b.base());
        }
    template <class Iterator1, class Iterator2>
    bool operator>=(const random_access_iterator<Iterator1> &a, const random_access_iterator<Iterator2> &b){
            return (a.base() >= b.base());
        }
    template <class Iterator1, class Iterator2>
    bool operator<=(const random_access_iterator<Iterator1> &a, const random_access_iterator<Iterator2> &b){
            return (a.base() <= b.base());
        }
    template <class Iterator1, class Iterator2>
    bool operator<(const random_access_iterator<Iterator1> &a, const random_access_iterator<Iterator2> &b){
            return (a.base() < b.base());
        }
    template <class Iterator1, class Iterator2>
    bool operator>(const random_access_iterator<Iterator1> &a, const random_access_iterator<Iterator2> &b){
            return (a.base() > b.base());
        }
        //
        // ADDITION + SOUSTRACTION OVERLOAD
        //

    template <class Iterator>
    random_access_iterator<Iterator> operator+(const random_access_iterator<Iterator> &a, typename random_access_iterator<Iterator>::difference_type b){
            return (random_access_iterator<Iterator>(a.base() + b));
        }
    template <class Iterator1, class Iterator2>
    typename random_access_iterator<Iterator1>::difference_type operator-(const random_access_iterator<Iterator1> &a, const random_access_iterator<Iterator2> &b){
            return (a.base() - b.base());
            
        }
}

#endif
