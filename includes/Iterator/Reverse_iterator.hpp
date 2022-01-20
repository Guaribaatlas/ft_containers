/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehaenec <jehaenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 23:15:27 by jehaenec          #+#    #+#             */
/*   Updated: 2022/01/20 18:09:38 by jehaenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "Iterator.hpp"

namespace ft
{
    template <class Iter>
    class reverse_iterator
    {
        		public:

		typedef				Iter											iterator_type;
		typedef	typename	ft::iterator_traits<Iter>::iterator_category	iterator_category;
		typedef	typename	ft::iterator_traits<Iter>::value_type			value_type;
		typedef	typename	ft::iterator_traits<Iter>::difference_type		difference_type;
		typedef	typename	ft::iterator_traits<Iter>::pointer				pointer;
		typedef	typename	ft::iterator_traits<Iter>::reference			reference;
        //
        //CONSTRUCTOR + DESTRUCTOR + ASSIGNATION OVERLOAD
        //
        reverse_iterator():_ptr(nullptr){
        }
        
        reverse_iterator(const reverse_iterator<Iter> &origin):_ptr(origin->getPtr()){
        }
        
        reverse_iterator(pointer pointer): _ptr(pointer){
        }
        
        virtual ~reverse_iterator(){}
        
        reverse_iterator & operator=(const reverse_iterator<Iter> &origin){
            this->_ptr = origin.getPtr();
            return (*this);
        }
        
        reverse_iterator & operator-=(difference_type n){
            this->_ptr += n;
            return (*this);
        }
        
        reverse_iterator & operator+=(difference_type n){
            this->_ptr -= n;
            return (*this);
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
            return(*(*this + i));
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
            return (a.base() > b.base());
        }
    template <class Iterator1, class Iterator2>
    bool operator>(const reverse_iterator<Iterator1> &a, const reverse_iterator<Iterator2> &b){
            return (a.base() < b.base());
        }
        //
        // ADDITION + SOUSTRACTION OVERLOAD
        //

    template <class Iterator>
    reverse_iterator<Iterator> operator+(const reverse_iterator<Iterator> &a, typename reverse_iterator<Iterator>::difference_type b){
            return (reverse_iterator<Iterator>(a.base() - b));
        }
    template <class Iterator1, class Iterator2>
    typename reverse_iterator<Iterator1>::difference_type operator-(const reverse_iterator<Iterator1> &a, const reverse_iterator<Iterator2> &b){
            return (a.base() + b.base());
            
        }
}

#endif
