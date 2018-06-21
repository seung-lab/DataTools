//
// Copyright (C) 2015-2018  Kisuk Lee           <kisuklee@mit.edu>
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

template<typename V, typename AG>
inline void
make_affinity( V const & seg, AG & aff )
{
    size_t sz = seg.shape()[0];
    size_t sy = seg.shape()[1];
    size_t sx = seg.shape()[2];
    size_t n  = sx*sy*sz;

    float zero = static_cast<float>(0);
    float one  = static_cast<float>(1);

    for ( size_t z = 0; z < sz; ++z )
        for ( size_t y = 0; y < sy; ++y )
            for ( size_t x = 0; x < sx; ++x )
            {
                aff[0][z][y][x] = zero;
                aff[1][z][y][x] = zero;
                aff[2][z][y][x] = zero;

                uint32_t id = seg[z][y][x];

                if ( x > 0 && id > 0 )
                {
                    if ( id == seg[z][y][x-1] )
                        aff[0][z][y][x] = one;
                }

                if ( y > 0 && id > 0 )
                {
                    if ( id == seg[z][y-1][x] )
                        aff[1][z][y][x] = one;
                }

                if ( z > 0 && id > 0 )
                {
                    if ( id == seg[z-1][y][x] )
                        aff[2][z][y][x] = one;
                }
            }
}
