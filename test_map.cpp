#include "map.hpp"
#include "pair.hpp"
#include <iostream>
#include <map>
#include "iterators/random_access_iterator.hpp"
#include <sys/time.h>

void test_ft_map_iterators(NAMESPACE::map<std::string, int> &test) {
	NAMESPACE::map<std::string, int>::iterator it;
	it = test.begin();
	std::cout << it->first << std::endl;
	std::cout <<  it->first << std::endl;
	++it;
	std::cout << it->first << std::endl;
	++it;
	std::cout << it->first << std::endl;
	++it;
	std::cout <<it->first << std::endl;
	++it;
	std::cout << it->first << std::endl;
	++it;
	--it;
	std::cout << it->first << std::endl;
	--it;
	std::cout << it->first << std::endl;
	--it;
	std::cout << it->first << std::endl;
	--it;
	std::cout << it->first << std::endl;
	NAMESPACE::pair<std::string, int> paire1("10", 5);
	NAMESPACE::pair<std::string, int> paire2("11", 5);
	test.insert(paire1);
	test.insert(it, paire2);
	test.display_tree();
	std::cout << (++it)->first << std::endl;
	test.display_tree();
	test.erase((test.find("ee")));
	test.display_tree();
	//test.erase(++(test.begin()), --test.end());
	//test.erase((test.find("c")), test.end());
	test.erase("b");
	test.display_tree();
	//test.erase("ee");
	test.erase("123");
	test.erase("c");
	test.erase("f");
	test.display_tree();
	test.erase("ee");
	std::cout<< "ko"<< std::endl;
	test.display_tree();

}

void test_ft_map_constructeur(NAMESPACE::map<std::string, int> &map) {
	std::cout << "----------- début tests test_ft_map_constructeur -------------" << std::endl;
	NAMESPACE::map<std::string, int> map2(map);
	std::cout << "-----> constructeur par range" <<std::endl;
	NAMESPACE::map<std::string, int> map3(map2.begin(),--map2.end());
	std::cout << "CA DEVFRAIT ETRE f : " << (--(map2.end()))->first << std::endl;
	map3.display_tree();
	//map.display_tree();
}

int main() {
	struct timeval	timebegin;
	struct timeval	timeend;
	gettimeofday(&timebegin, NULL);

	NAMESPACE::map<std::string, int> map;


	std::string ee("ee");
	std::string aa("aa");
	NAMESPACE::pair<std::string, int> paire1(ee, 7);
	NAMESPACE::pair<std::string, int> paire2("b", 7);
	NAMESPACE::pair<std::string, int> paire3("d", 7);
	NAMESPACE::pair<std::string, int> paire4("f", 7);
	NAMESPACE::pair<std::string, int> paire5(aa, 7);
	NAMESPACE::pair<std::string, int> paire6("c", 7);
	map.insert(paire1);
	map.insert(paire2);
	map.insert(paire3);
	map.insert(paire4);
	map.insert(paire5);
	map.insert(paire6);
	//map.display_tree();
	map["d"] = 17;
	map["123"];
	std::cout << "ohh " << map.lower_bound("f")->first << std::endl;
	std::cout << "ahh " << map.upper_bound("ee")->first << std::endl;
	ft::pair<NAMESPACE::map<std::string, int>::iterator,NAMESPACE::map<std::string, int>::iterator> range = map.equal_range("cbd");
	std::cout << "range : " << range.first->first << "/" << range.second->first << std::endl;
	test_ft_map_constructeur(map);
	std::cout << "TEST FT_MAP_ITERATEURS" << std::endl;
	test_ft_map_iterators(map);
	gettimeofday(&timeend, NULL);
	std::cout << (timeend.tv_sec - timebegin.tv_sec)
			* 1000000 + (timeend.tv_usec - timebegin.tv_usec) << " microsecondes" << std::endl;
}