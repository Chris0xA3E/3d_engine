/*
 * stl_loader.h
 *
 *  Created on: 25 maj 2024
 *      Author: LENOVO
 */

#ifndef STL_LOADER_STL_LOADER_H_
#define STL_LOADER_STL_LOADER_H_

int load_stl(FIL* file, stl_obj* obj);
void free_stl(stl_obj* obj);

#endif /* STL_LOADER_STL_LOADER_H_ */
