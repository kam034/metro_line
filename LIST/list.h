#ifndef METRO_LINE_LIST_H
#define METRO_LINE_LIST_H
#include <iostream>

namespace templateClass {

    template<class T>
    class List {

        struct Node {
            T value;
            Node *next;

            explicit Node(T val) : value(val), next(nullptr) {};
        };

    private:
        Node *head;
        Node *tail;

    public:

        //класс итератор
        class Iterator {
            friend class List<T>;
        private:
            List<T>* list;
            Node* node;

        public:
            Iterator() : list(nullptr), node(nullptr) {};
            Iterator(List<T>* list_x, Node* node_x) : list(list_x), node(node_x) {};

            T& operator*() { return node->value; };

            bool operator == (const Iterator& iterator) const {
                return list == iterator.list && node == iterator.node;
            }

            bool operator != (const Iterator& iterator) const {
                return !operator==(iterator);
            }

            Iterator& operator ++() {
                if (node)
                    node = node->next;
                return *this;
            }

            Iterator operator ++(int) {
                if (!node)
                    return *this;
                Iterator res(list, node);
                node = node->next;
                return res;
            }
        };


        //методы класса List
        bool is_empty() { return head == nullptr; };

        Iterator begin() { return Iterator(this, head); };
        Iterator end() { return Iterator(this, tail->next); };

        List &push_back(T val) {
            Node* p = new Node(val);
            if (is_empty()) {
                head = p;
                tail = p;
                return *this;
            }
            tail->next = p;
            tail = p;
            return *this;
        }

        List &erase(Iterator iterator) {
            if (this->is_empty())
                return *this;
            Node* p = head;
            if (p == iterator.node) {
                head = p->next;
                delete p;
                if (head == nullptr)
                    tail = nullptr;

                return *this;
            }
            while (p) {
                if (p->next == iterator.node) {
                    Node* del = p->next;
                    p->next = p->next->next;
                    delete del;
                }
                else
                    p = p->next;
            }
            return *this;
        };

        friend std::ostream& operator<<(std::ostream &out, List<T> &list) {
            if (list.is_empty())
                return out;
            for (auto &n: list) {
                out << n << " -> ";
            }
            out << std::endl;
            return out;
        }

        ~List() {
            Node* p = head;
            while(p) {
                head = p;
                p = p->next;
                delete head;
            }
        }

    };

}
#endif //METRO_LINE_LIST_H
