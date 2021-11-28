/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehaenec <jehaenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 20:43:10 by jehaenec          #+#    #+#             */
/*   Updated: 2021/11/26 03:13:47 by jehaenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Iterator.hpp"
#include "RandomAccess_iterator.hpp"

namespace ft
{
    template<class T, class Allocator = std::allocator<T>>
    class vector
    {
        public:
            typedef Allocator                                                       allocator_type;
            typedef T                                                               value_type;
            typedef typename allocator_type::size_type                              size_type;
            typedef typename allocator_type::reference                              reference;
            typedef typename allocator_type::const_reference                        const_reference;
            typedef typename allocator_type::pointer                                pointer;
            typedef typename allocator_type::const_pointer                          const_pointer;
            typedef typename random_access_iterator<value_type>                     iterator;
            typedef typename random_access_iterator<const value_type, value_type>   const_iterator;
            typedef typename reverse_iterator<iterator>                             reverse_iterator;
            typedef typename reverse_iterator<const_iterator>                       const_reverse_iterator;
       
            explicit vector(const allocator_type &alloc = allocator_type()): _alloc(alloc), _size(0), _capacity(0){
                _array = _alloc.allocate(_capacity);
            }

            explicit vector(size_type n, value_type &value_type = value_type(), const allocator_type &alloc = allocator_type()):_size(0), _capacity(n), _alloc(alloc)
            {
                _array = _alloc.allocate(_capacity);
                for (size_type i = 0; i < _size; i++){
                    _alloc.construct(&_array[i], value_type);
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
                    for (size_type i = _size; i < n; i++;)
                        push_back(val);
                    this->_size = n;
                }
                else
                {
                    reserve(n);
                    for (size_type i = _size; i < n; i++;)
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
                
            }
	        void assign(size_type n, const value_type& u){
                
            }
	void push_back(const value_type& x);
	void pop_back();
	iterator insert(const_iterator position, const value_type& x);
	template <class InputIterator>
		void insert (iterator position, size_type n, const value_type& val);
	iterator insert(iterator position, InputIterator first, InputIterator last);
	iterator erase(iterator position);
	iterator erase(iterator first, iterator last);
    void swap(vector& x);
    void clear() ;


        private:
            allocator_type  _alloc;
            pointer         _array;
            size_type       _size;
            size_type       _capacity;
            
            void _reallocateVec(size_type newCapacity)
		    {}
        
    };    
}
