#ifndef MAP_HPP_
#define MAP_HPP_
#include <iostream>
#include <vector>
#include <random>
#include "objectmanager.hpp"
#ifndef NDEBUG
#define __DEBUG_EXEC(code) code
#else
#define __DEBUG_EXEC(code) ;
#endif
class Map
{
    ObjectManager& oManager;
    std::vector<std::vector<int>> matrix;
public:
    Map(ObjectManager& oManager);
    ~Map();
    void setMatrix(std::vector<std::vector<int>> matrix);
    std::vector<std::vector<int>> getMatrix() const;
    void load() const;
    std::vector<std::vector<int>> generate(std::size_t size, double init_chance,
    std::size_t newlimit, std::size_t deletelimit, std::size_t numberSteps);
    std::vector<std::vector<int>> initMatrix(std::size_t size, double init_chance);
    std::vector<std::vector<int>> generateStep(std::size_t newlimit, std::size_t deletelimit);
    void dumpMatrix(std::vector<std::vector<int>> matrix) const;
};
#endif //MAP_HPP_