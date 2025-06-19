#pragma once
#ifndef GAME_H
#define GAME_H

//trrrr ha-cha!

#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include <algorithm>

#include <memory>

/* ========================================
 * +-+-+-+-+-+-+-+
 * |			 |
 * |Game 	     |
 * +-+-+-+-+-+-+-+
 * ========================================*/

class Game{
public:
	Game();
	void run();

private:
	void processEvents();
	void update();
	void render();

private:
	sf::RenderWindow window;
};

/* ========================================
 * +-+-+-+-+-+-+-+
 * |			 |
 * |SceneNode    |
 * +-+-+-+-+-+-+-+
 * ========================================*/


class SceneNode
: public sf::Transformable
, public sf::Drawable{
public:
	typedef std::unique_ptr<SceneNode> Ptr;

public:
	SceneNode();
	SceneNode(const SceneNode&) = delete;
	SceneNode& operator=(const SceneNode&) = delete;

	void attachChild(Ptr child);
	Ptr detachChild(const SceneNode& node);	

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const = 0;	

private:
	std::vector<Ptr> Children;
	SceneNode* Parent;

};


namespace Textures{
	enum ID{
		Rabbit
	};
}

template <typename Resource, typename Identifier>
class ResourceHolder{
private:
	std::map<Identifier, std::unique_ptr<Resource>> ResourceMap;

public:
	Resource& get(Identifier id);
	const Resource& get(Identifier id) const;
	void load(Identifier id, const std::string& filename);
	
	template<typename Parameter>
	void load(Identifier id, const std::string& filename, const Parameter& secondParam);
};

#include "resource_holder.inl"
#endif // Game_H	
