#include "pair.hpp"
#include "vector.hpp"
#include <iostream>
#include <vector>
template <class T>
void display_vector(NAMESPACE::vector<T> &vec) {
	typename NAMESPACE::vector<T>::iterator it;
	size_t idx = 0;

	it = vec.begin();
	std::cout << "vector size : " << vec.size() << std::endl;
	while (it != vec.end()) {
		std::cout << idx++ << ": " << *it << std::endl;
		++it;
	}
}

void test_ft_pair(void) {
	NAMESPACE::pair<std::string, int> paire1("bonjour", 7);
	NAMESPACE::pair<std::string, int> paire2 = NAMESPACE::make_pair<std::string, int>("quoi", 12);

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
	std::cout << (&(*it.base()) == &(*it_2.base())) << std::endl;
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

void test_ft_vector_constructeurs(NAMESPACE::vector<int> &vec) {
	std::cout << "---------------------- Tests constructeurs ----------------------" << std::endl;
	std::cout << "-------------> Constructeur par initialisation" << std::endl;
	display_vector(vec);
	std::cout << "-------------> Modification du vecteur par l'opérateur []" << std::endl;
	vec[0] = 1;
	vec[1] = 2;
	vec[3] = 4;
	display_vector(vec);
	std::cout << "-------------> Constructeur par copie" << std::endl;
	NAMESPACE::vector<int> vec2(vec);
	display_vector(vec2);
	std::cout << "-------------> Constructeur par range" << std::endl;
	NAMESPACE::vector<int>::iterator itb = vec.begin() + 1;
	NAMESPACE::vector<int>::iterator ite = vec.end();
	NAMESPACE::vector<int> vec3(itb, ite);
	display_vector(vec3);
}

void test_ft_vector_iterateurs(NAMESPACE::vector<int> &vec) {
	std::cout << "---------------------- Tests iterateurs ----------------------" << std::endl;	
	std::cout << "-------------> vector<int>iterator" << std::endl;	
	test_iterator<NAMESPACE::vector<int>::iterator>(vec.begin());
	std::cout << "-------------> vector<int>reverse_iterator" << std::endl;	
	NAMESPACE::vector<int>::reverse_iterator rev_itb = vec.rbegin();
	test_iterator<NAMESPACE::vector<int>::reverse_iterator>(rev_itb);
}

void display_size_max_size_capacity(NAMESPACE::vector<int> &vec, NAMESPACE::vector<int> &vec2) {
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

void test_ft_vector_capacity(NAMESPACE::vector<int> &vec) {
	std::cout << "---------------------- Tests capacity ----------------------" << std::endl;	
	NAMESPACE::vector<int> vec2(vec);
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
	int *adr = &(*vec2.begin());
	std::cout << "-------------> Resize vecteur 2 (3,3)" << std::endl;
	vec2.resize(3, 3);
	std::cout << "L'adresse est-elle la même ? : " << (&(*vec2.begin()) == adr) << std::endl;
	adr = &(*vec2.begin());
	display_vector(vec2);
	display_size_max_size_capacity(vec, vec2);
	std::cout << "-------------> Resize vecteur 2 (5,10)" << std::endl;
	vec2.resize(5, 10);
	std::cout << "L'adresse est-elle la même ? : " << (&(*vec2.begin()) == adr) << std::endl;
	adr = &(*vec2.begin());
	display_vector(vec2);
	display_size_max_size_capacity(vec, vec2);
	std::cout << "-------------> Reserve vecteur 2 (15)" << std::endl;	
	vec2.reserve(15);
	std::cout << "L'adresse est-elle la même ? : " << (&(*vec2.begin()) == adr) << std::endl;
	adr = &(*vec2.begin());
	display_vector(vec2);
	display_size_max_size_capacity(vec, vec2);
	std::cout << "-------------> Reserve vecteur 2 (1)" << std::endl;	
	vec2.reserve(1);
	std::cout << "L'adresse est-elle la même ? : " << (&(*vec2.begin()) == adr) << std::endl;
	adr = &(*vec2.begin());
	display_vector(vec2);
	display_size_max_size_capacity(vec, vec2);
	vec2.clear();
	std::cout << *(vec2.begin() + 1) << std::endl;
}

void test_ft_vector_accesseurs(NAMESPACE::vector<int> &vec) {
	std::cout << "---------------------- Tests accesseurs ----------------------" << std::endl;	
	std::cout << "-------------> vec[0]" << std::endl;	
	std::cout << vec[0] << std::endl;
	std::cout << "-------------> vec[3]" << std::endl;	
	std::cout << vec[3] << std::endl;
	std::cout << "-------------> vec.at(1)" << std::endl;	
	try {std::cout << vec.at(1) << std::endl;}
	catch (std::exception& e) {std::cout << e.what() << std::endl;}
	std::cout << "-------------> vec.at(4)" << std::endl;	
	try {std::cout << vec.at(4) << std::endl;}
	catch (std::exception& e) {std::cout << e.what() << std::endl;}
	std::cout << "-------------> vec.at(-532)" << std::endl;	
	try {std::cout << vec.at(-532) << std::endl;}
	catch (std::exception& e) {std::cout << e.what() << std::endl;}
	vec[0] = 55;
	vec[3] = 243;
	std::cout << "-------------> vec[0] = 55" << std::endl;	
	std::cout << "-------------> vec[3] = 243" << std::endl;	
	std::cout << "-------------> vec.front()" << std::endl;	
	std::cout << vec.front() << std::endl;
	std::cout << "-------------> vec.back()" << std::endl;	
	std::cout << vec.back() << std::endl;
}

void test_ft_vector_modifiers(NAMESPACE::vector<int> &vec) {
	std::cout << "---------------------- Tests modifiers ----------------------" << std::endl;
	NAMESPACE::vector<int> vec2(vec);
	std::cout << "-------------> assign par range (10, 7)" << std::endl;
	vec.assign(10, 7);
	display_vector(vec);
	std::cout << "-------------> assign par fill (vec2.begin(), vec2.end())" << std::endl;
	vec.assign(vec2.begin(), vec2.end());
	display_vector(vec);
	std::cout << "-------------> assign par range (vec2.begin(), vec2.end() - 2)" << std::endl;
	vec.assign(vec2.begin(), vec2.end() - 2);
	display_vector(vec);
	std::cout << "-------------> push_back vec2 : 9, 14, 22, 0, 8" << std::endl;
	vec2.push_back(9);
	vec2.push_back(14);
	vec2.push_back(22);
	vec2.push_back(0);
	vec2.push_back(8);
	display_vector(vec2);
	std::cout << "-------------> pop_back vec2" << std::endl;
	vec2.pop_back();
	display_vector(vec2);
	std::cout << "-------------> erase une seule valeur (vec.begin() + 1)" << std::endl;
	vec.erase(vec.begin());
	display_vector(vec);
	std::cout << "-------------> erase une range (vec2.begin() + 3, vec2.end() - 2)" << std::endl;
	vec2.erase(vec2.begin() + 3, vec2.end() - 2);
	display_vector(vec2);
	NAMESPACE::vector<int>::iterator it = vec.begin();
	vec.swap(vec2);
	std::cout << "-------------> swap vec et vec2" << std::endl;
	std::cout << "----> vec" << std::endl;
	display_vector(vec);
	std::cout << "----> vec2" << std::endl;
	display_vector(vec2);
	std::cout << "----> valeur de l'itérateur begin de l'ancien vec" << std::endl;
	std::cout << *it << std::endl;
	std::cout << "-------------> insert d'élément simple vec.end() - 1 de 31 à 36, avec capacité vecteur avant et après insertion" << std::endl;
	std::cout << "capacité : " << vec.capacity() << std::endl;
	vec.insert(vec.end() - 1, 31);
	vec.insert(vec.end() - 1, 32);
	vec.insert(vec.end() - 1, 33);
	display_vector(vec);
	std::cout << "capacité : " << vec.capacity() << std::endl;
	vec.insert(vec.end() - 1, 34);
	vec.insert(vec.end() - 1, 35);
	it = vec.insert(vec.end() - 1, 36);	
	display_vector(vec);
	std::cout << *it << std::endl;
	std::cout << "capacité : " << vec.capacity() << std::endl;
	std::cout << "-------------> insert de remplissage" << std::endl;
	std::cout << "----> vec.insert(vec.begin() + 3, 3, 101)" << std::endl;
	vec.insert(vec.begin() + 3, 3, 101);
	display_vector(vec);
	std::cout << "capacité : " << vec.capacity() << std::endl;
	std::cout << "----> vec.insert(vec.begin(), 8, 99)" << std::endl;
	vec.insert(vec.begin(), 8, 99);
	display_vector(vec);
	std::cout << "capacité : " << vec.capacity() << std::endl;
	std::cout << "----> vec.insert(vec.end(), 2, 100)" << std::endl;
	vec.insert(vec.end(), 2, 100);
	display_vector(vec);
	std::cout << "capacité : " << vec.capacity() << std::endl;
	std::cout << "----> vec.insert(vec.end() - 1, 3, 55)" << std::endl;
	vec.insert(vec.end() - 1, 3, 55);
	display_vector(vec);
	std::cout << "capacité : " << vec.capacity() << std::endl;
	std::cout << "-------------> insert de ranges" << std::endl;
	NAMESPACE::vector<int> vec3(vec);
	std::cout << "----> vector<int> vec3(vec)" << std::endl;
	display_vector(vec3);
	std::cout << "----> vec.insert(vec.begin() + 10, vec3.begin(), vec3.end() - 1)" << std::endl;
	vec.insert(vec.begin() + 10, vec3.begin(), vec3.end() - 1);
	display_vector(vec);
	std::cout << "capacité : " << vec.capacity() << std::endl;
	std::cout << "----> vec2.insert(vec2.begin(), vec.end() - 1, vec.end())" << std::endl;
	vec2.insert(vec2.begin(), vec.end() - 1, vec.end());
	display_vector(vec2);
	std::cout << "capacité : " << vec.capacity() << std::endl;
	std::cout << "----> vec2.insert(vec2.begin(), vec.begin(), vec.begin())" << std::endl;
	vec2.insert(vec2.begin(), vec.begin(), vec.begin());
	display_vector(vec2);
	std::cout << "capacité : " << vec.capacity() << std::endl;
}

void test_ft_vector_non_member_function_overloads(NAMESPACE::vector<int> &vec) {
	NAMESPACE::vector<int> vec2(vec);
	NAMESPACE::vector<int> vec3(vec);

	std::cout << "---------------------- Tests modifiers ----------------------" << std::endl;
	std::cout << "-------------> vec2 et vec3 copies de vec, on resize vec3 à 5" << std::endl;
	vec3.resize(5);
	std::cout << "----> (vec3 < vec)" << std::endl;
	std::cout << (vec3 < vec) << std::endl;
	std::cout << "----> (vec2 == vec)" << std::endl;
	std::cout << (vec2 == vec) << std::endl;
	std::cout << "----> (vec3 != vec)" << std::endl;
	std::cout << (vec3 == vec) << std::endl;
	std::cout << "-------------> vec2[1] = -12" << std::endl;
	vec2[1] = -12;
	std::cout << "----> (vec >= vec2)" << std::endl;
	std::cout << (vec >= vec2) << std::endl;
	swap(vec, vec2);
	std::cout << "-------------> swap(vec, vec2)" << std::endl;
	std::cout << "----> (vec <= vec3)" << std::endl;
	std::cout << (vec <= vec3) << std::endl;
	std::cout << "----> (vec3 > vec)" << std::endl;
	std::cout << (vec3 > vec) << std::endl;
}

int main() {
	NAMESPACE::vector<int> vec(4, 3);
	/*test_ft_vector_constructeurs(vec);
	test_ft_vector_iterateurs(vec);
	test_ft_vector_capacity(vec);
	test_ft_vector_accesseurs(vec);*/
	test_ft_vector_modifiers(vec);
	test_ft_vector_non_member_function_overloads(vec);
}