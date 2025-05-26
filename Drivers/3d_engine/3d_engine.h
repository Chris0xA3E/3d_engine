/*
 * 3d_engine.h
 *
 *  Created on: Apr 14, 2024
 *      Author: master
 */

#ifndef _3D_ENGINE_H_
#define _3D_ENGINE_H_

#pragma once

#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#define ScreenWidth 480
#define ScreenHight 272

#define FOV 20

#define PROJECTION_SCALE 70

typedef struct edge{unsigned int i; unsigned int j;} edge;
typedef struct point2d{ uint16_t x; uint16_t y;} point2d_t;
typedef struct point3d{ float x; float y; float z;} point3d_t;

typedef struct face{point3d_t* normal_v;point3d_t* p1; point3d_t* p2; point3d_t* p3;} face_t;
typedef struct face2d{point3d_t* normal_v;point2d_t* p1; point2d_t* p2; point2d_t* p3;} face2d_t;

typedef struct list_node{
	point3d_t* point;
	struct list_node * next;
}node_t;


typedef struct stl_obj{face_t* faces; uint32_t noTriangles;} stl_obj;
typedef struct stl_obj2d{face2d_t* faces; uint32_t noTriangles;} stl_obj2d;


//typedef struct edge{point3d_t i; point3d_t j;} edge;

typedef struct obj3d{
	point3d_t* points; // needs to be an array
	size_t point_len;

	edge* edges; // needs to be an array
	size_t edge_len;

} obj3d_t;

typedef struct {
    face2d_t* face2d;
    float average_z;
} face2d_with_z_t;

typedef struct obj2d{
	point2d_t* points; // needs to be an array
	size_t point_len;

	edge* edges; // needs to be an array
	size_t edge_len;

} obj2d_t;





node_t* createNode(point3d_t* key);
node_t* push(node_t* head,point3d_t* key);
node_t* pop(node_t* head);
node_t* search(node_t* head, point3d_t* key);


static point3d_t cube_vertices[] = {
    {-1, -1, -1}, // 0
    { 1, -1, -1}, // 1
    { 1,  1, -1}, // 2
    {-1,  1, -1}, // 3
    {-1, -1,  1}, // 4
    { 1, -1,  1}, // 5
    { 1,  1,  1}, // 6
    {-1,  1,  1}  // 7
};

static edge cube_edges[] = {
    {0, 1}, {1, 2}, {2, 3}, {3, 0}, // Bottom face
    {4, 5}, {5, 6}, {6, 7}, {7, 4}, // Top face
    {0, 4}, {1, 5}, {2, 6}, {3, 7}  // Vertical edges
};

static obj3d_t cube = {
		.edges = cube_edges,
		.edge_len = 12,
		.points = cube_vertices,
		.point_len = 8
};

static point3d_t torus_points[] = {
    {1.0, 0.0, 0.0},    // point 0
    {0.707, 0.707, 0.0},// point 1
    {0.0, 1.0, 0.0},    // point 2
    {-0.707, 0.707, 0.0}, // point 3
    {-1.0, 0.0, 0.0},   // point 4
    {-0.707, -0.707, 0.0}, // point 5
    {0.0, -1.0, 0.0},   // point 6
    {0.707, -0.707, 0.0},  // point 7
};

static edge torus_edges[] = {
    {0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}, {7, 0},
    {0, 2}, {2, 4}, {4, 6}, {6, 0}, {1, 3}, {3, 5}, {5, 7}, {7, 1}
};

static obj3d_t torus = {
		.points = torus_points,
		.point_len = sizeof(torus_points)/sizeof(point3d_t),
		.edges = torus_edges,
		.edge_len = sizeof(torus_edges)/sizeof(edge)
};



static point3d_t pyramid_points[] = {
    {0.0, 0.0, 1.0},    // point 0 (apex)
    {1.0, 1.0, 0.0},    // point 1 (base)
    {-1.0, 1.0, 0.0},   // point 2 (base)
    {-1.0, -1.0, 0.0},  // point 3 (base)
    {1.0, -1.0, 0.0}    // point 4 (base)
};

