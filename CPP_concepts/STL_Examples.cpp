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
    // std::vector is a dynamic array that provides fast random access, 
    // efficient memory allocation, and amortized constant-time insertions at the end.
	/*
	Use Case:
	* Use when you need a resizable array with fast random access and 
	primarily need to insert/remove elements at the end.
	* Best for storing data that needs to be accessed in a
       	linear fashion (sequential iteration).
	*/
    std::vector<int> vec = {1, 2, 3};
    vec.push_back(4); // Insertion
    vec.erase(vec.begin()); // Deletion
    std::cout << "Vector: ";
    for (int val : vec) std::cout << val << " ";
    std::cout << std::endl;

    // 2. Deque
    // std::deque is a container that allows fast insertion and deletion at both ends but
    // slower random access compared to std::vector
    /* Use cases:
       * Best for scenarios where you need efficient insertion/removal at both ends(queue or stack)
       * Suitable for implementing queues, double-ended queues, or when you need to perform operations
         at both ends frequently
    */
    std::deque<int> dq = {1, 2, 3};
    dq.push_front(0); // Insertion
    dq.pop_back(); // Deletion
    std::cout << "Deque: ";
    for (int val : dq) std::cout << val << " ";
    std::cout << std::endl;

    // 3. List
    // std::list is a doubly linked list that allows fast insertions and deletions at any position,
    // but it ahs slower random access than std::vector
    /* Use cases:
       * Use when you need efficient insertion and deletion at arbitrary positions(especially in middle)
       * Best for applications where elements are frequently inserted or deleted at arbitrary positions.
     */
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
    // std::set is a balanced binary tree(RedBlack Tree) that stores unique elements in sorted order
    // and provides logarithmic time complexity for search, insert, and delete operations.
    /* Use case:
       * Use when you need a collection of unique elements and need fast search, insert, and delete
       * Suitable for maintaining a sorted collection of items with no duplicates
     */
    std::set<int> s = {1, 2, 3};
    s.insert(4); // Insertion
    s.erase(2); // Deletion
    std::cout << "Set: ";
    for (int val : s) std::cout << val << " ";
    std::cout << std::endl;

    // 6. Unordered Set
    // std::unordered_set is implemented using a hash table and provides average constant time 
    // complexity for insert, search and delete operations
    /* Use case:
       * Use when you need a collection of unique elements and need fast insertion and searching,
         but the order of elements doesn't matter.
       * Suitable when quick lookups are needed without ordering constraints.
     */
    std::unordered_set<int> us = {1, 2, 3};
    us.insert(4); // Insertion
    us.erase(2); // Deletion
    std::cout << "Unordered Set: ";
    for (int val : us) std::cout << val << " ";
    std::cout << std::endl;

    // 7. Map (sorted key-value pairs)
    // std::map is a balanced binary tree but stores key-value pairs where the keys are unique.
    // it provides logarithmic time complexity for operations like insert, find, and delete.
    /* Use case:
       * Use when you need to map unique keys to values and want fast access to the elements based 
         on keys
       * Suitable for dictionary like data structures.
     */
    std::map<int, std::string> mp = {{1, "one"}, {2, "two"}, {3, "three"}};
    mp[4] = "four"; // Insertion
    mp.erase(2); // Deletion
    std::cout << "Map: ";
    for (const auto& [key, value] : mp) std::cout << "{" << key << ", " << value << "} ";
    std::cout << std::endl;

    // 8. Unordered Map
    // std::unordered_map is similar to std::map but uses a hash table to store key-value pairs, 
    // providing average constant time complexity for search, insert and delete operations.
    /* Use case:
       * Use when you need fast lookup of key-value pairs and dont care about the order
       * Suitable for implementing hash tables or associative arrays where performance is critical
     */
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

