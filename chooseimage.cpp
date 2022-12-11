#include "chooseimage.h"

QPixmap chooseImage::selImage(int sel) {
    switch (sel) {
    case 1:
        pix.load(":/resources/img/pngwing.com.png");
        break;
    case 2:
        pix.load(":/resources/img/pngwing.com (1).png");
        break;
    case 3:
        pix.load(":/resources/img/pngwing.com (2).png");
        break;
    case 4:
        pix.load(":/resources/img/pngwing.com (3).png");
        break;
    default:
        pix.load(":/resources/img/pngwing.com.png");
    }
    return pix;
}
