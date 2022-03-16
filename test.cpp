#include "pair.hpp"
#include "Vector.hpp"
#include <iostream>
#include <vector>
template <class T>
void display_vector(ft::Vector<T> &vec) {
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

template <class Iter>
void test_iterator(Iter it) {
	std::cout << "------> déréférencement" << std::endl;	
	std::cout << *it << std::endl;
	std::cout << "------> pré et post incrémentation" << std::endl;	
	++it;
	std::cout << *it << std::endl;
	it++;
	std::cout << *it << std::endl;
	std::cout << "------> pré et post décrémentation" << std::endl;	
	--it;
	std::cout << *it << std::endl;
	it--;
	std::cout << *it << std::endl;

	std::cout << "------> construction d'un itérateur-copie par instanciation" << std::endl;	
	Iter it_2 = it;
	std::cout << *it_2 << std::endl;
	std::cout << "------> incrémentation de la copie et comparaison des bases des 2 itérateurs" << std::endl;	
	it_2++;
	std::cout << it.base() << std::endl;
	std::cout << it_2.base() << std::endl;
	std::cout << "------> it +=2 et it -=2" << std::endl;	
	it_2 += 2;
	std::cout << *it_2 << std::endl;
	it_2 -= 2;
	std::cout << *it_2 << std::endl;
	std::cout << "------> tests booleens == ; != ; <= ; < ; >= ; > " << std::endl;	
	std::cout << (it == it_2) << std::endl;
	std::cout << (it != it_2) << std::endl;
	std::cout << (it <= it_2) << std::endl;
	std::cout << (it < it_2) << std::endl;
	std::cout << (it >= it_2) << std::endl;
	std::cout << (it > it_2) << std::endl;
	std::cout << "------> valeur des deux itérateurs" << std::endl;	
	std::cout << *(it) << std::endl;
	std::cout << *(it_2) << std::endl;
	std::cout << "------> soustraction des itérateurs pour obtenir leur distance" << std::endl;
	std::cout << (it_2 - it) << std::endl;
	std::cout << "------> addition d'un itérateur à 2" << std::endl;	
	std::cout << *(2 + it) << std::endl;

}

void test_ft_vector_constructeurs(ft::Vector<int> &vec) {
	std::cout << "---------------------- Tests constructeurs ----------------------" << std::endl;
	std::cout << "-------------> Constructeur par initialisation" << std::endl;
	display_vector(vec);
	std::cout << "-------------> Modification du vecteur par l'opérateur []" << std::endl;
	vec[0] = 1;
	vec[1] = 2;
	vec[3] = 4;
	display_vector(vec);
	std::cout << "-------------> Constructeur par copie" << std::endl;
	ft::Vector<int> vec2(vec);
	display_vector(vec2);
	std::cout << "-------------> Constructeur par range" << std::endl;
	ft::Vector<int>::iterator itb = vec.begin() + 1;
	ft::Vector<int>::iterator ite = vec.end();
	ft::Vector<int> vec3(itb, ite);
	display_vector(vec3);
}

void test_ft_vector_iterateurs(ft::Vector<int> &vec) {
	std::cout << "---------------------- Tests iterateurs ----------------------" << std::endl;	
	std::cout << "-------------> ft::vector<int>iterator" << std::endl;	
	test_iterator<ft::Vector<int>::iterator>(vec.begin());
	std::cout << "-------------> ft::vector<int>reverse_iterator" << std::endl;	
	ft::Vector<int>::reverse_iterator rev_itb = vec.rbegin();
	test_iterator<ft::Vector<int>::reverse_iterator>(rev_itb);
}

void display_size_max_size_capacity(ft::Vector<int> &vec, ft::Vector<int> &vec2) {
	std::cout << "-------------> size des vecteur 1 et 2" << std::endl;
	std::cout << vec.size() << std::endl;
	std::cout << vec2.size() << std::endl;
	std::cout << "-------------> max_size des vecteur 1 et 2" << std::endl;
	std::cout << vec.max_size() << std::endl;
	std::cout << vec2.max_size() << std::endl;
	std::cout << "-------------> capacity des vecteur 1 et 2" << std::endl;
	std::cout << vec.capacity() << std::endl;
	std::cout << vec2.capacity() << std::endl;
}

void test_ft_vector_capacity(ft::Vector<int> &vec) {
	std::cout << "---------------------- Tests capacity ----------------------" << std::endl;	
	ft::Vector<int> vec2(vec);
	vec2.resize(2, 2);
	std::cout << "-------------> Resize vecteur 2 (2,2)" << std::endl;
	display_vector(vec2);
	display_size_max_size_capacity(vec, vec2);
	std::cout << "-------------> Resize vecteur 2 (0,0)" << std::endl;
	vec2.resize(0, 0);
	display_vector(vec2);
	display_size_max_size_capacity(vec, vec2);
	std::cout << "vecteur 1 vide ? " << vec.empty() << std::endl;
	std::cout << "vecteur 2 vide ? " << vec2.empty() << std::endl;
	std::cout << "adresse array sous-jacent vecteur 2 : " << vec2.begin() << std::endl;
	std::cout << "-------------> Resize vecteur 2 (3,3)" << std::endl;
	vec2.resize(3, 3);
	std::cout << "adresse array sous-jacent vecteur 2 : " << vec2.begin() << std::endl;
	display_vector(vec2);
	display_size_max_size_capacity(vec, vec2);
	std::cout << "-------------> Resize vecteur 2 (5,10)" << std::endl;
	vec2.resize(5, 10);
	std::cout << "adresse array sous-jacent vecteur 2 : " << vec2.begin() << std::endl;
	display_vector(vec2);
	display_size_max_size_capacity(vec, vec2);
	std::cout << "-------------> Reserve vecteur 2 (15)" << std::endl;	
	vec2.reserve(15);
	std::cout << "adresse array sous-jacent vecteur 2 : " << vec2.begin() << std::endl;
	display_vector(vec2);
	display_size_max_size_capacity(vec, vec2);
	std::cout << "-------------> Reserve vecteur 2 (1)" << std::endl;	
	vec2.reserve(1);
	std::cout << "adresse array sous-jacent vecteur 2 : " << vec2.begin() << std::endl;
	display_vector(vec2);
	display_size_max_size_capacity(vec, vec2);
	vec2.clear();
	std::cout << *(vec2.begin() + 1) << std::endl;
}

int main() {
	ft::Vector<int> vec(4, 3);
	test_ft_vector_constructeurs(vec);
	test_ft_vector_iterateurs(vec);
	test_ft_vector_capacity(vec);
}