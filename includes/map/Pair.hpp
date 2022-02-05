#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft
{
    template <class T1, class T2>
    struct pair
    {
        typedef T1 first_type;
        typedef T2 second_type;

        T1 first;
        T2 second;


        pair():first(), second(){
        }

        template <class A, class B>
        pair(const pair<A, B> &origin): first(origin.first), second(origin.second){
        }

        pair(const first_type &a, const second_type &b): first(a), second(b){
        }

        const pair & operator=(const pair &other){
            this->first = other.first;
            this->second = other.second;
            return (*this);
        }

        bool operator==(const ft::pair<T1, T2> &cmp) const{
            return(this->first == cmp.first && this->second == cmp.second);
        }

        bool operator!=(const ft::pair<T1, T2> &cmp) const{
            return (cmp.first != this->first && cmp.second != this->second);
        }

        bool operator<(const ft::pair<T1, T2> &cmp) const{
            return (this->first < cmp.first || (!(cmp.first < this->first) && this->second < cmp.second));
        }

        bool operator>(const ft::pair<T1, T2> &cmp) const{
            return (cmp < *this);
        }

        bool operator<=(const ft::pair<T1, T2> &cmp) const{
            return !(cmp < *this);
        }

        bool operator>=(const ft::pair<T1, T2> &cmp) const{
            return !(*this < cmp);
        }

    };
    template <class T1, class T2>
	pair<T1, T2> make_pair(T1 x, T2 y){
		return (pair<T1, T2>(x, y));
	}
};

#endif