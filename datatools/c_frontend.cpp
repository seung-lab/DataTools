#include "c_frontend.h"
#include "backend/get_segmentation.hpp"

void get_segmentation(
		size_t        sz,
		size_t        sy,
		size_t        sx,
		const float*  aff_data,
		uint32_t*     seg_data)
{
	std::size_t n = sx*sy*sz;

	// Wrap affinities (no copy).
	affinity_graph_ref<float> aff(aff_data, boost::extents[3][sz][sy][sx]);

	// Wrap segmentation array (no copy).
	volume_ref_ptr<uint32_t> seg(
			new volume_ref<uint32_t>(seg_data, boost::extents[sz][sy][sx])
        );

    get_segmentation(aff, *seg);
}
