#ifndef MAP_SEARCH_DB_KIT_H_
#define MAP_SEARCH_DB_KIT_H_

#include <vector>

#include "poi.h"


namespace map_search {
namespace db {

// Read POIs from file in json format.
bool ReadJson(char* file_name);

std::vector<POI> Search(double lat, double lng, const std::string& input,
                        unsigned num);

}  // namespace db
}  // namespace map_search

#endif  // MAP_SEARCH_DB_KIT_H_
