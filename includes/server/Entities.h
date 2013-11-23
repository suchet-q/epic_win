#pragma once

# include		<list>
# include		"Coord.hpp"
# include		"Vector.hpp"

enum			entityGlobalType
{
	PLAYER,
	PLAYERMISSIL,
	MOBB,
	MOBBMISSIL,
	DECOR,
	NOTHING
};

enum			entityType
  {
	PLAYERS,
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
	KIKOU_SHOT,
	MONSTER,
	MONSTER_REVERT,
	BIDULE,
	BIDULE_REVERT,
	PLATFORM,
	PLATFORM_REVERT,
	PLATFORM2,
	PLATFORM2_REVERT
  };

class			Entity
{
protected:
  Coord<>		_intCoord;
  Coord<float>		_coord;
  Vector		_vecDir;
  entityType		_type;
  entityGlobalType	_globalType;
  char			_ID;

public:
  Entity();
  ~Entity();

  char		       	getID() const;
  void			setID(char);
  entityType		getType() const;
  Coord<>&		getCoord();
  Coord<float>&		getFloatCoord();
  entityGlobalType	getGlobalType() const;
  void			setGlobalType(entityGlobalType);

  void			setVecDir(float x, float y);
  void			setType(entityType type);

  virtual void		update(std::list<Entity *> &) = 0;
};
