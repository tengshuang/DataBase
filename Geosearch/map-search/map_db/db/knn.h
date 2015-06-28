#ifndef MAP_SEARCH_DB_KNN_H_
#define MAP_SEARCH_DB_KNN_H_

#include <queue>

#include "poi.h"


namespace map_search {
namespace db {
namespace knn {

// Naive algorithm.
// Assume poi_list is sorted by lat.
std::vector<POI> Naive(double lat, double lng,
                       const std::vector<POI>& poi_list,
                       unsigned neighbor_num);

}  // namespace knn
}  // namespace db
}  // namespace map_search

#endif  // MAP_SEARCH_DB_KNN_H_
