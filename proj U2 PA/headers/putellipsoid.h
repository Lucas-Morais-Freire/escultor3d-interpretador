#ifndef PUTELLIPSOID_H
#define PUTELLIPSOID_H

#include "figurageometrica.h"
#include "sculptor.h"

class PutEllipsoid : public FiguraGeometrica {
    private:
        int xcenter, ycenter, zcenter, rx, ry, rz;
    public:
        PutEllipsoid(int _xcenter, int _ycenter, int _zcenter, int _rx, int _ry, int _rz, float _r, float _g, float _b, float _a) {
            xcenter = _xcenter; ycenter = _ycenter; zcenter = _zcenter; rx = _rx; ry = _ry; rz = _rz;
            r = _r; g = _g; b = _b; a = _a;
        }
        void draw(Sculptor& t) {
            t.setColor(r, g, b, a);
            t.putEllipsoid(xcenter, ycenter, zcenter, rx, ry, rz);
        }
};

#endif //PUTELLIPSOID_H