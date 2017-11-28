import numpy as np

from _frontend import __get_segmentation

def get_segmentation(aff):

    # The C++ part assumes contiguous memory, make sure we have it.
    if not aff.flags['C_CONTIGUOUS']:
        print("Creating memory-contiguous affinity arrray (avoid this by passing C_CONTIGUOUS arrays)")
        aff = np.ascontiguousarray(aff)

    vol_shape = (aff.shape[1], aff.shape[2], aff.shape[3])
    seg = np.zeros(vol_shape, dtype=np.uint32)

    __get_segmentation(aff, seg)

    return seg
