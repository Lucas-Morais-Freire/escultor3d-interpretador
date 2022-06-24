#include <vector>
#include <string.h>
#include <fstream>
#include <iostream>
#include "headers/putvoxel.h"
#include "headers/cutvoxel.h"
#include "headers/putbox.h"
#include "headers/cutbox.h"
#include "headers/putsphere.h"
#include "headers/cutsphere.h"
#include "headers/putellipsoid.h"
#include "headers/cutellipsoid.h"
#include "headers/putcylinder.h"
#include "headers/cutcylinder.h"

void interpreter(std::vector<FiguraGeometrica*>& figs, const char* readFilePath, int dims[3]) {
    std::fstream fin;
    fin.open(readFilePath);
    if (!fin.is_open()) {
        exit(1);
    }
    std::string token;
    fin >> token;
    if (strcmp(token.data(), "dim") == 0) {
        fin >> dims[0] >> dims[1] >> dims[2];
    } else {
        exit(1);
    }

    float r, g, b, a;

    while(!fin.eof()) {
        fin >> token;
        if (strcmp(token.data(), "putvoxel") == 0) {
            int x, y, z;
            fin >> x >> y >> z >> r >> g >> b >> a;
            PutVoxel* o = new PutVoxel(x, y, z, r, g, b, a);
            figs.push_back(o);
        } else if (strcmp(token.data(), "cutvoxel") == 0) {
            int x, y, z;
            fin >> x >> y >> z;
            CutVoxel* o = new CutVoxel(x, y, z);
            figs.push_back(o);
        } else if (strcmp(token.data(), "putbox") == 0) {
            int x0, x1, y0, y1, z0, z1;
            fin >> x0 >> x1 >> y0 >> y1 >> z0 >> z1 >> r >> g >> b >> a;
            PutBox* o = new PutBox(x0, x1, y0, y1, z0, z1, r, g, b, a);
            figs.push_back(o);
        } else if (strcmp(token.data(), "cutbox") == 0) {
            int x0, x1, y0, y1, z0, z1;
            fin >> x0 >> x1 >> y0 >> y1 >> z0 >> z1;
            CutBox* o = new CutBox(x0, x1, y0, y1, z0, z1);
            figs.push_back(o);
        } else if (strcmp(token.data(), "putsphere") == 0) {
            int xcenter, ycenter, zcenter, radius;
            fin >> xcenter >> ycenter >> zcenter >> radius >> r >> g >> b >> a;
            PutSphere* o = new PutSphere(xcenter, ycenter, zcenter, radius, r, g, b, a);
            figs.push_back(o);
        } else if (strcmp(token.data(), "cutsphere") == 0) {
            int xcenter, ycenter, zcenter, radius;
            fin >> xcenter >> ycenter >> zcenter >> radius;
            CutSphere* o = new CutSphere(xcenter, ycenter, zcenter, radius);
            figs.push_back(o);
        } else if (strcmp(token.data(), "putellipsoid") == 0) {
            int xcenter, ycenter, zcenter, rx, ry, rz;
            fin >> xcenter >> ycenter >> zcenter >> rx >> ry >> rz >> r >> g >> b >> a;
            PutEllipsoid* o = new PutEllipsoid(xcenter, ycenter, zcenter, rx, ry, rz, r, g, b, a);
            figs.push_back(o);
        } else if (strcmp(token.data(), "cutellipsoid") == 0) {
            int xcenter, ycenter, zcenter, rx, ry, rz;
            fin >> xcenter >> ycenter >> zcenter >> rx >> ry >> rz;
            CutEllipsoid* o = new CutEllipsoid(xcenter, ycenter, zcenter, rx, ry, rz);
            figs.push_back(o);
        } else if (strcmp(token.data(), "putcylinder") == 0) {
            float xa, ya, za, xb, yb, zb, rad;
            fin >> xa >> ya >> za >> xb >> yb >> zb >> rad >> r >> g >> b >> a;
            PutCylinder* o = new PutCylinder(xa, ya, za, xb, yb, zb, rad, r, g, b, a);
            figs.push_back(o);
        } else if (strcmp(token.data(), "cutcylinder") == 0) {
            float xa, ya, za, xb, yb, zb, rad;
            fin >> xa >> ya >> za >> xb >> yb >> zb >> rad;
            CutCylinder* o = new CutCylinder(xa, ya, za, xb, yb, zb, rad);
            figs.push_back(o);
        } else {
            fin.ignore(150, '\n');
        }
    }
    fin.close();
}

int main() {
    int dims[3] = {0, 0, 0};
    std::vector<FiguraGeometrica*> figs;

    interpreter(figs, "instructions.txt", dims);

    Sculptor falcon(dims[0], dims[1], dims[2]);

    for (int i = 0; i < figs.size(); i++) {
        figs[i]->draw(falcon);
    }

    falcon.writeOFF("main.off");

    for (int i = 0; i < figs.size(); i++) {
        delete figs[i];
    }

    return 0;
}