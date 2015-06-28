#include "knn.h"

#include <algorithm>

namespace map_search {
namespace db {
namespace knn {

double dist(double x1, double y1, double x2, double y2) {
  return (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
}

double abs(double x) {
  return x > 0 ? x : -x;
}
double sqr(double x) {
  return x * x;
}


class POIComparison {
 public:
  POIComparison(double lat, double lng)
      : lat_(lat), lng_(lng) {}

  bool operator() (const POI& lhs, const POI& rhs) const {
    return dist(lhs.lat_, lhs.lng_, lat_, lng_) <
      dist(rhs.lat_, rhs.lng_, lat_, lng_);
  }

 private:
  double lat_;
  double lng_;
};

std::vector<POI> Naive(double lat, double lng,
                       const std::vector<POI>& poi_list,
                       unsigned neighbor_num) {
  if (poi_list.size() == 0)
    return std::vector<POI>();
  if (poi_list.size() <= neighbor_num) {
    std::vector<POI> new_poi_list(poi_list);
    std::sort(new_poi_list.begin(), new_poi_list.end(), POIComparison(lat,
          lng));
    return poi_list;
  }

  int l = 0;
  int r = poi_list.size() - 1;
  while (l < r) {
    int mid = (l + r + 1) >> 1;
    if (poi_list[mid].lat_ < lat)
      l = mid;
    else
      r = mid - 1;
  }
  r = l + 1;

  std::priority_queue<POI, std::vector<POI>, POIComparison> neighbor(
      POIComparison(lat, lng));
  while (l >= 0 || r < (int)poi_list.size()) {
    int t;
    if (r == (int)poi_list.size() ||
        (l >= 0 && abs(poi_list[l].lat_ - lat) < abs(poi_list[r].lat_ - lat)))
      t = l--;
    else
      t = r++;
    if (neighbor.size() < neighbor_num) {
      neighbor.push(poi_list[t]);
    } else {
      const POI& top = neighbor.top();
      if (sqr(abs(poi_list[t].lat_ - lat)) >= dist(top.lat_, top.lng_, lat, lng)) {
        break;
      }
      neighbor.push(poi_list[t]);
      neighbor.pop();
    }
  }

  std::vector<POI> to_vector;
  while (!neighbor.empty()) {
    to_vector.push_back(neighbor.top());
    neighbor.pop();
  }
  std::vector<POI> to_reverse;
  for (std::vector<POI>::reverse_iterator iter = to_vector.rbegin();
       iter != to_vector.rend(); ++iter)
    to_reverse.push_back(*iter);
  return to_reverse;
}

}  // namespace knn
}  // namespace db
}  // namespace map_search
