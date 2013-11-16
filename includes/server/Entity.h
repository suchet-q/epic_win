#pragma once

# include		"Coord.hpp"
//# include		"Sprite.h"

enum			entityType
  {
    PLAYER1 = 1,
    PLAYER2,
    PLAYER3,
    PLAYER4,
    MOBB,
    SHOT,
    LANDSCAPE
  };


class			Entity
{
protected:
  Coord<>		_intCoord;
  Coord<float>		_coord;
  Coord<float>		_vecDir;
  entityType		_type;
  //  Sprite		_sprite;

public:
  Entity();
  ~Entity();

  entityType		getType() const;
  Coord<>&			getCoord();

  void			setVecDir(Coord<float> const &coord);
  void			setType(entityType type);

  virtual void		update() = 0;
};
