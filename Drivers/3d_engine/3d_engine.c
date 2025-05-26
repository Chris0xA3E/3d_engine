/*
 * 3d_engine.c
 *
 *  Created on: Apr 14, 2024
 *      Author: master
 */


#include "3d_engine.h"


float deg2rad(float x){
	return x*(M_PI/180.0);
}

uint8_t compare_points(point3d_t a, point3d_t b){
	if(a.x!=b.x)
		return 1;
	if(a.y!=b.y)
		return 1;
	if(a.z!=b.z)
		return 1;
	return 0;
}

node_t* createNode(point3d_t* key){
	node_t* newNode = (node_t*)malloc(sizeof(node_t));
	newNode->point=key;
	newNode->next = NULL;
	return newNode;
}

node_t* push(node_t* head,point3d_t* key){
	node_t * new = createNode(key);

	if(new==NULL){
		//printf("ERROR ALLOCATING MEMORY\n");
		return head;
	}
	if(head == NULL)
		return new;
	new->next=head;
	return new;
}

node_t* pop(node_t* head){
	node_t * temp = head->next;
	head->next = NULL;
	free(head); /// specjalnie not freed point
	return temp;
}


node_t* search(node_t* head, point3d_t *x)
{
    node_t * current = head; // Initialize current
    while (current != NULL) {
        if (compare_points(*(current->point),*x) == 0)
            return current;
        current = current->next;
    }
    return NULL;
}


void rotate_x(point3d_t* point, float angle){
    float y = point->y;
    float z = point->z;
	point->x = point->x;
	point->y = y * cos(angle) - z * sin(angle);
	point->z = y * sin(angle) + z * cos(angle);
}


void rotate_y(point3d_t* point, float angle){
	float x = point->x;
	float z = point->z;
	point->x = x * cos(angle) + z * sin(angle);
	point->y = point->y;
	point->z = -x * sin(angle) + z * cos(angle);
}

void rotate_z(point3d_t* point, float angle){
	float x = point->x;
	float y = point->y;
	point->x = x * cos(angle) - y * sin(angle);
	point->y = x * sin(angle) + y * cos(angle);
	point->z = point->z;
}

//windowsizex /2 +(Fov*point.x)/ (Fov+point.z) * 10
//windowsizey /2 +(Fov*point.y)/ (Fov+point.z) * 10
point2d_t project(point3d_t point){
	point2d_t result;
	result.x = (uint16_t)(ScreenWidth/2 + (FOV*point.x)/(FOV+point.z)*PROJECTION_SCALE);
	result.y = (uint16_t)(ScreenHight/2 + (FOV*point.y)/(FOV+point.z)*PROJECTION_SCALE);
	return result;
}

obj2d_t* allocProcjection(unsigned int no_vert, unsigned int no_edges){
	obj2d_t* newObj = (obj2d_t*)malloc(sizeof(obj2d_t));
	newObj->points = (point2d_t*)malloc(sizeof(point2d_t)*no_vert);
	newObj->point_len = no_vert;
	newObj->edges = (edge*)malloc(sizeof(edge)*no_edges);
	newObj->edge_len = no_edges;

	return newObj;
}

//stl_obj2d* allocStlProjection(stl_obj* stl){
//	stl_obj2d* newObj=(stl_obj2d*)malloc(sizeof(stl_obj));
//	newObj->faces = (face2d_t*)malloc(sizeof(face2d_t)*stl->noTriangles);
//	newObj->noTriangles = stl->noTriangles;
//	return newObj;
//
//}
static float vector_length(point3d_t vec) {
    return sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}


stl_obj2d* allocStlProjection(stl_obj* stl) {
    stl_obj2d* newObj = (stl_obj2d*)malloc(sizeof(stl_obj2d)); // Allocate correct structure size
    if (newObj == NULL) return NULL;

    newObj->faces = (face2d_t*)malloc(sizeof(face2d_t) * stl->noTriangles);
    if (newObj->faces == NULL) {
        free(newObj);
        return NULL;
    }

    for (uint32_t i = 0; i < stl->noTriangles; i++) {
        newObj->faces[i].p1 = (point2d_t*)malloc(sizeof(point2d_t));
        newObj->faces[i].p2 = (point2d_t*)malloc(sizeof(point2d_t));
        newObj->faces[i].p3 = (point2d_t*)malloc(sizeof(point2d_t));
        newObj->faces[i].normal_v = (point3d_t*)malloc(sizeof(point3d_t)); // Ensure normal vector is allocated
    }

    newObj->noTriangles = stl->noTriangles;
    return newObj;
}

