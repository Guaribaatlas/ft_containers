/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehaenec <jehaenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 23:15:27 by jehaenec          #+#    #+#             */
/*   Updated: 2022/02/05 11:02:10 by jehaenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "Iterator.hpp"

namespace ft
{
    template <typename Iter>
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
        
        explicit reverse_iterator(iterator_type x){
            this->_ptr = x;
        }
    
        template<class U>
        reverse_iterator(const reverse_iterator<U> &origin):_ptr(origin.base()){
        }
        
        reverse_iterator(pointer pointer): _ptr(pointer){
        }
        
        virtual ~reverse_iterator(){}
        
        iterator_type base() const {
			return this->_ptr;
        }
        
        reverse_iterator & operator=(const reverse_iterator<Iter> &origin){
            this->_ptr = origin.base();
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
        
        reverse_iterator operator-(difference_type n)const{
			return (reverse_iterator(this->base() + n));
		}

        reverse_iterator operator+(difference_type n)const{
			return (reverse_iterator(this->base() - n));
		}

        
        pointer operator->(){
            return (&(operator*()));
        } 

        reference operator*()const{
			iterator_type tmp = this->_ptr;
			return *(--tmp);
		}
        reference operator[](int i){
            return(*(*this + i));
        }
        //
        //INCREMENT + DECREMENT
        //
        reverse_iterator& operator++(){
            --_ptr;
            return (*this);
        }
        reverse_iterator operator++(int){
            reverse_iterator tmp = *this;
            --_ptr;
            return (tmp);
        }
        reverse_iterator& operator--(){
            ++_ptr;
            return (*this);
        }
        reverse_iterator operator--(int){
            reverse_iterator tmp = *this;
            ++_ptr;
            return (tmp);
        }

        private:
            iterator_type _ptr;   
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
    reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type b, const reverse_iterator<Iterator> &a){
            return (reverse_iterator<Iterator>(a.base() - b));
        }
        
    template< class Iterator >
	typename reverse_iterator<Iterator>::difference_type operator-( const reverse_iterator<Iterator>& a, const reverse_iterator<Iterator>& b){
		return (b.base() - a.base());
	}
    
    template <class Iterator1, class Iterator2>
    typename reverse_iterator<Iterator1>::difference_type operator-(const reverse_iterator<Iterator1> &a, const reverse_iterator<Iterator2> &b){
            return (b.base() - a.base());
            
        }
}

#endif
