import numpy as np

from _frontend import __get_segmentation, __dilate_segmentation


def ascontiguousarray(a):
    # The C++ part assumes contiguous memory, make sure we have it.
    if not a.flags['C_CONTIGUOUS']:
        print("Creating memory-contiguous affinity arrray.")
        a = np.ascontiguousarray(a)
    return a


def get_segmentation(aff):
    aff = ascontiguousarray(aff)
    vol_shape = (aff.shape[1], aff.shape[2], aff.shape[3])
    seg = np.zeros(vol_shape, dtype=np.uint32)

    __get_segmentation(aff, seg)

    return seg


def dilate_segmentation(seg, k=10):
    seg = ascontiguousarray(seg)
    seg = np.copy(seg)
    dst = np.zeros_like(seg, dtype=np.uint32)

    __dilate_segmentation(seg, dst, k)

    return ret
