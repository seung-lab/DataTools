from libc.stdint cimport uint32_t

cimport numpy as np


def __get_segmentation(
        np.ndarray[np.float32_t, ndim=4] aff,
        np.ndarray[uint32_t,     ndim=3] seg,
        float tz, float ty, float tx):

    cdef float*    aff_data
    cdef uint32_t* seg_data

    aff_data = &aff[0,0,0,0]
    seg_data = &seg[0,0,0]

    get_segmentation(
            aff.shape[1],
            aff.shape[2],
            aff.shape[3],
            aff_data,
            seg_data,
            tz, ty, tx)

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


def __create_border(np.ndarray[uint32_t, ndim=3] seg,
                    np.ndarray[uint32_t, ndim=3] out):

    cdef uint32_t* seg_data
    cdef uint32_t* out_data

    seg_data = &seg[0,0,0]
    out_data = &out[0,0,0]

    create_border(
            seg.shape[0],
            seg.shape[1],
            seg.shape[2],
            seg_data,
            out_data)


def __make_affinity(
        np.ndarray[uint32_t,     ndim=3] seg,
        np.ndarray[np.float32_t, ndim=4] aff):

    cdef uint32_t* seg_data
    cdef float*    aff_data

    seg_data = &seg[0,0,0]
    aff_data = &aff[0,0,0,0]

    make_affinity(
            seg.shape[0],
            seg.shape[1],
            seg.shape[2],
            seg_data,
            aff_data)


def __merge_regions(
        np.ndarray[uint32_t,     ndim=3] rg,
        np.ndarray[uint32_t,     ndim=3] seg
        np.ndarray[np.float32_t, ndim=1] dend_values,
        np.ndarray[uint32_t,     ndim=1] dend_pairs,
        size_t nedges, float threshold):

    cdef uint32_t* rg_data
    cdef uint32_t* seg_data
    cdef float*    values_data
    cdef uint32_t* pairs_data

    rg_data = &rg[0,0,0]
    seg_data = &seg[0,0,0]
    values_data = &dend_values[0]
    pairs_data = &dend_pairs[0]

    merge_regions(
            seg.shape[0],
            seg.shape[1],
            seg.shape[2],
            rg_data,
            seg_data,
            values_data,
            pairs_data,
            nedges,
            threshold)



cdef extern from "c_frontend.h":

    void get_segmentation(
            size_t          sz,
            size_t          sy,
            size_t          sx,
            const float*    aff_data,
            uint32_t*       seg_data,
            float           tz,
            float           ty,
            float           tx);

    void dilate_segmentation(
            size_t          sz,
            size_t          sy,
            size_t          sx,
            uint32_t*       seg_data,
            uint32_t*       dst_data,
            uint32_t        k);

    void create_border(
            size_t          sz,
            size_t          sy,
            size_t          sx,
            uint32_t*       seg_data,
            uint32_t*       out_data);

    void make_affinity(
            size_t          sz,
            size_t          sy,
            size_t          sx,
            const uint32_t* seg_data,
            float*          aff_data);

    void merge_regions(
            size_t          sz,
            size_t          sy,
            size_t          sx,
            const uint32_t* rg_data,
            uint32_t*       seg_data,
            const float*    dend_values,
            const uint32_t* dend_pairs,
            size_t          nedges,
            float           threshold);
