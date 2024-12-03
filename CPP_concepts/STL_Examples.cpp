#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <queue>
#include <array>
#include <bitset>
#include <algorithm>

void demonstrateSTLContainers() {
    // 1. Vector
    std::vector<int> vec = {1, 2, 3};
    vec.push_back(4); // Insertion
    vec.erase(vec.begin()); // Deletion
    std::cout << "Vector: ";
    for (int val : vec) std::cout << val << " ";
    std::cout << std::endl;

    // 2. Deque
    std::deque<int> dq = {1, 2, 3};
    dq.push_front(0); // Insertion
    dq.pop_back(); // Deletion
    std::cout << "Deque: ";
    for (int val : dq) std::cout << val << " ";
    std::cout << std::endl;

    // 3. List
    std::list<int> lst = {1, 2, 3};
    lst.push_back(4); // Insertion
    lst.remove(2); // Deletion
    std::cout << "List: ";
    for (int val : lst) std::cout << val << " ";
    std::cout << std::endl;

    // 4. Forward List
    std::forward_list<int> flst = {1, 2, 3};
    flst.push_front(0); // Insertion
    flst.remove(2); // Deletion
    std::cout << "Forward List: ";
    for (int val : flst) std::cout << val << " ";
    std::cout << std::endl;

    // 5. Set
    std::set<int> s = {1, 2, 3};
    s.insert(4); // Insertion
    s.erase(2); // Deletion
    std::cout << "Set: ";
    for (int val : s) std::cout << val << " ";
    std::cout << std::endl;

    // 6. Unordered Set
    std::unordered_set<int> us = {1, 2, 3};
    us.insert(4); // Insertion
    us.erase(2); // Deletion
    std::cout << "Unordered Set: ";
    for (int val : us) std::cout << val << " ";
    std::cout << std::endl;

    // 7. Map
    std::map<int, std::string> mp = {{1, "one"}, {2, "two"}, {3, "three"}};
    mp[4] = "four"; // Insertion
    mp.erase(2); // Deletion
    std::cout << "Map: ";
    for (const auto& [key, value] : mp) std::cout << "{" << key << ", " << value << "} ";
    std::cout << std::endl;

    // 8. Unordered Map
    std::unordered_map<int, std::string> ump = {{1, "one"}, {2, "two"}, {3, "three"}};
    ump[4] = "four"; // Insertion
    ump.erase(2); // Deletion
    std::cout << "Unordered Map: ";
    for (const auto& [key, value] : ump) std::cout << "{" << key << ", " << value << "} ";
    std::cout << std::endl;

    // 9. Stack
    std::stack<int> stk;
    stk.push(1); stk.push(2); stk.push(3); // Insertion
    stk.pop(); // Deletion
    std::cout << "Stack (top): " << stk.top() << std::endl;

    // 10. Queue
    std::queue<int> que;
    que.push(1); que.push(2); que.push(3); // Insertion
    que.pop(); // Deletion
    std::cout << "Queue (front): " << que.front() << std::endl;

    // 11. Priority Queue
    std::priority_queue<int> pq;
    pq.push(1); pq.push(5); pq.push(3); // Insertion
    pq.pop(); // Deletion
    std::cout << "Priority Queue (top): " << pq.top() << std::endl;

    // 12. Array
    std::array<int, 4> arr = {1, 2, 3, 4};
    std::cout << "Array: ";
    for (int val : arr) std::cout << val << " ";
    std::cout << std::endl;

    // 13. Bitset
    std::bitset<8> bs(42); // 42 in binary
    bs.set(1); // Set bit 1
    bs.reset(3); // Reset bit 3
    std::cout << "Bitset: " << bs << std::endl;
   
    // Multi containers 
    // cannot use the [] operator with std::multimap or std::unordered_multimap to access
    // 1. Multiset
    std::multiset<int> mset = {1, 2, 2, 3};
    mset.insert(2); // Insertion of duplicate value
    mset.erase(mset.find(2)); // Delete one instance of 2
    std::cout << "Multiset: ";
    for (int val : mset) std::cout << val << " ";
    std::cout << std::endl;

    // 2. Multimap
    std::multimap<int, std::string> mmap = {{1, "one"}, {2, "two"}, {2, "duplicate two"}, {3, "three"}};
    mmap.insert({2, "another two"}); // Insert duplicate key
    auto range = mmap.equal_range(2); // Get range of duplicates for key 2
    std::cout << "Multimap: ";
    for (auto it = range.first; it != range.second; ++it) {
        std::cout << "{" << it->first << ", " << it->second << "} ";
    }
    std::cout << std::endl;

    // 3. Unordered Multiset
    std::unordered_multiset<int> umset = {1, 2, 2, 3};
    umset.insert(2); // Insertion of duplicate value
    umset.erase(umset.find(2)); // Delete one instance of 2
    std::cout << "Unordered Multiset: ";
    for (int val : umset) std::cout << val << " ";
    std::cout << std::endl;

    // 4. Unordered Multimap
    std::unordered_multimap<int, std::string> ummap = {{1, "one"}, {2, "two"}, {2, "duplicate two"}, {3, "three"}};
    ummap.insert({2, "another two"}); // Insert duplicate key
    std::cout << "Unordered Multimap: ";
    for (const auto& [key, value] : ummap) {
        std::cout << "{" << key << ", " << value << "} ";
    }
    std::cout << std::endl;
}

int main() {
    demonstrateSTLContainers();
    return 0;
}

