#include "map.hpp"
#include "pair.hpp"
#include <iostream>
#include "iterators/random_access_iterator.hpp"

int main() {
	ft::map<std::string, int> test;

	std::string ee("ee");
	NAMESPACE::pair<std::string, int> paire1(ee, 7);
	NAMESPACE::pair<std::string, int> paire2("b", 7);
	NAMESPACE::pair<std::string, int> paire3("d", 7);
	NAMESPACE::pair<std::string, int> paire4("f", 7);
	NAMESPACE::pair<std::string, int> paire5("a", 7);
	NAMESPACE::pair<std::string, int> paire6("c", 7);
	test.add(paire1);
	test.add(paire2);
	test.add(paire3);
	test.add(paire4);
	test.add(paire5);
	test.add(paire6);
	test.display_tree();

	ft::map<std::string, int>::iterator it;
	it = test.begin();
	std::cout << it->_value.first << std::endl;
	--it;
	--it;
	--it;
	--it;
	std::cout <<  it->_value.first << std::endl;
	++it;
	std::cout << it->_value.first << std::endl;
	++it;
	std::cout << it->_value.first << std::endl;
	++it;
	std::cout <<it->_value.first << std::endl;
	++it;
	std::cout << it->_value.first << std::endl;
	++it;
	std::cout << it->_value.first << std::endl;
	++it;
	std::cout << it->_value.first << std::endl;
	++it;
	std::cout << it->_value.first << std::endl;
	++it;
	std::cout << it->_value.first << std::endl;
	++it;
	std::cout << it->_value.first << std::endl;
	--it;
	std::cout << it->_value.first << std::endl;
	--it;
	std::cout << it->_value.first << std::endl;
	--it;
	std::cout << it->_value.first << std::endl;
	--it;
	std::cout << it->_value.first << std::endl;
	--it;
	std::cout << it->_value.first << std::endl;
	--it;
	std::cout << it->_value.first << std::endl;
	--it;
	std::cout << it->_value.first << std::endl;
	--it;
	std::cout << it->_value.first << std::endl;
	--it;
	std::cout << it->_value.first << std::endl;
	--it;
	std::cout << it->_value.first << std::endl;
}