#pragma once

template<typename  T>
class QuadTree {
private:
    static const int MAX_OBJECTS = 4;	// Максимальное количество объектов в узле
    static const int MAX_LEVELS = 3;    // Максимальная глубина дерева

    int level;							// Уровень узла
    std::vector<T> objects;				// Объекты, хранящиеся в узле
    float x, y;							// Позиция узла
    float width, height;				// Размер узла
    QuadTree* nodes[4];					// Дочерние узлы

public:
    QuadTree(int level, float x, float y, float width, float height);
    ~QuadTree();
    void clear();
    void split();
    int getIndex(T entity);
    void insert(T entity);
    std::vector<T> retrieve(T entity);
};

template <typename T>
QuadTree<T>::QuadTree(int level, float x, float y, float width, float height) : level(level), x(x), y(y), width(width), height(height)
{
	for (int i = 0; i < 4; ++i) {
		nodes[i] = nullptr;
	}
}

template <typename T>
QuadTree<T>::~QuadTree()
{
	for (int i = 0; i < 4; ++i) {
		delete nodes[i];
	}
}

template <typename T>
void QuadTree<T>::clear()
{
	objects.clear();
	for (int i = 0; i < 4; ++i) {
		if (nodes[i] != nullptr) {
			nodes[i]->clear();
			delete nodes[i];
			nodes[i] = nullptr;
		}
	}
}

template <typename T>
void QuadTree<T>::split()
{
	float subWidth = width / 2;
	float subHeight = height / 2;

	nodes[0] = new QuadTree(level + 1, x, y, subWidth, subHeight); // Северо-западный
	nodes[1] = new QuadTree(level + 1, x + subWidth, y, subWidth, subHeight); // Северо-восточный
	nodes[2] = new QuadTree(level + 1, x, y + subHeight, subWidth, subHeight); // Юго-западный
	nodes[3] = new QuadTree(level + 1, x + subWidth, y + subHeight, subWidth, subHeight); // Юго-восточный
}

template <typename T>
int QuadTree<T>::getIndex(T entity)
{
	int index = -1;
	double verticalMidpoint = x + (width / 2);
	double horizontalMidpoint = y + (height / 2);

	double entityX, entityY;
	entity->getCords(entityX, entityY);

	bool topQuad = (entityY < horizontalMidpoint);
	bool bottomQuad = (entityY > horizontalMidpoint);

	if (entityX < verticalMidpoint) {
		if (topQuad) {
			index = 0; // Северо-западный
		}
		else if (bottomQuad) {
			index = 2; // Юго-западный
		}
	}
	else {
		if (topQuad) {
			index = 1; // Северо-восточный
		}
		else if (bottomQuad) {
			index = 3; // Юго-восточный
		}
	}

	return index;
}

template <typename T>
void QuadTree<T>::insert(T entity)
{
	if (nodes[0] != nullptr) {
		int index = getIndex(entity);
		if (index != -1) {
			nodes[index]->insert(entity);
			return;
		}
	}

	objects.push_back(entity);

	if (objects.size() > MAX_OBJECTS && level < MAX_LEVELS) {
		if (nodes[0] == nullptr) {
			split();
		}

		for (size_t i = 0; i < objects.size(); ++i) {
			int index = getIndex(objects[i]);
			if (index != -1) {
				nodes[index]->insert(objects[i]);
				objects.erase(objects.begin() + i);
				--i;
			}
		}
	}
}

template <typename T>
std::vector<T> QuadTree<T>::retrieve(T entity)
{
	std::vector<T> returnObjects;
	int index = getIndex(entity);
	if (index != -1 && nodes[0] != nullptr) {
		returnObjects = nodes[index]->retrieve(entity);
	}
	else
	{
		for (const auto& obj : objects) {
			returnObjects.push_back(obj);
		}
	}
	return returnObjects;
}


