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

template<typename V>
inline void
create_border( V & seg )
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
            size_t j0 = (y > 0)    ? y-1 : y;
            size_t j1 = (y < sy-1) ? y+1 : y;

            for ( size_t x = 0; x < sx; ++x )
            {
                ID id1 = seg[z][y][x];

                if ( id1 > 0 )
                {
                    size_t i0 = (x > 0)    ? x-1 : x;
                    size_t i1 = (x < sx-1) ? x+1 : x;

                    bool is_border = false;
                    for ( size_t j = j0; j <= j1 ; ++j )
                    {
                        for ( size_t i = i0; i <= i1 ; ++i )
                        {
                            ID id2 = seg[z][j][i];
                            if ( id2 > 0 && id1 != id2 )
                            {
                                is_border = true;
                                break;
                            }
                        }
                        if ( is_border ) break;
                    }

                    if ( is_border )
                        seg[z][y][x] = 0;
                }
            }
        }
    }
}