static edge pyramid_edges[] = {
    {0, 1}, {0, 2}, {0, 3}, {0, 4},
    {1, 2}, {2, 3}, {3, 4}, {4, 1}
};

static obj3d_t pyramid = {
	.points = pyramid_points,
	.point_len = sizeof(pyramid_points)/sizeof(point3d_t),
	.edges = pyramid_edges,
	.edge_len = sizeof(pyramid_edges)/sizeof(edge)
};


static point3d_t sphere_points[] = {
    // Sample points for a sphere
    {0.0f, 1.0f, 0.0f},    // point 0
    {0.5878f, 0.8090f, 0.0f},  // point 1
    {0.9511f, 0.3090f, 0.0f},  // point 2
    {0.9511f, -0.3090f, 0.0f}, // point 3
    {0.5878f, -0.8090f, 0.0f}, // point 4
    {0.0f, -1.0f, 0.0f},   // point 5
    {-0.5878f, -0.8090f, 0.0f},// point 6
    {-0.9511f, -0.3090f, 0.0f},// point 7
    {-0.9511f, 0.3090f, 0.0f}, // point 8
    {-0.5878f, 0.8090f, 0.0f}, // point 9
    {0.0f, 0.0f, 1.0f},    // point 10
    {0.0f, 0.9511f, 0.3090f},  // point 11
    {0.0f, 0.5878f, 0.8090f},  // point 12
    {0.0f, -0.5878f, 0.8090f}, // point 13
    {0.0f, -0.9511f, 0.3090f}, // point 14
    {0.0f, -0.9511f, -0.3090f},// point 15
    {0.0f, -0.5878f, -0.8090f},// point 16
    {0.0f, 0.5878f, -0.8090f}, // point 17
    {0.0f, 0.9511f, -0.3090f}, // point 18
    {0.0f, 0.0f, -1.0f},   // point 19
};

