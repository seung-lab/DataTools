//
// Copyright (C) 2012-2019  Aleksandar Zlateski <zlateski@mit.edu>
//                          Kisuk Lee           <kisuklee@mit.edu>
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

#include <vector>

#include <boost/pending/disjoint_sets.hpp>

#include "types.hpp"

namespace backend {

template< typename V, typename F >
inline void
merge_regions( V const & seg,
               V & out,
               const F * dend_values,
               const typename V::element * dend_pairs,
               size_t nedges,
               F threshold)
{
    typedef typename V::element ID;

    // Find the largest ID in segmentation
    ID max_segid = seg[0];
    size_t sz = seg.shape()[0];
    size_t sy = seg.shape()[1];
    size_t sx = seg.shape()[2];
    size_t n = sx*sy*sz;
    for ( size_t i = 1; i < n; ++i )
    {
        if ( seg[i] > max_segid )
            max_segid = seg[i];
    }

    // Intitialize disjoint set
    std::vector<ID>       p(max_segid+1);
    std::vector<uint8_t>  r(max_segid+1);
    for ( ID i = 0; i < max_segid+1; ++i )
    {
        p[i] = i;
        r[i] = 0;
    }
    boost::disjoint_sets<uint8_t*,ID*> sets(&r[0],&p[0]);

    // Merging
    for ( size_t i = 0; i < nedges; ++i )
    {
        if ( dend_values[i] < threshold )
        {
            break;
        }

        ID s1 = sets.find_set(dend_pairs[2*i]);
        ID s2 = sets.find_set(dend_pairs[2*i+1]);

        if ( s1 != s2 && s1 && s2 )
        {
            sets.link(s1,s2);
            uint32_t s = sets.find_set(s1);
        }
    }

    // Remapping
    std::vector<ID> remaps(max_segid+1);

    ID next_id = 1;

    for ( ID id = 0; id < max_segid+1; ++id )
    {
        ID s = sets.find_set(id);
        if ( s && (remaps[s] == 0) )
        {
            remaps[s] = next_id++;
        }
    }

    for ( std::ptrdiff_t idx = 0; idx < n; ++idx )
    {
        out[idx] = remaps[sets.find_set(seg[idx])];
    }
}

} // namespace backend
