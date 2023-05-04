#include <iostream>
#include <unordered_map>


namespace union_find {
    
    class Node {
    public:
        int x;
        int rank;
        Node* p;
    };

    class DisjointSet {
    public:
        DisjointSet() {}
        DisjointSet(DisjointSet& other) = delete;
        ~DisjointSet() {
            for (auto i : sets) {
                auto tmp = i.second;
                delete tmp;
                i.second = nullptr;
            }
        }
        // make sets
        void make_set(int key) {
            if (sets.find(key) != sets.end()) {
                throw std::exception("key already exisits");
            }
            Node *tmp = new Node{ key, 0, nullptr };
            tmp->p = tmp;
            sets.insert({ key, tmp });
        }
        // performs path compression along the way to the parent node
        Node* find_set(int key) {
            try {
                auto x = sets.at(key);
                if (x != x->p) {
                    x->p = find_set(x->p->x);
                }
                return x->p;
            }
            catch (std::exception e) {
                return nullptr;
            }
        }
        // union by rank
        void make_union(int k1, int k2) {
            auto s1 = find_set(k1);
            auto s2 = find_set(k2);
            if (s1 == nullptr || s2 == nullptr) {
                throw std::exception("make_union -> key not found\n");
            }
            if (s1->p == s2->p) {
                return;
            }
            if (s1->rank > s2->rank) {
                s2->p = s1;
            }
            else {
                s1->p = s2;
                if (s1->rank == s2->rank) {
                    s2->rank += 1;
                }
            }
        }

        int belongs_to(int key) {
            auto _p = find_set(key);
            while (_p->p->x != _p->x) _p = _p->p;
            return _p->x;
        }

        int set_size() {
            int count = 0;
            for (auto i : sets) count++;
            return count;
        }
        // debug
        void _show_sets()  {
            for (auto i : sets) {
                std::cout << "val->" << i.first 
                    << " parent->" << belongs_to(i.first) << " rank->" << i.second->rank << std::endl;
            }
        }
    private:
        std::unordered_map<int, Node*> sets;
    };
}