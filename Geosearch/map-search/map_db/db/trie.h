#ifndef MAP_SEARCH_DB_TRIE_H_
#define MAP_SEARCH_DB_TRIE_H_

#include <vector>
#include <string>

namespace map_search {
namespace db {


const int kInvalidChar = -1;

// Map 'a'..'z' to 0..25, 'A'..'Z' to 0..25, '0'..'9' to 26..35,
// others to kInvalidChar.
int MapChar(char c);

const unsigned kChildNum = 37;
const int kInvalidNodeRef = -1;

const int kTrieNodesCapacity = 21000;

// Since store data refs in each node in trie, it is no needs to cache.
class Trie {
 public:
  class TrieNode {
   public:
    TrieNode();
    ~TrieNode();

    int GetChild(unsigned c) const;
    bool AddChild(unsigned c, int child_ref);

    void AddDataRef(unsigned ref);
    const std::vector<unsigned>* GetDataRefs() const;

   private:
    int child_[kChildNum];
    std::vector<unsigned> data_refs_;
  };

  Trie();
  ~Trie();

  bool Push(const std::string& str, unsigned ref);
  const std::vector<unsigned>* GetRefs(const std::string& str);

  unsigned Size();

  void Clear();

 private:
  std::vector<TrieNode> nodes_;
};

}  // namespace db
}  // namespace map_search

#endif  // MAP_SEARCH_DB_TRIE_H_
