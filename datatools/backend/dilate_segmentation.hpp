//
// Copyright (C)      2017  Kisuk Lee           <kisuklee@mit.edu>
// ---------------------------------------------------------------
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
#pragma once

#include "types.hpp"

#include <limits>

template<typename V>
inline void
dilate_segmentation( V & seg, V & dst, typename V::element k )
{
    typedef typename V::element ID;

    size_t sz = seg.shape()[0];
    size_t sy = seg.shape()[1];
    size_t sx = seg.shape()[2];
    size_t n  = sx*sy*sz;

    for ( size_t z = 0; z < sz; ++z )
    {
        for ( size_t y = 0; y < sy; ++y )
        {
            for ( size_t x = 0; x < sx; ++x )
            {
                if ( seg[z][y][x] > 0 )
                    dst[z][y][x] = 0;
                else
                    dst[z][y][x] = std::numeric_limits<ID>::max();

                if ( x > 0 )
                {
                    if ( dst[z][y][x-1] + 1 <= dst[z][y][x] )
                    {
                        dst[z][y][x] = dst[z][y][x-1] + 1;
                        seg[z][y][x] = seg[z][y][x-1];
                    }
                }

                if ( y > 0 )
                {
                    if ( dst[z][y-1][x] + 1 <= dst[z][y][x] )
                    {
                        dst[z][y][x] = dst[z][y-1][x] + 1;
                        seg[z][y][x] = seg[z][y-1][x];
                    }
                }
            }
        }
    }

    for ( size_t dz = 0, z = sz - 1; dz < sz; ++dz, --z )
    {
        for ( size_t dy = 0, y = sy - 1; dy < sy; ++dy, --y )
        {
            for ( size_t dx = 0, x = sx - 1; dx < sx; ++dx, --x )
            {
                if ( x < sx - 1 )
                {
                    if ( dst[z][y][x+1] + 1 <= dst[z][y][x] )
                    {
                        dst[z][y][x] = dst[z][y][x+1] + 1;
                        seg[z][y][x] = seg[z][y][x+1];
                    }
                }

                if ( y < sy - 1 )
                {
                    if ( dst[z][y+1][x] + 1 <= dst[z][y][x] )
                    {
                        dst[z][y][x] = dst[z][y+1][x] + 1;
                        seg[z][y][x] = seg[z][y+1][x];
                    }
                }
            }
        }
    }

    for ( size_t i = 0; i < n; ++i )
    {
        if ( dst.data()[i] > k )
            seg.data()[i] = 0;
    }
}