static edge sphere_edges[] = {
    // Sample edges for a sphere
    {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {0, 7}, {0, 8}, {0, 9},
    {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}, {7, 8}, {8, 9}, {9, 1},
    {1, 10}, {2, 10}, {3, 10}, {4, 10}, {5, 10}, {6, 10}, {7, 10}, {8, 10}, {9, 10},
    {1, 11}, {2, 12}, {3, 13}, {4, 14}, {5, 15}, {6, 16}, {7, 17}, {8, 18}, {9, 19}
};

static obj3d_t sphere = {
		.points = sphere_points,
		.point_len = sizeof(sphere_points)/sizeof(point3d_t),
		.edges = sphere_edges,
		.edge_len = sizeof(sphere_edges)/sizeof(edge)

};
static point3d_t tank_points[] = {
    // Tank body
    {0.0f, 0.0f, 0.0f},    // point 0 (front top)
    {2.0f, 0.0f, 0.0f},    // point 1 (front bottom)
    {2.0f, 0.0f, 1.0f},    // point 2 (rear bottom)
    {0.0f, 0.0f, 1.0f},    // point 3 (rear top)
    // Tank turret
    {1.0f, 0.5f, 0.5f},    // point 4 (turret front top)
    {1.5f, 0.5f, 0.5f},    // point 5 (turret front bottom)
    {1.5f, 0.5f, 0.0f},    // point 6 (turret rear bottom)
    {1.0f, 0.5f, 0.0f},    // point 7 (turret rear top)
    // Tank tracks
    {0.5f, -0.1f, 0.1f},   // point 8 (track front top)
    {1.5f, -0.1f, 0.1f},   // point 9 (track front bottom)
    {1.5f, -0.1f, -0.1f},  // point 10 (track rear bottom)
    {0.5f, -0.1f, -0.1f}   // point 11 (track rear top)
};

static edge tank_edges[] = {
    // Tank body edges
    {0, 1}, {1, 2}, {2, 3}, {3, 0},
    // Tank turret edges
    {4, 5}, {5, 6}, {6, 7}, {7, 4},
    // Connect turret to body
    {0, 4}, {1, 5}, {2, 6}, {3, 7},
    // Tank track edges
    {8, 9}, {9, 10}, {10, 11}, {11, 8},
    // Connect tracks to body
    {0, 8}, {1, 9}, {2, 10}, {3, 11}
};

static obj3d_t tank  =  {
		.points = tank_points,
		.point_len = sizeof(tank_points)/sizeof(point3d_t),
		.edges = tank_edges,
		.edge_len = sizeof(tank_edges)/sizeof(edge)
};


static point3d_t hexagonal_cuboid_points[] = {
    // Bottom hexagon
    {0.0f, 0.0f, 0.0f},     // point 0
    {1.0f, 0.0f, 0.0f},     // point 1
    {1.5f, 0.866f, 0.0f},   // point 2
    {1.0f, 1.732f, 0.0f},   // point 3
    {0.0f, 1.732f, 0.0f},   // point 4
    {-0.5f, 0.866f, 0.0f},  // point 5
    // Top hexagon
    {0.0f, 0.0f, 1.0f},     // point 6
    {1.0f, 0.0f, 1.0f},     // point 7
    {1.5f, 0.866f, 1.0f},   // point 8
    {1.0f, 1.732f, 1.0f},   // point 9
    {0.0f, 1.732f, 1.0f},   // point 10
    {-0.5f, 0.866f, 1.0f}   // point 11
};

static edge hexagonal_cuboid_edges[] = {
    // Bottom hexagon edges
    {0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 0},
    // Connect top and bottom hexagons
    {0, 6}, {1, 7}, {2, 8}, {3, 9}, {4, 10}, {5, 11},
    // Top hexagon edges
    {6, 7}, {7, 8}, {8, 9}, {9, 10}, {10, 11}, {11, 6}
};

static obj3d_t hexagonal_cuboid = {
		.points = hexagonal_cuboid_points,
		.point_len = sizeof(hexagonal_cuboid_points)/sizeof(point3d_t),
		.edges = hexagonal_cuboid_edges,
		.edge_len = sizeof(hexagonal_cuboid_edges)/sizeof(edge)
};




/*
static double Rx[3][3] = {{1,0,0},{0,cos(a),-sin(a)},{0,sin(a),cos(a)}};
static double Ry[3][3] = {{cos(a),0,sin(a)},{0,1,0},{-sin(a),0,cos(a)}};
static double Rz[3][3] = {{cos(a),-sin(a),0},{sin(a),cos(a),0},{0,0,1}};
*/

//windowsizex /2 +(Fov*point.x)/ (Fov+point.z) * 10
//windowsizey /2 +(Fov*point.y)/ (Fov+point.z) * 10

float deg2rad(float x);

uint8_t compare_points(point3d_t a, point3d_t b);

void rotate_x(point3d_t* point, float angle);
void rotate_y(point3d_t* point, float angle);
void rotate_z(point3d_t* point, float angle);

void rotate_obj(obj3d_t* obj, float angle_x, float angle_y, float angle_z);
void rotate_stl_obj(stl_obj* obj, float angle_x, float angle_y, float angle_z);

obj2d_t* allocProcjection(unsigned int no_vert, unsigned int no_edges);
stl_obj2d* allocStlProjection(stl_obj* stl);
point2d_t project(point3d_t point);

void render_stl_object(stl_obj* in_obj,stl_obj2d* out_obj);
void render_object(obj3d_t* in_obj,obj2d_t* out_obj);
float average_z(face_t face);
void normalize_vector(point3d_t* vec);

static float vector_length(point3d_t vec);
uint32_t adjust_luminosity(uint32_t color, float factor);

//void draw();
stl_obj* create_icosahedron(void);
void calculate_normal(face_t* face);
float dot_product(point3d_t vec1, point3d_t vec2);
int compare_faces(const void* a, const void* b);
void painterAlgorithm(stl_obj* in_obj, stl_obj2d* out_obj);

#endif /* 3D_ENGINE_3D_ENGINE_H_ */
