#include<iostream>
#include<map>
#include<deque>
#include<algorithm>
using namespace std;
// input
map<char, float> chart = {
    {'a', 0.1},
    {'b', 0.2},
    {'c',0.25},
    {'d',0.25},
    {'e',0.05},
    {'f',0.15}
};

class node{
    //float key; // probability
    int code;
    public:
        node *left;
        node *right;
        char symbol;
        float key;
        node(char s, float k){
            symbol = s;
            key = k;
            left= NULL;
            right = NULL;
        }
};
map<node *,int> forest;
node *ptr;
node *root;
void init(){
    for(map<char, float>:: iterator it = chart.begin(); it != chart.end(); it++){
        ptr = new node(it->first, it->second);
        forest[ptr];
    }
}
void printForest(map<node *,int> &forest){
    for(map<node *,int>::iterator it = forest.begin(); it != forest.end(); it++){
        cout << (it->first)->symbol << ' ';
    }
    cout << endl;
}
node *getMin(map<node *,int> &forest){
    node* min = forest.begin()->first;
    for(map<node *,int>::iterator it = forest.begin(); it != forest.end(); it++){
        if(it->first->key < min->key){
            min = it->first;
        }
    }
    return min;
}
void combine(node *min1, node * min2, map<node *,int> &forest){
    node *new_node = new node((min1->symbol + min2->symbol),(min1->key + min2->key));
    new_node->left = min1;
    new_node->right = min2;
    forest[new_node];
    root = new_node;
}
void printHuffmanTree(node *root){
    if(root){
        if(!root->left && !root->right)
            cout << root->symbol << ' ';
        printHuffmanTree(root->left);
        printHuffmanTree(root->right);
    }
}
void constructHuffmanTree(){
    node *min1;
    node *min2;
    int l = forest.size();
    while(--l > 0){
        min1 = getMin(forest);
        forest.erase(min1);
        min2 = getMin(forest);
        forest.erase(min2);
        combine(min1, min2, forest);
    }
}
int main(){
    init();
    printForest(forest);
    cout << "----------------------------" << endl;
    constructHuffmanTree();
    printHuffmanTree(root);
    cout << endl;
    return 0;
}