#pragma once

template<typename T = unsigned short int>
class			Coord
{
private:
  T			_x;
  T			_y;

public:
  Coord(T x, T y) {
    this->_x = x;
    this->_y = y;
  }
  Coord() {
    this->_x = 0;
    this->_y = 0;
  }
  ~Coord() {}

  T			getX() const {return _x;}
  T			getY() const {return _y;}

  void			set (T x, T y) {
    this->_x = x;
    this->_y = y;
  }
  void			setX(T x) {this->_x = x;}
  void			setY(T y) {this->_y = y;}

  Coord			&operator=(Coord const &coord) {
    this->_x = coord.getX();
    this->_y = coord.getY();
    return *this;
  }

  Coord			&operator+(Coord const &coord) {
    this->_x += coord.getX();
    this->_y += coord.getY();
    return *this;
  }
  Coord			&operator-(Coord const &coord) {
    this->_x -= coord.getX();
    this->_y -= coord.getY();
    return *this;
  }
  Coord			&operator/(Coord const &coord) {
    this->_x /= coord.getX();
    this->_y /= coord.getY();
    return *this;
  }
  Coord			&operator*(Coord const &coord) {
    this->_x *= coord.getX();
    this->_y *= coord.getY();
    return *this;
  }

  Coord			&operator+=(Coord const &coord) {
    *this = *this + coord;
    return *this;
  }
  Coord			&operator-=(Coord const &coord) {
    *this = *this - coord;
    return *this;
  }
  Coord			&operator/=(Coord const &coord) {
    *this = *this / coord;
    return *this;
  }
  Coord			&operator*=(Coord const &coord) {
    *this = *this * coord;
    return *this;
  }
};
