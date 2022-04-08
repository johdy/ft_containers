#include "map.hpp"
#include "pair.hpp"
#include <iostream>
#include "iterators.hpp"

int main() {
	ft::BST<ft::pair<std::string, int> > test;

	NAMESPACE::pair<std::string, int> paire1("bonjour", 7);
	NAMESPACE::pair<std::string, int> paire2("banjour", 7);
	NAMESPACE::pair<std::string, int> paire3("bbnjour", 7);
	NAMESPACE::pair<std::string, int> paire4("dsqjnur", 7);
	NAMESPACE::pair<std::string, int> paire5("azert", 7);
	NAMESPACE::pair<std::string, int> paire6("baojour", 7);
	test.add(paire1);
	test.add(paire2);
	test.add(paire3);
	test.add(paire4);
	test.add(paire5);
	test.add(paire6);
	test.display_tree();

	ft::bst_iterator<ft::pair<std::string, int> > it;
	it = test.begin();
	std::cout << it->_value.first << std::endl;
	--it;
	--it;
	--it;
	++it;
	++it;
	std::cout << it->_value.first << std::endl;
}