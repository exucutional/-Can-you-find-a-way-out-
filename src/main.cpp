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
	sol::state lua;
	sol::state lua2;
	lua2.open_libraries(sol::lib::base);
	sol::load_result lr = lua.load("print 'hello'; a = function (v) print(v) return v end");
	sol::protected_function target = lr;
	sol::bytecode target_bc = target.dump();
	auto result2 = lua2.safe_script(target_bc.as_string_view(), sol::script_pass_on_error);
}
int main()
{
	//sol3test();
	App game;
	int exitCode = game.run();
	return exitCode;
	return 0;
}