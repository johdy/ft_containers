clang++ -g -std=c++98 -D NAMESPACE=ft test_map.cpp
./a.out > ft_test.txt
clang++ -g -std=c++98 -D NAMESPACE=std test_map.cpp
./a.out > std_test.txt
diff ft_test.txt std_test.txt
