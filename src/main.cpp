#include <iostream>

template<typename ...T>
void print(T ...args){
	auto printArg{
		[](const auto &arg){std::cout << arg;}
	};
	(printArg(args), ...);
}
int main(){
	print("Hello, World!");
	return 0;
}