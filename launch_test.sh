clang++ -g -std=c++98 -D NAMESPACE=ft test.cpp -Iiterators -I.
./a.out > ft_test.txt
clang++ -g -std=c++98 -D NAMESPACE=std test.cpp -Iiterators -I.
./a.out > std_test.txt
diff ft_test.txt std_test.txt
