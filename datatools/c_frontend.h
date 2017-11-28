#ifndef C_FRONTEND_H
#define C_FRONTEND_H

#include "types.hpp"

void get_segmentation(
        size_t          sz,
        size_t          sy,
        size_t          sx,
        const float*    aff_data,
        uint32_t*       seg_data);

#endif
