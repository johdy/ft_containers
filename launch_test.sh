clang++ -g -D NAMESPACE=ft test_map.cpp -Iiterators -I.
./a.out > ft_test.txt
clang++ -g -D NAMESPACE=std test_map.cpp -Iiterators -I.
./a.out > std_test.txt
diff ft_test.txt std_test.txt