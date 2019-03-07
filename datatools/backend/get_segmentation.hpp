//
// Copyright (C) 2012-2017  Aleksandar Zlateski <zlateski@mit.edu>
//               2015-2017  Kisuk Lee           <kisuklee@mit.edu>
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

#include <boost/pending/disjoint_sets.hpp>

namespace backend {

template< typename AG, typename V >
inline void
get_segmentation( AG const & aff,
                  V & seg,
                  float tz = 0.5,
                  float ty = 0.5,
                  float tx = 0.5 )
{
    size_t sz = aff.shape()[1];
    size_t sy = aff.shape()[2];
    size_t sx = aff.shape()[3];
    size_t n  = sx*sy*sz;

    std::vector<uint32_t> p(n+1);
    std::vector<uint8_t>  r(n+1);
    for ( size_t i = 0; i < n+1; ++i )
    {
        p[i] = i;
        r[i] = 0;
    }
    boost::disjoint_sets<uint8_t*,uint32_t*> sets(&r[0], &p[0]);
    std::vector<uint32_t>                    sizes(n+1);

    for ( size_t i = 0; i < n; ++i )
    {
        seg.data()[i] = i+1;
        sizes[i+1] = 1;
    }

    typedef std::pair<uint32_t,uint32_t> edge_type;
    std::vector<edge_type> edges;

    // Thresholded affinity graph.
    for ( size_t z = 0; z < sz; ++z )
    {
        for ( size_t y = 0; y < sy; ++y )
        {
            for ( size_t x = 0; x < sx; ++x )
            {
                long id1 = seg[z][y][x];

                if ( x > 0 )
                {
                    // Skip disconnected (black) edges.
                    // Only count connected (white) edges.
                    if ( aff[0][z][y][x] > tx )
                    {
                        long id2 = seg[z][y][x-1];
                        edges.push_back(edge_type(id1, id2));
                    }
                }

                if ( y > 0 )
                {
                    // Skip disconnected (black) edges.
                    // Only count connected (white) edges.
                    if ( aff[1][z][y][x] > ty )
                    {
                        long id2 = seg[z][y-1][x];
                        edges.push_back(edge_type(id1, id2));
                    }
                }

                if ( z > 0 )
                {
                    // Skip disconnected (black) edges.
                    // Only count connected (white) edges.
                    if ( aff[2][z][y][x] > tz )
                    {
                        long id2 = seg[z-1][y][x];
                        edges.push_back(edge_type(id1, id2));
                    }
                }
            }
        }
    }

    // Connected components of the thresholded affinity graph.
    // Compute the size of each connected component.
    for ( auto& e: edges )
    {
        uint32_t set1 = sets.find_set(e.first);
        uint32_t set2 = sets.find_set(e.second);

        if ( set1 != set2 )
        {
            sets.link(set1, set2);
            uint32_t new_set = sets.find_set(set1);

            sizes[set1] += sizes[set2];
            sizes[set2]  = 0;

            std::swap(sizes[new_set], sizes[set1]);
        }
    }

    std::vector<uint32_t> remaps(n+1);

    uint32_t next_id = 1;

    // Assign a unique segment ID to each of
    // the pixel in a connected component.
    for ( size_t i = 0; i < n; ++i )
    {
        uint32_t id = sets.find_set(seg.data()[i]);
        if ( sizes[id] > 1 )
        {
            if ( remaps[id] == 0 )
            {
                remaps[id]    = next_id;
                seg.data()[i] = next_id;
                ++next_id;
            }
            else
            {
                seg.data()[i] = remaps[id];
            }
        }
        else
        {
            remaps[id]    = 0;
            seg.data()[i] = 0;
        }
    }
}

} // namespace backend
