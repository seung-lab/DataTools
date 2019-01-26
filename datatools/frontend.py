import numpy as np

from ._frontend import __get_segmentation, __dilate_segmentation, __create_border, __make_affinity


def ascontiguousarray(a):
    # The C++ part assumes contiguous memory, make sure we have it.
    if not a.flags['C_CONTIGUOUS']:
        # print("Creating memory-contiguous affinity arrray.")
        a = np.ascontiguousarray(a)
    return a


def get_segmentation(aff, threshold=(0.5,0.5,0.5)):
    aff = ascontiguousarray(aff)
    vol_shape = (aff.shape[1], aff.shape[2], aff.shape[3])
    seg = np.zeros(vol_shape, dtype=np.uint32)

    if np.isscalar(threshold):
        threshold = [threshold]*3

    __get_segmentation(aff, seg, *threshold)

    return seg


def dilate_segmentation(seg, k=10):
    seg = ascontiguousarray(seg)
    seg = np.copy(seg)
    dst = np.zeros_like(seg, dtype=np.uint32)

    __dilate_segmentation(seg, dst, k)

    return seg, dst


def create_border(seg):
    seg = ascontiguousarray(seg)
    out = np.copy(seg)

    __create_border(seg, out)

    return out


def make_affinity(seg):
    seg = ascontiguousarray(seg)
    aff_shape = (3, seg.shape[0], seg.shape[1], seg.shape[2])
    aff = np.zeros(aff_shape, dtype=np.float32)

    __make_affinity(seg, aff)

    return aff
