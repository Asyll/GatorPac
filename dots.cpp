#include "dots.h"

dots::dots(int posx, int posy, Qstring name)
{
    this->posx = posx;
    this->posy = posy;
    this->name = name;

QString imageLocation = "://Images/Characters/" + name + "_forward.png";
forward.load(imageLocation);


}
