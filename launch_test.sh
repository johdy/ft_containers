clang++ -g -D NAMESPACE=ft test.cpp
./a.out > ft_test.txt
clang++ -g -D NAMESPACE=std test.cpp
./a.out > std_test.txt
diff ft_test.txt std_test.txt