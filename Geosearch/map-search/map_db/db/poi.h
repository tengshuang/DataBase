#ifndef MAP_SEARCH_DB_POI_H_
#define MAP_SEARCH_DB_POI_H_

#include <string>

namespace map_search {
namespace db {


class POI {
 public:
  POI(std::string name, double lat, double lng, std::string addr);
  ~POI();

  std::string name_;
  double lat_;
  double lng_;
  std::string addr_;
};

}  // namespace db
}  // namespace map_search

#endif  // MAP_SEARCH_DB_POI_H_
