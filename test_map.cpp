#include "map.hpp"
#include "pair.hpp"
#include <iostream>
#include <map>
#include "iterators/random_access_iterator.hpp"
#include <sys/time.h>

void display_tree_beg_to_end(NAMESPACE::map<std::string, int> &test, std::string name) {
	NAMESPACE::map<std::string, int>::iterator it_beg = test.begin();
	NAMESPACE::map<std::string, int>::iterator it_end = test.end();
	size_t size = test.size();
	std::cout << "---MAP " << name << " of SIZE = " << size << "---" << std::endl;
	while (size != 0 && it_beg != it_end) {
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
	//test.display_tree(true);
	//test.erase("10");
	//test.display_tree();


}

void test_operations(NAMESPACE::map<std::string, int> map) {
	std::cout << "-/-/-/-/-/-/-/-/-/- Test operations-/-/-/-/-/-/-/-/-/-" << std::endl;
	std::cout << "-----> find dans map 15007 de azerty, a............, non_existant, zz, zzzz" <<std::endl;
	int i = 0;
	std::string a = "a";

	while (++i < 15000) {
		map.insert(NAMESPACE::pair<std::string, int>(a.append(1, '.'), i));
	}
	std::cout << map.find("azerty")->second << std::endl;
	std::cout << map.find("a............")->second << std::endl;
	if (map.find("non_existant") == map.end())
		std::cout << "non_existant n'existe pas dans la map" << std::endl;
	std::cout << map.find("zz")->second << std::endl;
	if (map.find("zzzz") == map.end())
		std::cout << "zzzz n'existe pas dans la map" << std::endl;
	std::cout << "-----> Memes tests avec count()" <<std::endl;
	std::cout << map.count("azerty") << std::endl;
	std::cout << map.count("a............")<< std::endl;
	std::cout << map.count("non_existant") << std::endl;
	std::cout << map.count("zz") << std::endl;
	std::cout << map.count("zzzz") << std::endl;
	NAMESPACE::map<std::string, int>::iterator it;
	std::cout << "-----> Memes tests avec equal_range() et affichage lower et upper bound. affichage ensuite lower_bound() et upper_bound()" <<std::endl;
	NAMESPACE::pair<NAMESPACE::map<std::string, int>::iterator, NAMESPACE::map<std::string, int>::iterator > paire_it;
	paire_it = map.equal_range("azerty");
	std::cout << paire_it.first->first << "/" << paire_it.second->first << std::endl;
	std::cout << map.lower_bound("azerty")->first << "/" << map.upper_bound("azerty")->first << std::endl;
	paire_it = map.equal_range("a............");
	std::cout << paire_it.first->second << "/" << paire_it.second->second << std::endl;
	std::cout << map.lower_bound("a............")->second << "/" << map.upper_bound("a............")->second << std::endl;
	paire_it = map.equal_range("non_existant");
	std::cout << paire_it.first->first << "/" << paire_it.second->first << std::endl;
	std::cout << map.lower_bound("non_existant")->first << "/" << map.upper_bound("non_existant")->first << std::endl;
	paire_it = map.equal_range("zz");
	std::cout << paire_it.first->first << "/ upper_bound == end() ? " << (paire_it.second == map.end()) << std::endl;
	std::cout << map.lower_bound("zz")->first << "/ upper_bound == end() ? " << (map.upper_bound("zz") == map.end()) << std::endl;
	paire_it = map.equal_range("zzzz");
	std::cout << "lower_bound == end() ? " << (paire_it.first == map.end())  << "/ upper_bound == end() ? " << (paire_it.second == map.end()) << std::endl;
	std::cout << "lower_bound == end() ? " << (map.lower_bound("zzzz") == map.end())  << "/ upper_bound == end() ? " << (map.upper_bound("zzzz") == map.end()) << std::endl;
}

void test_capacity_and_observers(NAMESPACE::map<std::string, int> map) {
	std::cout << "-/-/-/-/-/-/-/-/-/- Test capacity and observers -/-/-/-/-/-/-/-/-/-" << std::endl;
	std::cout << "-----> Map 1 est -elle vide ? Puis affichage size" <<std::endl;
	std::cout << map.empty() << "/" << map.size() << std::endl;
	std::cout << "-----> Test comparateur entre first et --end puis first et first, key_compare puis value_compare" <<std::endl;
	NAMESPACE::map<std::string, int>::key_compare compare = map.key_comp();
	NAMESPACE::map<std::string, int>::value_compare vcompare = map.value_comp();
	std::cout << compare(map.begin()->first, (--(map.end()))->first) <<std::endl;
	std::cout << compare((--(map.end()))->first, (--(map.end()))->first) <<std::endl;
	std::cout << map.value_comp()(*(map.begin()), *(--(map.end()))) << std::endl;
	std::cout << map.value_comp()(*(map.begin()), *(map.begin())) << std::endl;
	std::cout << "-----> Clear puis affichage vide? et size" <<std::endl;
	map.clear();
	std::cout << map.empty() << "/" << map.size() << std::endl;
	std::cout << "-----> Affichage max_size" << std::endl;
	std::cout << map.max_size() << std::endl;
}

void test_ft_modifiers(NAMESPACE::map<std::string, int> &map) {
	std::cout << "-/-/-/-/-/-/-/-/-/- Suite des tests modifiers -/-/-/-/-/-/-/-/-/-" << std::endl;
	std::cout << "-----> construction de map 2 et swap avec map 1" <<std::endl;
	NAMESPACE::map<std::string, int> map2(map);
	NAMESPACE::map<std::string, int>::iterator it;
	it = map.begin();
	map2["zippo"] = 33;
	map2.erase("b");
	map2["hollow"] = 91;

	display_tree_beg_to_end(map, "map 1");
	display_tree_beg_to_end(map2, "map 2");
	map2.swap(map);
	display_tree_beg_to_end(map, "map 1");
	display_tree_beg_to_end(map2, "map 2");
	std::cout << "-----> iteration de l'iterateur construit à map.begin() avant le swap" << std::endl;
	while (it != map2.end())
		std::cout << (it++)->first << std::endl;
	std::cout << "-----> clear de map 1 et reswap" <<std::endl;
	map.clear();
	map.swap(map2);
	display_tree_beg_to_end(map, "map 1");
	display_tree_beg_to_end(map2, "map 2");
	std::cout << "-----> reclear de map 2" <<std::endl;
	map2.clear();
	display_tree_beg_to_end(map2, "map 2");
	std::cout << "-----> erase dans deux maps de 'bonjour' puis insert dans 1 de c :: 17 avec retention iterator de retour" << std::endl;
	NAMESPACE::pair<std::string, int> paire("c", 17);
	map.erase("bonjour");
	map2.erase("bonjour");
	it = map.insert(paire).first;
	std::cout << "iterateur retour pointe sur : " << it->first << std::endl;
	display_tree_beg_to_end(map, "map 1");
	map.insert(map.begin(), map.end());
	std::cout << "-----> insert avec hint" << std::endl;
	NAMESPACE::pair<std::string, int> paire2("bol", 41);
	NAMESPACE::pair<std::string, int> paire3("azerty", 6);
	NAMESPACE::pair<std::string, int> paire4("h", 10);
	NAMESPACE::pair<std::string, int> paire5("zz", 5);
	map.insert(it, paire2);
	map.insert(it, paire3);
	map.insert(map.end(), paire4);
	map.insert(map.begin(), paire5);
	display_tree_beg_to_end(map, "map 1");

}

void test_ft_map_modifiers_big_time(NAMESPACE::map<std::string, int> &map) {
	int i = 0;
	std::string a = "a";

	while (++i < 15000) {
		map.insert(NAMESPACE::pair<std::string, int>(a.append(1, '.'), i));
	}
	std::cout << "-----> insert de 15000 paires de a. a a................" <<std::endl;
	//display_tree_beg_to_end(map, "map1");
	map.erase(map.begin(), map.end());
	display_tree_beg_to_end(map, "map1");
}

void test_ft_map_constructeur(NAMESPACE::map<std::string, int> &map) {
	std::cout << "-/-/-/-/-/-/-/-/-/- début tests test_ft_map_constructeur + element access et modifiers part 1 -/-/-/-/-/-/-/-/-/-" << std::endl;
	std::string ee("ee");
	std::string aa("aa");
	NAMESPACE::pair<std::string, int> paire1(ee, 7);
	NAMESPACE::pair<std::string, int> paire2("b", 7);
	NAMESPACE::pair<std::string, int> paire3("d", 7);
	NAMESPACE::pair<std::string, int> paire4("f", 7);
	NAMESPACE::pair<std::string, int> paire5(aa, 45);
	std::cout << "-----> insert de paires ee, b, d, f, aa, c" <<std::endl;
	map.insert(paire1);
	map.insert(paire2);
	map.insert(paire3);
	map.insert(paire4);
	map.insert(paire5);
	map.insert(NAMESPACE::make_pair<std::string, int>("c", 18));
	display_tree_beg_to_end(map, "map1");
	std::cout << "-----> accessor[], modification de la valeur de d, de 123, de grp puis de 123" <<std::endl;
	map["d"] = 17;
	map["123"];
	map["grp"] = 777;
	map["123"] = -13;
	display_tree_beg_to_end(map, "map1");
	std::cout << "-----> constructeur par copie de map2" <<std::endl;
	NAMESPACE::map<std::string, int> map2(map);
	display_tree_beg_to_end(map2, "map2");
	std::cout << "-----> erase par key de d, j et 123" <<std::endl;
	map2.erase("b");
	map2.erase("j");
	map2.erase("123");
	display_tree_beg_to_end(map2, "map2");
	display_tree_beg_to_end(map, "map1");
	std::cout << "-----> constructeur par range de map3 map2.begin() a map2.end()" <<std::endl;
	NAMESPACE::map<std::string, int> map3(map2.begin(), --(map2.end()));
	display_tree_beg_to_end(map3, "map3");
	std::cout << "-----> erase de range de map 3 begin to end, puis insert de range de map 1 dans map 3 begin to --end" <<std::endl;
	map3.erase(map3.begin(), map3.end());
	display_tree_beg_to_end(map3, "map3");
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
	it = map3.insert(NAMESPACE::make_pair<std::string, int>("c", 18)).first;
	std::cout << it->first << std::endl;
	display_tree_beg_to_end(map3, "map3");
	std::cout << "-----> erase de map1 jsq end par range (root compris)" <<std::endl;
	map.erase(map.begin(), (map.end()));
	display_tree_beg_to_end(map, "map1");

	std::cout << "-----> Construction map<string, map> et iteration pour affichage, avec map nb 2 = map nb 3" <<std::endl;
	NAMESPACE::map<std::string, int> map_const(map);
	NAMESPACE::map<std::string, NAMESPACE::map<std::string, int> > map_inception;
	NAMESPACE::pair<std::string, NAMESPACE::map<std::string, int> > paire_map("Map nb 1", map);
	NAMESPACE::pair<std::string, NAMESPACE::map<std::string, int> > paire_map2("Map nb 2", map2);
	NAMESPACE::pair<std::string, NAMESPACE::map<std::string, int> > paire_map3("Map nb 3", map2);
	map_inception.insert(paire_map);
	map_inception.insert(paire_map2);
	map_inception.insert(paire_map3);
	NAMESPACE::map<std::string, NAMESPACE::map<std::string, int> >::iterator it_maps = map_inception.begin();
	while (it_maps != map_inception.end()) {
		display_tree_beg_to_end(it_maps->second, it_maps->first);
		++it_maps;
	}
	map_inception["Map nb 3"] = map3;
	std::cout << "-----> modification 'Map nb 3' par accesseur []" <<std::endl;
	it_maps = map_inception.begin();
	while (it_maps != map_inception.end()) {
		display_tree_beg_to_end(it_maps->second, it_maps->first);
		++it_maps;
	}
	map = map3;
}

void test_const(const NAMESPACE::map<std::string, int> &map) {
	NAMESPACE::pair<std::string, int> paire3("d", 7);
	NAMESPACE::map<std::string, int>::const_iterator cit = map.begin();
	//while (cit != map.end())
		std::cout << (cit)->first << std::endl;
}

int main() {
	struct timeval	timebegin;
	struct timeval	timeend;
	gettimeofday(&timebegin, NULL);

	NAMESPACE::map<std::string, int> map;

	test_ft_map_constructeur(map);
	test_ft_modifiers(map);
	test_capacity_and_observers(map);
	test_operations(map);
	NAMESPACE::map<std::string, int>::reverse_iterator rit = map.rbegin();

	std::cout << rit->first << std::endl;
	map["h"] = 17;
	map["hh"] = 17;
	map["hhhh"] = 17;
	map["hhhhhh"] = 17;
	map["123"];
	map["grp"] = 777;
	map["123"] = -13;
	rit = --(map.rend());

	std::cout << rit->first << std::endl;
	test_const(map);

	//display_tree_beg_to_end(map, "map1");
	//test_ft_map_modifiers_big_time(map);
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

