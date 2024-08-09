#include <iostream>
#include <string>
using namespace std;





class Trie {


    public:


        Trie prefix (const string& s, int k) {

            return i_prefix (root, s, k);


        }

        bool find_word (const string& s, int k) {

            return i_word (root, s, k);

        }

        bool isEmpty() {

            return root == nullptr;

        }

        void insert (const string& s) {

            i_insert (root, s, 0);

        }





    private:

        struct node {

            char info = '?';
            node* left = nullptr;
            node* right = nullptr;
            node* cen = nullptr;
            bool end = false;

        };


        node* root = nullptr;



        Trie i_prefix (node* p, const string& s, int i) {

            if (i == s.length()) {

                Trie t;
                t.root = p;
                return t;

            }

            if (p == nullptr) return Trie();

            if (p -> info == s[i]) return i_prefix (p -> cen, s, i+1);

            else {

                if (p -> info < s[i]) return i_prefix (p -> right, s, i);
                else return i_prefix (p -> left, s, i);

            }


        }

        bool i_word (node* p, const string& s, int i) {

            return i + 1 == s.length() and p != nullptr and p -> end; 

        }

        void i_insert (node*& p, const string& s, int i) {

            if (p == nullptr) {

                p = new node; 
                if (i < s.length()) p->info = s[i];
            }

            if (p -> info == '?') p->info = s[i];


            if (p -> info < s[i]) i_insert (p -> right, s, i);

            else if (p -> info > s[i]) i_insert (p -> left, s, i);

            else {

                if (i == s.length()) p -> end = true;

                else i_insert (p-> cen, s, i+1);

            }

        }

                    












        







};
