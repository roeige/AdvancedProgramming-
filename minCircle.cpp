/**
 * Name: Roei Gehassi and Itay Shwartz
 * ID: 208854754 and 318528171
 */
// C++ program to find the minimum enclosing
// circle for N integer points in a 2-D plane
#include <algorithm>
#include <assert.h>
#include <iostream>
#include <math.h>
#include <vector>
#include "anomaly_detection_util.h"
#include "minCircle.h"



// Defining infinity
#define INF 1e18

// Function to return the euclidean distance
// between two points
double dist(const Point &a, const Point &b) {
    return sqrt(pow(a.x - b.x, 2)
                + pow(a.y - b.y, 2));
}

// Function to check whether a point lies inside
// or on the boundaries of the circle
bool is_inside(const Circle &c, const Point &p) {
    return dist(c.center, p) <= c.radius;
}

// The following two functions are used
// To find the equation of the circle when
// three points are given.

// Helper method to get a circle defined by 3 points
Point get_circle_center(double bx, double by,
                        double cx, double cy) {
    double B = bx * bx + by * by;
    double C = cx * cx + cy * cy;
    double D = bx * cy - by * cx;
    return {(float) ((cy * B - by * C) / (2 * D)),
            (float) ((bx * C - cx * B) / (2 * D))};
}

// Function to return a unique circle that
// intersects three points
Circle circle_from(const Point &A, const Point &B,
                   const Point &C) {
    Point I = get_circle_center(B.x - A.x, B.y - A.y,
                                C.x - A.x, C.y - A.y);

    I.x += A.x;
    I.y += A.y;
    return {I, (float) dist(I, A)};
}

// Function to return the smallest circle
// that intersects 2 points
Circle circle_from(const Point &A, const Point &B) {
    // Set the center to be the midpoint of A and B
    Point C = {(float) ((A.x + B.x) / 2.0), (float) ((A.y + B.y) / 2.0)};

    // Set the radius to be half the distance AB
    return {C, (float) (dist(A, B) / 2.0)};
}

// Function to check whether a circle
// encloses the given points
bool is_valid_circle(const Circle &c,
                     vector<Point> &P, int size) {

    // Iterating through all the points
    // to check whether the points
    // lie inside the circle or not
    for (const Point &p: P)
        if (!is_inside(c, p))
            return false;
    return true;
}

// Function to return the minimum enclosing
// circle for N <= 3
Circle min_circle_trivial(vector<Point> &P, size_t size) {
    assert(size <= 3);
    if (size == 0) {
        return {{0, 0}, 0};
    } else if (size == 1) {
        return {P[0], 0};
    } else if (size == 2) {
        return circle_from(P[0], P[1]);
    }

    // To check if MEC can be determined
    // by 2 points only
    for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 3; j++) {
            Circle c = circle_from(P[i], P[j]);
            if (is_valid_circle(c, P, (int) size))
                return c;
        }
    }
    return circle_from(P[0], P[1], P[2]);
}

// Returns the MEC using Welzl's algorithm
// Takes a set of input points P and a set R
// points on the circle boundary.
// n represents the number of points in P
// that are not yet processed.
Circle welzl_helper(Point **P,
                    int p_size, std::vector<Point> R, int r_size) {
    // Base case when all points processed or |R| = 3
    if (p_size == 0 || r_size == 3) {
        return min_circle_trivial(R, r_size);
    }

    // Pick a random point randomly
    int idx = rand() % p_size;
    Point p = *P[idx];

    // Put the picked point at the end of P
    // since it's more efficient than
    // deleting from the middle of the vector
    swap(P[idx], P[p_size - 1]);
    // Get the MEC circle d from the
    // set of points P - {p}
    Circle d = welzl_helper(P, p_size - 1, R, r_size);
    // If d contains p, return d
    if (is_inside(d, p)) {
        return d;
    }
    // Otherwise, must be on the boundary of the MEC
    R.push_back(p);

    // Return the MEC for P - {p} and R U {p}
    return welzl_helper(P, p_size - 1, R, r_size + 1);
}

Circle minimum_enclosing_circle(Point **P, size_t size) {
    Point **P_copy = P;
    //random_shuffle(P_copy[0], P_copy[size - 1]);
    std::vector<Point> R;
    R.reserve(size);
    return welzl_helper(P_copy, (int) size, R, 0);
}

Circle findMinCircle(Point **points, size_t size) {
    //initialize from points' array to points' vectors
//    std::vector<Point> p_vector;
//    p_vector.reserve(size);
//    for (int i = 0; i < size; i++) {
//        p_vector.push_back(*points[i]);
//    }
    return minimum_enclosing_circle(points, size);
}