void rotate_obj(obj3d_t* obj, float angle_x, float angle_y, float angle_z){
	for(size_t i=0; i<obj->point_len; i++){
		rotate_x(&obj->points[i],angle_x);
		rotate_y(&obj->points[i],angle_y);
		rotate_z(&obj->points[i],angle_z);
	}
}
void rotate_stl_obj(stl_obj* obj, float angle_x, float angle_y, float angle_z) {
    for (size_t i = 0; i < obj->noTriangles; i++) {
        // Rotate the normal vector
        rotate_x(obj->faces[i].normal_v, angle_x);
        rotate_y(obj->faces[i].normal_v, angle_y);
        rotate_z(obj->faces[i].normal_v, angle_z);

        // Rotate each vertex of the triangle
        rotate_x(obj->faces[i].p1, angle_x);
        rotate_y(obj->faces[i].p1, angle_y);
        rotate_z(obj->faces[i].p1, angle_z);

        rotate_x(obj->faces[i].p2, angle_x);
        rotate_y(obj->faces[i].p2, angle_y);
        rotate_z(obj->faces[i].p2, angle_z);

        rotate_x(obj->faces[i].p3, angle_x);
        rotate_y(obj->faces[i].p3, angle_y);
        rotate_z(obj->faces[i].p3, angle_z);
    }
}


void render_object(obj3d_t* in_obj,obj2d_t* out_obj){
	for(int i=0; i<in_obj->point_len; i++){
		out_obj->points[i]=project(in_obj->points[i]);
	}
	out_obj->point_len = in_obj->point_len;
	out_obj->edges = in_obj->edges;
	out_obj->edge_len = in_obj->edge_len;

	return;
}

float dot_product(point3d_t vec1, point3d_t vec2) {
    return (vec1.x * vec2.x) + (vec1.y * vec2.y) + (vec1.z * vec2.z);
}

//void render_stl_object(stl_obj* in_obj,stl_obj2d* out_obj){
//	out_obj->noTriangles = in_obj->noTriangles;
//	for(uint32_t i = 0; i < in_obj->noTriangles; i++){
//		*(out_obj->faces[i].normal_v)=(*(in_obj->faces[i].normal_v));
//		*(out_obj->faces[i].p1)=project(*(in_obj->faces[i].p1));
//		*(out_obj->faces[i].p2)=project(*(in_obj->faces[i].p2));
//		*(out_obj->faces[i].p3)=project(*(in_obj->faces[i].p3));
//	}
//	return;
//}

//void render_stl_object(stl_obj* in_obj, stl_obj2d* out_obj) {
//    out_obj->noTriangles = in_obj->noTriangles;
//    for (uint32_t i = 0; i < in_obj->noTriangles; i++) {
//        out_obj->faces[i].normal_v = in_obj->faces[i].normal_v;
//        *out_obj->faces[i].p1 = project(*(in_obj->faces[i].p1));
//        *out_obj->faces[i].p2 = project(*(in_obj->faces[i].p2));
//        *out_obj->faces[i].p3 = project(*(in_obj->faces[i].p3));
//    }
//}
void render_stl_object(stl_obj* in_obj, stl_obj2d* out_obj) {
    out_obj->noTriangles = in_obj->noTriangles;
    for (uint32_t i = 0; i < in_obj->noTriangles; i++) {
        *(out_obj->faces[i].normal_v) = *(in_obj->faces[i].normal_v); // Copy normal vector
        *(out_obj->faces[i].p1) = project(*(in_obj->faces[i].p1)); // Project and assign the result
        *(out_obj->faces[i].p2) = project(*(in_obj->faces[i].p2)); // Project and assign the result
        *(out_obj->faces[i].p3) = project(*(in_obj->faces[i].p3)); // Project and assign the result
    }
}

void calculate_normal(face_t* face) {
    float u_x = face->p2->x - face->p1->x;
    float u_y = face->p2->y - face->p1->y;
    float u_z = face->p2->z - face->p1->z;

    float v_x = face->p3->x - face->p1->x;
    float v_y = face->p3->y - face->p1->y;
    float v_z = face->p3->z - face->p1->z;

    face->normal_v->x = u_y * v_z - u_z * v_y;
    face->normal_v->y = u_z * v_x - u_x * v_z;
    face->normal_v->z = u_x * v_y - u_y * v_x;

    float length = sqrt(face->normal_v->x * face->normal_v->x + face->normal_v->y * face->normal_v->y + face->normal_v->z * face->normal_v->z);
    if (length > 0) {
    	face->normal_v->x /= length;
    	face->normal_v->y /= length;
    	face->normal_v->z /= length;
    }
}

