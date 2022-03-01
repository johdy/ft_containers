#include "pair.hpp"
#include "Vector.hpp"
#include <iostream>

template <class T>
void display_vector(ft::Vector<T> vec) {
	T* it;

	it = vec.begin();
	while (it != vec.end()) {
		std::cout << *it << std::endl;
		++it;
	}
}

int main() {
	ft::pair<std::string, int> paire1("bonjour", 7);
	ft::pair<std::string, int> paire2 = ft::make_pair<std::string, int>("quoi", 12);



	std::cout << paire1.first << std::endl; 
	std::cout << (paire1 == paire1) << std::endl; 
	std::cout << (paire1 <= paire2) << std::endl; 
	std::cout << (paire1 > paire2) << std::endl; 
	std::cout << (paire1 == paire2) << std::endl; 

	ft::Vector<int> vec(4,3);
	std::cout << paire1.first << std::endl;
	ft::Vector<int> vec2(vec);
	vec2.resize(2, 2);
	display_vector(vec);
	std::cout << paire1.first << std::endl;
	display_vector(vec2);


}