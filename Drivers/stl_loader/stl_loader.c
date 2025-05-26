/*
 * stl_loader.c
 *
 *  Created on: 25 maj 2024
 *      Author: LENOVO
 */


#include "fatfs.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "3d_engine.h"



int load_stl(FIL* file, stl_obj* obj) {

    FRESULT res;
    UINT br;

    res = f_open(file, "test.stl", FA_READ);

    if(res != FR_OK){
    	return res;
    }

    f_lseek(file, 80); //skip the header

    uint32_t face_count=0;
    res=f_read(file, &face_count, sizeof(face_count), &br);
    if(res != FR_OK)
    	return res;
    face_t* faces = (face_t*)malloc(sizeof(face_t)*face_count);
    obj->noTriangles = face_count;
    if(face_count == 0)
    	return 1;

    //face_temp =
    //node_t* head = NULL;
    for(uint32_t i = 0; i<face_count; i++){

        faces[i].normal_v = (point3d_t*)malloc(sizeof(point3d_t));
        faces[i].p1 = (point3d_t*)malloc(sizeof(point3d_t));
        faces[i].p2 = (point3d_t*)malloc(sizeof(point3d_t));
        faces[i].p3 = (point3d_t*)malloc(sizeof(point3d_t));

        f_read(file, faces[i].normal_v, sizeof(float) * 3, &br);
        f_read(file, faces[i].p1, sizeof(float) * 3, &br);
        f_read(file, faces[i].p2, sizeof(float) * 3, &br);
        f_read(file, faces[i].p3, sizeof(float) * 3, &br);

        f_lseek(file, f_tell(file) + 2); //skip attr byte count
    }

    //malloc(sizeof)





    return 0;
}

void free_stl(stl_obj* obj) {
    if (obj->faces != NULL) {

    	for (size_t i = 0; i < obj->noTriangles; i++) {
    	        free(obj->faces[i].normal_v);
    	        free(obj->faces[i].p1);
    	        free(obj->faces[i].p2);
    	        free(obj->faces[i].p3);
    	    }


        free(obj->faces);

        free(obj);
    }
}

