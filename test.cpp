#include "pair.hpp"
#include "Vector.hpp"
#include <iostream>

template <class T>
void display_vector(ft::Vector<T> vec) {
	typename ft::Vector<T>::iterator it;
	size_t idx = 0;

	it = vec.begin();
	std::cout << "Vector size : " << vec.size() << std::endl;
	while (it != vec.end()) {
		std::cout << idx++ << ": " << *it << std::endl;
		++it;
	}
}

void test_ft_pair(void) {
	ft::pair<std::string, int> paire1("bonjour", 7);
	ft::pair<std::string, int> paire2 = ft::make_pair<std::string, int>("quoi", 12);

	std::cout << paire1.first << std::endl; 
	std::cout << (paire1 == paire1) << std::endl; 
	std::cout << (paire1 <= paire2) << std::endl; 
	std::cout << (paire1 > paire2) << std::endl; 
	std::cout << (paire1 == paire2) << std::endl; 
}

void test_ft_vector(void) {
	std::cout << "---------------------- Test constructeurs ----------------------" << std::endl;
	std::cout << "-------------> Constructeur par initialisation" << std::endl;
	ft::Vector<int> vec(4, 3);
	display_vector(vec);
	std::cout << "-------------> Constructeur par copie" << std::endl;
	ft::Vector<int> vec2(vec);
	display_vector(vec2);
	std::cout << "-------------> Constructeur par range" << std::endl;
	ft::Vector<int>::iterator it = vec.begin() + 1;
	ft::Vector<int> vec3(it, it + 2);
	vec2.resize(2, 2);
	display_vector(vec);
	display_vector(vec2);
}

int main() {
	test_ft_vector();
}