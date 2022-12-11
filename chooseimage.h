#ifndef CHOOSEIMAGE_H
#define CHOOSEIMAGE_H

#include "qpixmap.h"

class chooseImage
{
public:
    chooseImage();
    QPixmap pix;

public slots:
    QPixmap selImage(int sel);
};

#endif // CHOOSEIMAGE_H
