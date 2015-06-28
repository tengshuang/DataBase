#include "poi.h"

namespace map_search {
namespace db {

POI::POI(std::string name, double lat, double lng, std::string addr)
  : name_(name), lat_(lat), lng_(lng), addr_(addr) {}

POI::~POI() {}

}  // namespace db
}  // namespace map_search

