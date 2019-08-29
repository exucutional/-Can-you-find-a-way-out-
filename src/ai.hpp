#ifndef AI_HPP_
#define AI_HPP_
#include "objectmanager.hpp"
#include "map.hpp"
#include "vector_func.hpp"
class AImanager
{
    ObjectManager& oManager;
    Map& map;
    sol::state lua;
    sol::bytecode bcode;
public:
    AImanager(ObjectManager& oManager, Map& map);
    void init();
    void update();
};
#endif //AI_HPP_