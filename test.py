#!/usr/bin/env python
from dataprovider import emio
from dataprovider import transform as tf
from datatools import *

import h5py
import numpy as np
import os
import time

if __name__ == "__main__":

    # Temp.
    seg_dir = '~/Data_local/datasets/SNEMI3D/data/crop_x512_y512_z100'
    seg = os.path.join(os.path.expanduser(seg_dir), 'train_segb.h5')

    # Load data.
    print "Load segmentation..."
    seg = emio.imread(seg)

    # Affinitize.
    t0 = time.time()

    dsts = list()
    dsts.append((0,0,1))
    dsts.append((0,1,0))
    dsts.append((1,0,0))

    affs = list()
    for dst in dsts:
        affs.append(tf.affinitize(seg, dst=dst))
    aff = np.concatenate(affs, axis=0)

    elapsed = time.time() - t0
    print "affinitize: %.3f" % elapsed

    # Recompute connected components.
    t0 = time.time()
    reseg = get_segmentation(aff)
    elapsed = time.time() - t0
    print "get_segmentation: %.3f" % elapsed

    # Save output.
    fname = 'reseg.h5'
    if os.path.exists(fname):
        os.remove(fname)
    f = h5py.File(fname)
    f.create_dataset('/main', data=reseg)
    f.close()
