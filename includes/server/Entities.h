#pragma once

# include		<list>
# include		"Coord.hpp"
//# include		"Sprite.h"

enum			entityGlobalType
{
	PLAYER,
	PLAYERMISSIL,
	MOBB,
	MOBBMISSIL,
	DECOR
};

enum			entityType
  {
	PLAYER1 = 1,
	PLAYER2,
	PLAYER3,
	PLAYER4,
	DRONE = 6,
	ALIEN,
	DOG,
	JUMPER,
	XWING,
	METROID,
	LARVE,
	FIREBALL,
	BASIC_SHOT,
	BALLS,
	MEDIUM_SHOT,
	BIG_SHOT,
	BIGGEST_SHOT,
	KIKOU_SHOT
  };

class			Entity
{
protected:
  Coord<>		_intCoord;
  Coord<float>		_coord;
  Coord<float>		_vecDir;
  entityType		_type;
  entityGlobalType	_globalType;
  //  Sprite		_sprite;

public:
  Entity();
  ~Entity();

  entityType		getType() const;
  Coord<>&		getCoord();
  Coord<float>&		getFloatCoord();
  entityGlobalType	getGlobalType() const;
  void				setGlobalType(entityGlobalType);

  void			setVecDir(float x, float y);
  void			setType(entityType type);

  virtual void		update(std::list<Entity *> &) = 0;
};
