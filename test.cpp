#include "pair.hpp"
#include "Vector.hpp"
#include <iostream>
#include <vector>
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

void test_ft_vector(void) {
	std::cout << "---------------------- Test constructeurs ----------------------" << std::endl;
	std::cout << "-------------> Constructeur par initialisation" << std::endl;
	ft::Vector<int> vec(4, 3);
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
	std::vector<int> vecstd(4,3);
	vecstd[0] = 1;
	vecstd[1] = 2;
	vecstd[3] = 4;
	ft::Vector<int>::iterator ite = vec.end();
	std::cout << *(itb) << std::endl;
	std::cout << *ite << std::endl;
	ft::Vector<int> vec3(itb, ite);
	display_vector(vec3);
	std::cout << "---------------------- Test iterateurs ----------------------" << std::endl;	
	std::cout << "-------------> ft::vector<int>iterator" << std::endl;	
	test_iterator<ft::Vector<int>::iterator>(--itb);
	std::cout << "-------------> ft::vector<int>reverse_iterator" << std::endl;	
	ft::Vector<int>::reverse_iterator rev_itb = vec.rbegin();
	test_iterator<ft::Vector<int>::reverse_iterator>(rev_itb);
	std::cout << "---------------------- Test fonctions membres ----------------------" << std::endl;	

	vec2.resize(2, 2);
	display_vector(vec);
	display_vector(vec2);
}

int main() {
	test_ft_vector();
}