from libc.stdint cimport uint32_t

cimport numpy as np


def __get_segmentation(
        np.ndarray[np.float32_t, ndim=4] aff,
        np.ndarray[uint32_t,     ndim=3] seg):

    cdef float*    aff_data
    cdef uint32_t* seg_data

    aff_data = &aff[0,0,0,0]
    seg_data = &seg[0,0,0]

    get_segmentation(
            aff.shape[1],
            aff.shape[2],
            aff.shape[3],
            aff_data,
            seg_data)

def __dilate_segmentation(
        np.ndarray[uint32_t, ndim=3] seg,
        np.ndarray[uint32_t, ndim=3] dst,
        uint32_t k):

    cdef uint32_t* seg_data
    cdef uint32_t* dst_data

    seg_data = &seg[0,0,0]
    dst_data = &dst[0,0,0]

    dilate_segmentation(
            seg.shape[0],
            seg.shape[1],
            seg.shape[2],
            seg_data,
            dst_data,
            k)


cdef extern from "c_frontend.h":

    void get_segmentation(
            size_t          sz,
            size_t          sy,
            size_t          sx,
            const float*    aff_data,
            uint32_t*       seg_data);

    void dilate_segmentation(
            size_t          sz,
            size_t          sy,
            size_t          sx,
            uint32_t*       seg_data,
            uint32_t*       dst_data,
            uint32_t        k);