stl_obj* create_icosahedron(void) {
    // Golden ratio
    const float phi = (1 + sqrt(5)) / 2;

    // Normalizing factor
    const float a = 1 / sqrt(1 + phi * phi);

    // Vertices of an icosahedron
    point3d_t vertices[12] = {
        {-a, phi * a, 0}, {a, phi * a, 0}, {-a, -phi * a, 0}, {a, -phi * a, 0},
        {0, -a, phi * a}, {0, a, phi * a}, {0, -a, -phi * a}, {0, a, -phi * a},
        {phi * a, 0, -a}, {phi * a, 0, a}, {-phi * a, 0, -a}, {-phi * a, 0, a}
    };

    // Indices of the vertices that form the 20 triangular faces
    uint32_t faces_indices[20][3] = {
        {0, 11, 5}, {0, 5, 1}, {0, 1, 7}, {0, 7, 10}, {0, 10, 11},
        {1, 5, 9}, {5, 11, 4}, {11, 10, 2}, {10, 7, 6}, {7, 1, 8},
        {3, 9, 4}, {3, 4, 2}, {3, 2, 6}, {3, 6, 8}, {3, 8, 9},
        {4, 9, 5}, {2, 4, 11}, {6, 2, 10}, {8, 6, 7}, {9, 8, 1}
    };

    // Allocate memory for the STL object
    stl_obj* icosahedron = (stl_obj*)malloc(sizeof(stl_obj));
    if (!icosahedron) {
        return NULL;
    }

    // Allocate memory for the faces
    icosahedron->faces = (face_t*)malloc(20 * sizeof(face_t));
    if (!icosahedron->faces) {

        free(icosahedron);
        return NULL;
    }

    icosahedron->noTriangles = 20;

    // Allocate and assign memory for each face and its vertices
    for (uint32_t i = 0; i < 20; i++) {
        face_t* face = &icosahedron->faces[i];

        face->normal_v = (point3d_t*)malloc(sizeof(point3d_t));
        face->p1 = (point3d_t*)malloc(sizeof(point3d_t));
        face->p2 = (point3d_t*)malloc(sizeof(point3d_t));
        face->p3 = (point3d_t*)malloc(sizeof(point3d_t));

        if (!face->normal_v || !face->p1 || !face->p2 || !face->p3) {

            // Free previously allocated memory
            for (uint32_t j = 0; j <= i; j++) {
                free(icosahedron->faces[j].normal_v);
                free(icosahedron->faces[j].p1);
                free(icosahedron->faces[j].p2);
                free(icosahedron->faces[j].p3);
            }
            free(icosahedron->faces);
            free(icosahedron);
            return NULL;
        }

        face->normal_v->x = face->normal_v->y = face->normal_v->z = 0.0f;  // Setting normal vector to zero for simplicity

        *face->p1 = vertices[faces_indices[i][0]];
        *face->p2 = vertices[faces_indices[i][1]];
        *face->p3 = vertices[faces_indices[i][2]];
    }

    return icosahedron;
}


uint32_t adjust_luminosity(uint32_t color, float factor) {

    uint8_t a = (color >> 24) & 0xFF;
    uint8_t r = (color >> 16) & 0xFF;
    uint8_t g = (color >> 8) & 0xFF;
    uint8_t b = color & 0xFF;


    r = (uint8_t)(r * factor);
    g = (uint8_t)(g * factor);
    b = (uint8_t)(b * factor);

    uint32_t new_color = (a << 24) | (r << 16) | (g << 8) | b;

    return new_color;
}

float average_z(face_t face) {
    return (face.p1->z + face.p2->z + face.p3->z) / 3.0f;
}
int compare_faces(const void* a, const void* b) {
    face2d_with_z_t* faceA = (face2d_with_z_t*)a;
    face2d_with_z_t* faceB = (face2d_with_z_t*)b;
    if (faceA->average_z < faceB->average_z) return 1; // Sort in descending order
    if (faceA->average_z > faceB->average_z) return -1;
    return 0;
}

void painterAlgorithm(stl_obj* in_obj, stl_obj2d* out_obj) {
    uint32_t num_faces = in_obj->noTriangles;
    face2d_with_z_t* faces_with_z = (face2d_with_z_t*)malloc(sizeof(face2d_with_z_t) * num_faces);

    // Create array with faces and their average z
    for (uint32_t i = 0; i < num_faces; i++) {
        faces_with_z[i].face2d = &out_obj->faces[i];
        faces_with_z[i].average_z = average_z(in_obj->faces[i]);
    }

    // Sort the array based on the average z values
    qsort(faces_with_z, num_faces, sizeof(face2d_with_z_t), compare_faces);

    // Reorder out_obj->faces according to the sorted order
    face2d_t* sorted_faces = (face2d_t*)malloc(sizeof(face2d_t) * num_faces);
    for (uint32_t i = 0; i < num_faces; i++) {
        sorted_faces[i] = *faces_with_z[i].face2d;
    }
    for (uint32_t i = 0; i < num_faces; i++) {
        out_obj->faces[i] = sorted_faces[i];
    }

    free(faces_with_z);
    free(sorted_faces);
}
//void draw();

// Function to normalize a vector
void normalize_vector(point3d_t* vec) {
    float length = vector_length(*vec);

    if (length != 0) { // Prevent division by zero
        vec->x /= length;
        vec->y /= length;
        vec->z /= length;
    }
}







