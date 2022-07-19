clang++ -Wall -Werror -Wextra -std=c++98 -D NAMESPACE=ft test_vector_and_stack.cpp -I.
./a.out > ft_test.txt
clang++ -Wall -Werror -Wextra -std=c++98 -D NAMESPACE=std test_vector_and_stack.cpp -I.
./a.out > std_test.txt
diff ft_test.txt std_test.txt
rm a.out
