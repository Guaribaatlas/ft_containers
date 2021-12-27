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

        template <classe T1, class T2>
        pair(const pair<T1,T2> &origin): first(origin.first), second(origin.second){
        }

        pair(const first_type &a, const second_type &b): first(a), second(b){
        }

        const pair & operator=(const pair &other){
            this->first = other.first;
            this->second = other.second;
            return (*this);
        }

        bool operator==(const ft::pair<T1, T2> &cmp) const{
            return(cmp.first == this->first && cmp.second == this->second);
        }

        bool operator!=(const ft::pair<T1, T2> &cmp) const{
            return (cmp.first != this.first && cmp.second != this->second);
        }

        bool operator<(const ft::pair<T1, T2> &cmp) const{
            return (cmp)
        }

        bool operator>(const ft::pair<T1, T2> &cmp) const{

        }

        bool operator<=(const ft::pair<T1, T2> &cmp) const{

        }

        bool operator>=(const ft::pair<T1, T2> &cmp) const{

        }

    };
};

#endif