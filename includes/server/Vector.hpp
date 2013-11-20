#pragma once

# include		<cmath>

# include		"Coord.hpp"

class			Vector : public Coord<float>
{
public:
  Vector() : Coord() {}
  Vector(float x, float y) : Coord(x, y) {}
  ~Vector() {}

  void			normalize() {
    float		norme = sqrt((_x * _x) + (_y * _y));
    
    _x /= norme;
    _y /= norme;
  }
};
