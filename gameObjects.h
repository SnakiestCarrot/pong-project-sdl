#ifndef GAMEOBJECT_H
#define GAMEOBJECTS_H


struct Ball {
  double posX;
  double posY;
  double speedX;
  double speedY;
};

struct Paddle {
  double posX;
  double posY;
  double speedX;
  double speedY;
  int height;
};


#endif