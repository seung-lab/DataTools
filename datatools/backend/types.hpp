#pragma once

#include <boost/multi_array.hpp>
#include <boost/multi_array/types.hpp>

#include <memory>
#include <vector>
#include <tuple>

typedef std::size_t size_t;

template <typename T>
using volume = boost::multi_array<T,3>;

template <typename T>
using volume_ref = boost::multi_array_ref<T,3>;

template <typename T>
using volume_const_ref = boost::const_multi_array_ref<T,3>;

template <typename T>
using volume_ptr = std::shared_ptr<volume<T>>;

template <typename T>
using volume_ref_ptr = std::shared_ptr<volume_ref<T>>;

template <typename T>
using volume_const_ref_ptr = std::shared_ptr<volume_const_ref<T>>;

template <typename T>
using affinity_graph = boost::multi_array<T,4>;

template <typename T>
using affinity_graph_ref = boost::const_multi_array_ref<T,4>;

template <typename T>
using affinity_graph_ptr = std::shared_ptr<affinity_graph<T>>;

template <typename T>
using affinity_graph_ref_ptr = std::shared_ptr<affinity_graph_ref<T>>;
