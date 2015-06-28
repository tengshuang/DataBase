#include "kit.h"

#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "json/json.h"
#include "trie.h"
#include "knn.h"

namespace map_search {
namespace db {

std::vector<POI> poi_list;
Trie trie;

int poi_compare(const POI& a, const POI& b) {
  return a.lat_ < b.lat_;
}

std::vector<std::string> GetKeywords(const std::string& input) {
  std::vector<std::string> keywords;
  std::string keyword;
  for (std::string::const_iterator ch = input.begin(); ch != input.end();
       ++ch) {
    int char_mapped = MapChar(*ch);
    if (char_mapped == kInvalidChar) {
      if (!keyword.empty()) {
        keywords.push_back(keyword);
        keyword.clear();
      }
    } else {
      keyword.push_back(*ch);
    }
  }
  if (!keyword.empty())
    keywords.push_back(keyword);
  return keywords;
}

bool ReadJson(char* file_name) {
  std::ifstream fin(file_name);
  std::string str;

  poi_list.clear();
  trie.Clear();

  std::cout << "***********Reading json from*******" << file_name << "...\n";
  while (getline(fin, str)) {
    std::stringstream stream(str);
    Json::Reader reader;
    Json::Value root;
    if (!reader.parse(stream, root, false)) {
      continue;
    }

    std::string name = root["name"].asString();
    Json::Value pos = root["latlng"];
    double lat = pos[(Json::Value::UInt)0].asDouble();
    double lng = pos[(Json::Value::UInt)1].asDouble();
    std::string addr = root["addr"].asString();
    poi_list.push_back(POI(name, lat, lng, addr));
  }
  fin.close();
  std::cout << "*************Read finished.*************\n";

  sort(poi_list.begin(), poi_list.end(), poi_compare);

  std::cout << "****************Building trie...************\n";
  for (unsigned poi_index = 0; poi_index < poi_list.size(); ++poi_index) {
    std::string& name = poi_list[poi_index].name_;
    std::vector<std::string> keywords = GetKeywords(name);
    for (std::vector<std::string>::iterator iter = keywords.begin();
         iter != keywords.end(); ++iter) {
      trie.Push(*iter, poi_index);
    }
  }
  std::cout << "******************Build finished. Size of trie is " << trie.Size() << "***********\n";
  return true;
}

// Intersection of 2 sorted list.
std::vector<unsigned> IntersectRefs(const std::vector<unsigned>& refs_a,
                                const std::vector<unsigned>& refs_b) {
  std::vector<unsigned> refs;
  unsigned index_a = 0;
  unsigned index_b = 0;
  while (index_a < refs_a.size() && index_b < refs_b.size()) {
    if (refs_a[index_a] == refs_b[index_b]) {
      refs.push_back(refs_a[index_a]);
      ++index_a;
      ++index_b;
    } else if (refs_a[index_a] < refs_b[index_b]) {
      ++index_a;
    } else {
      ++index_b;
    }
  }
  return refs;
}

double cached_lat;
double cached_lng;
unsigned cached_num;
std::string cached_input;
std::vector<POI> cached_pois;

std::vector<std::string> cached_keywords;
std::vector<std::vector<unsigned> > cached_refss;

std::vector<POI> Search(double lat, double lng, const std::string& input,
                        unsigned num) {
  if (lat == cached_lat && lng == cached_lng && input == cached_input &&
      num == cached_num)
    return cached_pois;
  cached_input = input;

  // Find the first position that different.
  std::vector<std::string> keywords = GetKeywords(input);
  unsigned index = 0;
  for (index = 0; index < keywords.size() &&
       index < cached_keywords.size(); ++index) {
    if (keywords[index] != cached_keywords[index])
      break;
  }

  if (keywords.size() == cached_keywords.size() && index == keywords.size()) {
    // Same keywords, no needs to update refs.
    if (lat == cached_lat && lng == cached_lng && num == cached_num)
      return cached_pois;

    cached_lat = lat;
    cached_lng = lng;
    cached_num = num;
  } else {
    cached_lat = lat;
    cached_lng = lng;
    cached_num = num;

    for (int tmp_index = (int)cached_keywords.size()-1; tmp_index >= (int)index;
         --tmp_index) {
      cached_keywords.pop_back();
      cached_refss.pop_back();
    }
    if (cached_refss.size() > 0 && cached_refss.back().size() == 0) {
      return cached_pois;
    }

    for (unsigned tmp_index = index; tmp_index < keywords.size(); ++tmp_index) {
      cached_keywords.push_back(keywords[tmp_index]);
      const std::vector<unsigned>* refs = trie.GetRefs(keywords[tmp_index]);
      if (refs == NULL) {
        cached_refss.push_back(std::vector<unsigned>());
        cached_pois = std::vector<POI>();
        return cached_pois;
      }
      if (cached_refss.size() == 0)
        cached_refss.push_back(*refs);
      else
        cached_refss.push_back(IntersectRefs(cached_refss.back(), *refs));
    }
  }

  const std::vector<unsigned>& u_refs = cached_refss.back();
  std::cout << "Matched " << u_refs.size() << " entries.\n";

  std::vector<POI> matched_poi_list;
  for (unsigned index = 0; index < u_refs.size(); ++index)
    matched_poi_list.push_back(poi_list.at(u_refs[index]));
  cached_pois = knn::Naive(lat, lng, matched_poi_list, num);
  return cached_pois;
}

}  // namespace db
}  // namespace map_search
