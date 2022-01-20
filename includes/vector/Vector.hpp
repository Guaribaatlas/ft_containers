/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehaenec <jehaenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 20:43:10 by jehaenec          #+#    #+#             */
/*   Updated: 2021/12/15 18:09:15 by jehaenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <memory>

#include "../Iterator/Iterator.hpp"
#include "../Iterator/RandomAccess_iterator.hpp"
#include "../Iterator/Reverse_iterator.hpp"

namespace ft
{
    template<class T, class Allocator = std::allocator<T> >
    class vector
    {
        public:
            typedef Allocator                                                       allocator_type;
            typedef T                                                               value_type;
            typedef typename allocator_type::size_type                              size_type;
            typedef typename allocator_type::difference_type                        difference_type;
            typedef typename allocator_type::reference                              reference;
            typedef typename allocator_type::const_reference                        const_reference;
            typedef typename allocator_type::pointer                                pointer;
            typedef typename allocator_type::const_pointer                          const_pointer;
            typedef random_access_iterator<value_type>                              iterator;
            typedef random_access_iterator<const value_type, value_type>            const_iterator;
            typedef reverse_iterator<iterator>                                      reverse_iterator;
            typedef ft::reverse_iterator<const_iterator>                            const_reverse_iterator;
       
            explicit vector(const allocator_type &alloc = allocator_type()): _alloc(alloc), _size(0), _capacity(0){
                _array = _alloc.allocate(_capacity);
            }

            explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type()):_size(0), _capacity(n), _alloc(alloc)
            {
                _array = _alloc.allocate(_capacity);
                for (size_type i = 0; i < _size; i++){
                    _alloc.construct(&_array[i], val);
                    _size++;
                }
            }
        
            vector(const vector& x):_size(x._size), _capacity(x._capacity), _alloc(x._alloc){
                _array = _alloc.allocate(x._size);
                for (size_t i = 0; i < x._size; i++){
                    this->_array[i] = _alloc.construct(this->_array[i], x._array[i]);
                }
            }
            
            ~vector(){   
            }
            
            vector& operator=(const vector& x)
            {
                this->_capacity = x._capacity;
                this->size = x._size;
                this->_alloc = x._alloc;
                this->_array = _alloc.allocate(_capacity);
                for(size_t i; i < _size; i++){
                    this->_array[i] = _alloc.construct(this->_array[i], x._array[i]);
                }
            }
            
            iterator            begin(){
                return(iterator(_array));
            }
            
            const_iterator      begin()const{
                return (const_iterator(_array));
            }

            iterator            end(){
                return (iterator(this->_array + this->_size));
            }  

            const_iterator      end()const{
                return (const_iterator(this->array + this->size));
            }
            
            reverse_iterator    rbegin(){
                return (reverse_iterator(this->begin()));
            }
            
            const_reverse_iterator rbegin()const{
                return (const_reverse_iterator(this->begin()));
            }
            
            reverse_iterator       rend(){
                return (reverse_iterator(this->end()));
            }
            
            const_reverse_iterator rend()const{
                return (const_reverse_iterator(this->end()));
            }

            size_type	size()const{
                return (this->_size);
            }
            size_type	max_size()const{
                return (this->_alloc.max_size());
            }
            
            void		resize (size_type n, value_type val = value_type())
            {
                if (n < _size)
                {
                    while(n < _size)
                        pop_back();
                }
                else if ( n > _size && n < _capacity)
                {
                    for (size_type i = _size; i < n; i++)
                        push_back(val);
                    this->_size = n;
                }
                else
                {
                    reserve(n);
                    for (size_type i = _size; i < n; i++)
                        _alloc.construct(&_array[i], val);   
                    this->_size = n;
                }
            }
            
            size_type	capacity()const{
                return (this->_capacity);
            }
            
            bool		empty()const{
                return (this->size() == 0);
            }
            
            void		reserve(size_type n){
                if (n > this->_capacity)
                    _reallocateVec(n);
            }

            reference       operator[](size_type n){
                return (this->_array[n]);
            }
            
            const_reference operator[](size_type n) const{
                return (this->_array[n]);
            }
            
            reference       at(size_type n){
                if (n < 0 || this->_size < n)
                    throw std::out_of_range("n is out of range");
            }
            const_reference at(size_type n) const{
                if (n < 0 || this->_size < n)
                    throw std::out_of_range("n is out of range");
            }
            
            reference       front(){
                return (_array[0]);
            }
            
            const_reference front()const{
                return (_array[0]);
            }
            
            reference       back(){
                return (_array[_size]);    
            }
            
            const_reference back()const{
                return (_array[_size]);
            }
             
	        template <class InputIterator>
		    void assign(InputIterator first, InputIterator last){
                size_t new_size = last - first;
                if (new_size > this->_alloc.max_size())
                    throw std::length_error("size requested is greater than max size (vector max_size)\n");
                for (size_t i = 0; i < _size; i++)
                    _alloc.destroy(_array[i]);
                if (new_size < _capacity)
                {
                    _alloc.deallocate(_array, _capacity);
                    _capacity = new_size;
                    _array = _alloc.allocate(_capacity);
                }
                int i = 0;
                for (InputIterator it = first; it != last ; it++)
                    _alloc.construct(_array[i++], *it);
                _size = new_size;                
            }
            
	        void assign(size_type n, const value_type& u){
                if (n > this->_alloc.max_size())
                    throw std::length_error("size requested is greater than max size (vector max_size)\n");
                for (size_t i = 0; i < _size; i++)
                    _alloc.destroy(_array[i]);
                if (n < _capacity)
                {
                    _alloc.deallocate(_array, _capacity);
                    _capacity = n;
                    _array = _alloc.allocate(_capacity);
                }
                for (size_type i; i < n; i++)
                    _alloc.construct(_array[i++], u);
                _size = n;            
            }
            
	        void push_back(const value_type& x){
                if (this->_size + 1 > _capacity)
                {
                    if (_capacity == 0)
                        _reallocateVec(1);
                    else
                        _reallocateVec(_capacity * 2); 
                }
                _alloc.construct(_array[_size++], x);
            }    
	        void pop_back(){
                if (_size > 0)
                    _alloc.detroy(&_array[_size - 1]);
                _size--;
            }
            
            void insert (iterator position, size_type n, const value_type& val)
	        {
                while (n--)
                    position = insert(position, val) + 1;
            }
	   
		    iterator insert(const_iterator position, const value_type& x)
            {
                size_t i = -1;
                size_t j = _size;
                iterator n = begin();
                while ((n != position) && (++i <_size))
                    n++;
                if (_capacity < (_size + 1))
                    reserve(_capacity * 2);
                while (j > i)
                {
                    _array[j] = _array[j-1];
                    j--;
                }
                _array[i] = x;
                _size++;
                return (&_array[i]);
            }
        
            template <class InputIterator>
	        iterator insert(iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0){
                ft::vector<value_type> tmp(first, last);
                for (iterator it = tmp.begin(); it != tmp.end(); it++){
                    position = insert(position, *it) + 1;
                }
            }
        
	        iterator erase(iterator position){
                return (erase(position, position + 1));
            }
            
	        iterator erase(iterator first, iterator last){
                size_type n = first - this->begin();
                size_type len = last- first;
                for (size_type i = n; i < _size && i +len < _size; i++)
                    (*this)[i] = (*this)[i + len];
                for (difference_type i = 0 ; i < last - first ; i++)
                    this->pop_back();
                return (this->begin() + n);
            }
            
            void swap(vector& x){
                allocator_type tmp_alloc;
                pointer tmp_array;
                size_type tmp_size;
                size_type tmp_capacity;

                tmp_alloc = this->_alloc;
                tmp_array = this->_array;
                tmp_size = this->_size;
                tmp_capacity = this->_capacity;
                
                this->_alloc = x._alloc;
                this->_array = x._array;
                this->_size = x._size;
                this->_capacity = x._capacity;
                
                x._alloc = tmp_alloc;
                x._array = tmp_array;
                x._size = tmp_size;
                x._capacity = tmp_capacity;
            }

        private:
            allocator_type  _alloc;
            pointer         _array;
            size_type       _size;
            size_type       _capacity;
            
            void _reallocateVec(size_type newCapacity)
		    {
                pointer tmp = _alloc.allocate(newCapacity);
                size_type size = _size;
                for (size_type i = 0; i < size; i++)			
				    _alloc.construct(&tmp[i], _array[i]);
			    this->~vector();
			    this->_array = tmp;
			    this->_size = size;
			    this->_capacity = newCapacity;
            }
        
    };    
}
