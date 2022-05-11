#include "map.hpp"
#include "pair.hpp"
#include <iostream>
#include <map>
#include "iterators/random_access_iterator.hpp"
#include <sys/time.h>

void display_tree_beg_to_end(NAMESPACE::map<std::string, int> &test, std::string name) {
	NAMESPACE::map<std::string, int>::iterator it_beg = test.begin();
	NAMESPACE::map<std::string, int>::iterator it_end = test.end();
	std::cout << "-----MAP " << name << " of SIZE = " << test.size() << "-----" << std::endl;
	while (it_beg != it_end) {
		std::cout << (it_beg)->first << " : " << it_beg->second << std::endl;
		++it_beg;
	}
}

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
	//test.display_tree();
	std::cout << (++it)->first << std::endl;
	//test.display_tree();
	test.erase((test.find("ee")));
	//test.display_tree();
	test.erase(test.find("10"), test.end());
	it = test.begin();
	//std::cout << it.base() << test.end().base() << std::endl;
	//std::cout << (--it).base() << std::endl;
	//std::cout << (--it).base() << std::endl;
	//test.display_tree();
	test.erase("aa");
	//test.erase((test.find("c")), test.end());
	//test.display_tree();
	test.erase("f");
	/*test.erase("ee");
	test.display_tree();
	test.erase("123");
	test.display_tree();
	test.erase("c");
	test.display_tree();
	test.erase("f");
	test.display_tree();*/
	//test.erase("ee");
	//std::cout<< "ko"<< std::endl;
	test.display_tree(true);
	//test.erase("10");
	//test.display_tree();

}

void test_ft_map_constructeur(NAMESPACE::map<std::string, int> &map) {
	std::cout << "----------- début tests test_ft_map_constructeur + modifiers et element access -----------" << std::endl;
	std::string ee("ee");
	std::string aa("aa");
	NAMESPACE::pair<std::string, int> paire1(ee, 7);
	NAMESPACE::pair<std::string, int> paire2("b", 7);
	NAMESPACE::pair<std::string, int> paire3("d", 7);
	NAMESPACE::pair<std::string, int> paire4("f", 7);
	NAMESPACE::pair<std::string, int> paire5(aa, 45);
	NAMESPACE::pair<std::string, int> paire6("c", 18);
	std::cout << "-----> insert de paires ee, b, d, f, aa, c" <<std::endl;
	map.insert(paire1);
	map.display_tree(true);
	map.insert(paire2);
	map.display_tree(true);
	map.insert(paire3);
	map.display_tree(true);
	map.insert(paire4);
	map.display_tree(true);
	map.insert(paire5);
	map.display_tree(true);
	map.insert(paire6);
	int i = 0;
	std::string a = "a";
	while (++i < 50) {
		//map.display_tree(true);
		map.insert(NAMESPACE::pair<std::string, int>(a.append(1, '.'), i));
	}
	display_tree_beg_to_end(map, "map1");
	std::cout << "-----> accessor[], modification de la valeur de d, de 123, de grp puis de 123" <<std::endl;
	map["d"] = 17;
	display_tree_beg_to_end(map, "map1");
	map["123"];
	display_tree_beg_to_end(map, "map1");
	map["grp"] = 777;
	display_tree_beg_to_end(map, "map1");
	map["123"] = -13;
	display_tree_beg_to_end(map, "map1");
	map.display_tree(true);
	std::cout << "-----> constructeur par copie de map2" <<std::endl;
	NAMESPACE::map<std::string, int> map2(map);
	//display_tree_beg_to_end(map2, "map2");
	//map2.display_tree(true);
	//map2["bef"] = 1007;
	std::cout << "-----> erase par key de d, j et 123" <<std::endl;
	map2.erase("b");
	map2.display_tree(true);	
	map2.erase("j");
	map2.erase("ee");
	map2.erase("123");
	map2.display_tree(true);
	map2.erase("aa");
	map2.display_tree(true);
	map2.erase("bef");
	map2.erase("d");
	map2.erase("grp");
	map2.erase("b");
	map2.erase("f");
	display_tree_beg_to_end(map2, "map2");
	map.display_tree(true);
	map2.display_tree();
	display_tree_beg_to_end(map2, "map2");
	display_tree_beg_to_end(map, "map1");
	std::cout << "-----> constructeur par range de map3 map2.begin() a map2.end()" <<std::endl;
	NAMESPACE::map<std::string, int> map3(map2.begin(),map2.end());
	display_tree_beg_to_end(map3, "map3");
	std::cout << "-----> erase de range de map 3 begin to end, puis insert de range de map 1 dans map 3 begin to --end" <<std::endl;
	//map3.erase(map3.begin(), map3.end());
	//display_tree_beg_to_end(map3, "map3");
	map3.insert(map.begin(), --(map.end()));
	display_tree_beg_to_end(map3, "map3");
	std::cout << "-----> erase de map3 jsq --end par l'incrementation d'un iterateur (root compris)" <<std::endl;
	NAMESPACE::map<std::string, int>::iterator it = map3.begin();
	NAMESPACE::map<std::string, int>::iterator it2 = it;
	while (it != --(map3.end())) {
		it2 = it++;
		map3.erase(it2);	
	}
	display_tree_beg_to_end(map3, "map3");
	std::cout << "-----> insert dans map3 de (aa:45) deux fois et check bool retour" <<std::endl;
	std::cout << map3.insert(paire5).second << std::endl;
	std::cout << map3.insert(paire5).second << std::endl;
	std::cout << "-----> insert dans map3 de (c:18) et retention iterateur retour" <<std::endl;
	it = map3.insert(paire6).first;
	std::cout << it->first << std::endl;
	display_tree_beg_to_end(map3, "map3");
	std::cout << "-----> erase de map1 jsq --end par range (root compris)" <<std::endl;
	map.erase(map.begin(), --(map.end()));
	display_tree_beg_to_end(map, "map1");
}

int main() {
	struct timeval	timebegin;
	struct timeval	timeend;
	gettimeofday(&timebegin, NULL);

	NAMESPACE::map<std::string, int> map;

	test_ft_map_constructeur(map);

	/*std::cout << "ohh " << map.lower_bound("f")->first << std::endl;
	std::cout << "ahh " << map.upper_bound("ee")->first << std::endl;
	ft::pair<NAMESPACE::map<std::string, int>::iterator,NAMESPACE::map<std::string, int>::iterator> range = map.equal_range("cbd");
	std::cout << "range : " << range.first->first << "/" << range.second->first << std::endl;
	std::cout << "TEST FT_MAP_ITERATEURS" << std::endl;
	test_ft_map_iterators(map);*/
	gettimeofday(&timeend, NULL);
	std::cout << (timeend.tv_sec - timebegin.tv_sec)
			* 1000000 + (timeend.tv_usec - timebegin.tv_usec) << " microsecondes" << std::endl;
}