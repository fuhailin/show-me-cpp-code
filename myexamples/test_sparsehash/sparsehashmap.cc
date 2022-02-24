#include <algorithm>
#include <iostream>
#include <sparsehash/sparse_hash_map>
#include <string>

// A custom value type that has a default constructor
class MyValueType {
 public:
  // The usual boilerplate
  MyValueType() : _value("unknown") {}
  MyValueType(const MyValueType& other) : _value(other._value) {}
  MyValueType(const char* value) : _value(value) {}
  void operator=(const MyValueType& other) { _value = other._value; }
  const std::string asString() const { return _value; }

 private:
  std::string _value;
};

// Allow value type to be redirected to std::ostream
std::ostream& operator<<(std::ostream& o, const MyValueType& value) {
  o << value.asString();
  return o;
}

// A sparse_hash_map typedef, for convenience
typedef google::sparse_hash_map<std::string, MyValueType> MyHashMap;

int main() {
  MyHashMap my_hash_map;
  my_hash_map.set_deleted_key("");

  my_hash_map["roses"] = "red";

  // The other way to insert items, as with std::map
  const std::pair<MyHashMap::const_iterator, bool> result =
      my_hash_map.insert(std::make_pair("violets", "blue"));
  if (!result.second) {
    std::cout << "Failed to insert item into sparse_hash_map" << std::endl;
    return 1;
  }

  std::cout << "violets: " << result.first->second << std::endl;

  // The other way to retrieve values
  const MyHashMap::iterator itr = my_hash_map.find("violets");
  if (itr == my_hash_map.end()) {
    std::cout << "Failed to find item in sparse_hash_map" << std::endl;
    return 1;
  }

  // Fails if 'set_deleted_key()' has not been called
  my_hash_map.erase(itr);

  // Accessing values using [] is only permitted when the value type has a
  // default constructor. This line will not compile without one.
  const MyValueType& roses = my_hash_map["roses"];

  // Print output
  std::cout << "roses: " << roses << std::endl;
  std::cout << "violets: " << my_hash_map["violets"] << std::endl;

  return 0;
}