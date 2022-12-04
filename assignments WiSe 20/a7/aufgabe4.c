/*
 * Stephan Jokiel
 * Maxine Rahlfes
 */

#define _USE_MATH_DEFINES
#define _GNU_SOURCE

#include "base.h"
#include <math.h>


enum Tag {
    TCylinder,
    TSphere,
    TCuboid
} typedef Tag;

struct Cylinder {
    double r, h; // V = pi * r^2 * h
} typedef Cylinder;

struct Sphere {
    double r; // V = 4 / 3 * pi * r^3
} typedef Sphere;

struct Cuboid {
    double a, b, c; // V = a * b *c
} typedef Cuboid;

struct GeomObject {
    Tag form;
    union {
        Cylinder cyl;
        Sphere sph;
        Cuboid cub;
    };
} typedef GeomObject;


GeomObject make_cylinder(double r, double h) {
    require("positive zahl", r >= 0 && h >= 0);
    GeomObject o = {};
    o.form = TCylinder;
    o.cyl.r = r;
    o.cyl.h = h;
    return o;
}

GeomObject make_sphere(double r) {
    require("positive zahl", r >= 0);
    GeomObject o = {};
    o.form = TSphere;
    o.sph.r = r;
    return o;
}

GeomObject make_cuboid(double a, double b, double c) {
    require("positive zahl", a >= 0 && b >= 0 && c >= 0);
    GeomObject o = {};
    o.form = TCuboid;
    o.cub.a = a;
    o.cub.b = b;
    o.cub.c = c;
    return o;
}

double volume(GeomObject o);

void volume_test(void) {
    test_within_d(volume(make_sphere(2)), 4 / 3.0 * M_PI * 2 * 2 * 2, 1e-6);
    test_within_d(volume(make_cuboid(2, 3, 4)), 2 * 3 * 4, 1e-6);
    test_within_d(volume(make_cylinder(3, 4)), 4 * M_PI * 3 * 3, 1e-6);
}

// GeomObject -> double
// Computes the surface area of the given object.
double volume(GeomObject o) {
    double volm;
    require("valid tag", o.form == TSphere || o.form == TCuboid || o.form == TCylinder);
    switch (o.form) {
        case TSphere:
            volm = M_PI * o.sph.r * o.sph.r * o.sph.r * 4 / 3;
            break;
        case TCuboid:
            volm = o.cub.a * o.cub.b * o.cub.c;
            break;
        case TCylinder:
            volm = o.cyl.r * o.cyl.r * o.cyl.h * M_PI;
            break;
    }
	ensure("non-negative result", volm >= 0);
    return volm;
}

int main(void) {
    volume_test();
    return 0;
}


/*   d)
 *      Die Enumeration 'tag' ist wichtig, um dem Eingabewert "o" zuzuweisen, welche eigenschaften er besitzt.
 *      In unserem Fall hat eine sphere nur einen Wert, 'r' .
 *      Cylinder z.B. jedoch 2.
 *      Wenn man nun also, ohne dass der input ein tag hat, diesen eingibt, (und er nicht durch unser
 *      'require' ausgefiltert wird) und nun angibt, dass der radius. o.r (o.tag.r, aber tag entfällt)
 *      dann wüsste unser programm nicht, welche Berechnung zu tun ist.
 *      Die Enumeration erleichtert uns also, die eingegeben werte ihrer zugehörigen Berechnung zuzuweisen.
 *
 */
