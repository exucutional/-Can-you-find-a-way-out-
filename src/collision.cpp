#include "collision.hpp"
static const float NORMAL_TOLERANCE = 0.0001f;
static const std::size_t CHARACTER_SIZE = 10;
static const std::size_t OUTLINE_THICKNESS = 1;
static inline sqr(float val)
{
	return val * val;
}
static inline float getLength(const sf::Vector2f& vector)
{
	return sqrt(sqr(vector.x) + sqr(vector.y));
}
static inline dotProduct(const sf::Vector2f& v1, const sf::Vector2f& v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}
static inline sf::Vector2f getNormal(const sf::Vector2f& vector)
{
	return sf::Vector2f(-vector.y, vector.x);
}
static inline sf::Vector2f getNormalized(const sf::Vector2f& vector)
{
	float length = getLength(vector);
	if (length < NORMAL_TOLERANCE)
		return sf::Vector2f();
	return sf::Vector2f(vector.x / length, vector.y / length);
}
static inline sf::Vector2f getPerpendicularAxis(const sf::Vector2f& vertex1, const sf::Vector2f& vertex2)
{
	return getNormal(getNormalized(vertex2 - vertex1));
}
static inline bool areOverlapping(const sf::Vector2f& v1, const sf::Vector2f& v2)
{
	return v1.x <= v2.y && v1.y >= v2.x;
}
static inline float getOverlapLength(const sf::Vector2f& v1, const sf::Vector2f& v2)
{
	if (!areOverlapping(v1, v2))
		return 0.f;
	return std::min(v1.y, v2.y) - std::max(v1.x, v2.x);
}
static inline sf::Vector2f getGlobalCenter(const sf::Shape& shape)
{
	const sf::Transform& transform = shape.getTransform();
	sf::FloatRect local = shape.getLocalBounds();
	return transform.transformPoint(local.width / 2.f, local.height / 2.f);
}
static sf::Vector2f projectOnAxis(const std::vector<sf::Vector2f>& vertices, const sf::Vector2f& axis)
{
	float min = std::numeric_limits<float>::infinity();
	float max = -std::numeric_limits<float>::infinity();
	for (auto& vertex: vertices) {
		float projection = dotProduct(vertex, axis);
		if (projection < min)
			min = projection;
		if (projection > max)
			max = projection;
	}
	return sf::Vector2f(min, max);
}
static std::vector<sf::Vector2f> getVertices(const sf::ConvexShape& convex)
{
	std::vector<sf::Vector2f> vertices;
	const sf::Transform& transform = convex.getTransform();
	auto pointCount = convex.getPointCount();
	assert(pointCount >= 3);
	for (std::size_t i = 0; i < pointCount; i++) {
		vertices.push_back(transform.transformPoint(convex.getPoint(i)));
	}
	return vertices;
}
static std::vector<sf::Vector2f> getPerpendicularAxes(const sf::ConvexShape& convex1, const sf::ConvexShape& convex2)
{
	std::vector<sf::Vector2f> axes;
	auto pointCount1 = convex1.getPointCount();
	assert(pointCount1 >= 3);
	auto pointCount2 = convex2.getPointCount();
	assert(pointCount2 >= 3);
	for (std::size_t i = 1; i <= pointCount1; i++) {
		axes.push_back(getPerpendicularAxis(convex1.getPoint(i), convex1.getPoint(i - 1)));
	}
	axes.push_back(getPerpendicularAxis(convex1.getPoint(0), convex1.getPoint(pointCount1 - 1)));
	for (std::size_t i = 1; i <= pointCount2; i++) {
		axes.push_back(getPerpendicularAxis(convex2.getPoint(i), convex2.getPoint(i - 1)));
	}
	axes.push_back(getPerpendicularAxis(convex2.getPoint(0), convex2.getPoint(pointCount2 - 1)));
	return axes;
}
Collider::Collider()
{
	__DEBUG_EXEC(std::cout << "Collider()\n");
	rectangle.setFillColor(sf::Color::Transparent);
	rectangle.setOutlineThickness(OUTLINE_THICKNESS);
	rectangle.setOutlineColor(sf::Color::White);
	LuaScript script("data/setting.lua");
	std::string fontPath = script.get<std::string>("FontPath");
	font.loadFromFile(fontPath);
	info.setFont(font);
	info.setStyle(sf::Text::Regular);
	info.setFillColor(sf::Color::White);
	info.setCharacterSize(CHARACTER_SIZE);
}
Collider::~Collider()
{
	__DEBUG_EXEC(std::cout << "~Collider\n");
}
const sf::RectangleShape& Collider::getOBB()
{
	return rectangle;
}
const sf::Text& Collider::getInfo() 
{
	return info;
}
void Collider::setOBBposition(float x, float y)
{
	rectangle.setPosition(x, y);
	info.setPosition(x, y - 2 * (2 * info.getLineSpacing() + info.getCharacterSize()));
	std::stringstream ss;
	ss << "X:" << x << "\nY:" << y;
	std::string infostr = ss.str();
	info.setString(infostr);
}
void Collider::setOBBposition(const sf::Vector2f& position)
{
	rectangle.setPosition(position);
	info.setPosition(position.x, position.y - 2 * (2 * info.getLineSpacing() + info.getCharacterSize()));
	std::stringstream ss;
	ss << "X:" << position.x << "\nY:" << position.y;
	std::string infostr = ss.str();
	info.setString(infostr);
}
void Collider::setOBBsize(const sf::Vector2f& size)
{
	rectangle.setSize(size);
}
Collision::Collision()
{
	__DEBUG_EXEC(std::cout << "Collision\n");
}
Collision::~Collision()
{
	__DEBUG_EXEC(std::cout << "~Collision\n");
}
bool Collision::intersect(const sf::CircleShape& circle1, const sf::CircleShape& circle2, sf::Vector2f* mtv_ptr)
{
	sf::Vector2f centre1 = getGlobalCenter(circle1);
	sf::Vector2f centre2 = getGlobalCenter(circle2);
	if (sqr(centre1.x - centre2.x) + sqr(centre1.y - centre2.y) > sqr(circle1.getRadius()+ circle2.getRadius())) {
		if (mtv_ptr)
			*mtv_ptr = sf::Vector2f();
		return false;
	}
	if (mtv_ptr)
		*mtv_ptr = getNormalized(centre1 - centre2) * (circle1.getRadius() + circle2.getRadius() - getLength(centre1- centre2));
	return true;
}
bool Collision::intersect(const sf::RectangleShape& rectangle1, const sf::RectangleShape& rectangle2, sf::Vector2f* mtv_ptr)
{
	sf::FloatRect r1 = rectangle1.getLocalBounds();
	sf::FloatRect r2 = rectangle2.getLocalBounds();
	return r1.intersects(r2);
}
bool Collision::intersect(const sf::ConvexShape& convex1, const sf::ConvexShape& convex2, sf::Vector2f* mtv_ptr)
{
	std::vector<sf::Vector2f> vertices1 = getVertices(convex1);
	std::vector<sf::Vector2f> vertices2 = getVertices(convex2);
	std::vector<sf::Vector2f> axes = getPerpendicularAxes(convex1, convex2);
	float minOverlap = std::numeric_limits<float>::infinity();
	for (auto& axis : axes) {
		sf::Vector2f proj1 = projectOnAxis(vertices1, axis);
		sf::Vector2f proj2 = projectOnAxis(vertices2, axis);
		float overlap = getOverlapLength(proj1, proj2);
		if (overlap == 0.f) { 
			if (mtv_ptr)
				*mtv_ptr = sf::Vector2f();
			return false;
		} else {
			if (overlap < minOverlap) {
				minOverlap = overlap;
				if (mtv_ptr)
					*mtv_ptr = axis * minOverlap; 
			}
		}
	}
	if (mtv_ptr) {
		bool notPointingInTheSameDirection = dotProduct(getGlobalCenter(convex1) - getGlobalCenter(convex2), *mtv_ptr) < 0;
		if (notPointingInTheSameDirection) { (*mtv_ptr) = -(*mtv_ptr); }
	}
	return true;
}	