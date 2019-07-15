#include "game.hpp"

const sf::Time deltaTime = sf::seconds(0.01f);

//virtual Collide(obj[i], obj[j]);
class B
{
	std::string str;
public:
	B() {str = "col2 class\n";}
	void print() {std::cout << str;}
};
class A
{
	B b;
public:
	void print() {b.print();}
	void scripttest() 
	{
		sol::state lua;
		lua.open_libraries(sol::lib::base, sol::lib::math);
		lua.new_usertype<A>("A", sol::constructors<A()>(),
		"print", &A::print);
		lua.new_usertype<B>("B", sol::constructors<B()>(),
		"print", &B::print);
		lua["b"] = std::ref(A::b);
		lua.script("b:print()");
	}
};
void sol3test()
{
	auto a = std::make_shared<A>();
	a->scripttest();
	sol::state lua;
	lua.open_libraries(sol::lib::base, sol::lib::math);
	lua.new_usertype<A>("A", sol::constructors<A()>(),
		"print", &A::print);
	//lua.new_usertype<B>("B", sol::constructors<B()>(),
	//	"print", &B::print);
	lua.script_file("src/script.lua");
	//lua["test"](a);
}
int main()
{
	//sol3test();
	App game;
	int exitCode = game.run();
	return exitCode;
	return 0;
}