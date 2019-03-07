#include "c_frontend.h"
#include "backend/get_segmentation.hpp"
#include "backend/dilate_segmentation.hpp"
#include "backend/create_border.hpp"
#include "backend/make_affinity.hpp"
#include "backend/merge_regions.hpp"

void get_segmentation(
		size_t        sz,
		size_t        sy,
		size_t        sx,
		const float*  aff_data,
		uint32_t*     seg_data,
        float         tz,
        float         ty,
        float         tx)
{
	// Wrap affinities (no copy).
	affinity_graph_const_ref<float> aff(aff_data, boost::extents[3][sz][sy][sx]);

	// Wrap segmentation array (no copy).
	volume_ref_ptr<uint32_t> seg(
			new volume_ref<uint32_t>(seg_data, boost::extents[sz][sy][sx]));

    backend::get_segmentation(aff, *seg, tz, ty, tx);
}

void dilate_segmentation(
		size_t        sz,
		size_t        sy,
		size_t        sx,
		uint32_t*     seg_data,
		uint32_t*     dst_data,
        uint32_t      k)
{
	// Wrap segmentation array (no copy).
	volume_ref_ptr<uint32_t> seg(
			new volume_ref<uint32_t>(seg_data, boost::extents[sz][sy][sx]));

    // Wrap distance array (no copy).
	volume_ref_ptr<uint32_t> dst(
			new volume_ref<uint32_t>(dst_data, boost::extents[sz][sy][sx]));

    backend::dilate_segmentation(*seg, *dst, k);
}

void create_border(
		size_t    sz,
		size_t    sy,
		size_t    sx,
		uint32_t* seg_data,
        uint32_t* out_data)
{
    // Wrap output array (no copy).
	volume_ref_ptr<uint32_t> seg(
			new volume_ref<uint32_t>(seg_data, boost::extents[sz][sy][sx]));

    // Wrap output array (no copy).
	volume_ref_ptr<uint32_t> out(
			new volume_ref<uint32_t>(out_data, boost::extents[sz][sy][sx]));

    backend::create_border(*seg, *out);
}

void make_affinity(
		size_t            sz,
		size_t            sy,
		size_t            sx,
		const uint32_t*   seg_data,
		float*            aff_data)
{
	// Wrap segmentation (no copy).
    volume_const_ref<uint32_t> seg(seg_data, boost::extents[sz][sy][sx]);

	// Wrap affinity array (no copy).
    affinity_graph_ref_ptr<float> aff(
        new affinity_graph_ref<float>(aff_data, boost::extents[3][sz][sy][sx]));

    backend::make_affinity(seg, *aff);
}

void merge_regions(
        size_t          sz,
        size_t          sy,
        size_t          sx,
        const uint32_t* rg_data,
        uint32_t*       seg_data
        const float*    dend_values,
        const uint32_t* dend_pairs,
        size_t          nedges,
        float           threshold)
{
    // Wrap segmentation (no copy).
    volume_const_ref<uint32_t> rg(rg_data, boost::extents[sz][sy][sx]);

    // Wrap region array (no copy).
	// volume_ref_ptr<uint32_t> rg(
	// 		new volume_ref<uint32_t>(rg_data, boost::extents[sz][sy][sx]));

    // Wrap segmentation array (no copy).
	volume_ref_ptr<uint32_t> seg(
			new volume_ref<uint32_t>(seg_data, boost::extents[sz][sy][sx]));

    backend::merge_regions(rg, seg, dend_values, dend_pairs, nedges, threshold);
}
