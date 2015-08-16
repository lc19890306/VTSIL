#ifndef H5_CMPRSS_H
#define H5_CMPRSS_H

#include "H5Cpp.h"

#include <iostream>
#include <string>

#ifndef H5_NO_NAMESPACE
using namespace H5;
#ifndef H5_NO_STD
using std::cout;
using std::endl;
#endif  // H5_NO_STD
#endif

/* typedef struct { */
/*   unsigned index; */
/*   H5std_string name; */
/* } attr_info_t; */

/* void */
/* file_info(H5Location &loc_id, const H5std_string name, void *opdata) { */
/*   attr_info_t *info = (attr_info_t *)opdata; */

/*   info->name = name; */
/*   cout << "Name : " << name << endl; */
/*   /\* return (void *)0; *\/ */
/* } */

#endif	/* H5_CMPRSS_H */
