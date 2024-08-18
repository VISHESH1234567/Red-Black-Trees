#include <bits/stdc++.h>
#include <fstream>
using namespace std;
string lowercase(string word){
    for (int i=0;i<word.size();i++){
        if (word[i]>='A' and word[i]<='Z') word[i] = word[i]-'A'+'a';
    }
    return word;
}
class IndexEntry {
private:
    string word;
    vector<pair<string, int>> chapter_word_counts;  // List of (chapter, word_count) tuples

public:
    IndexEntry(string word_val) : word(word_val) {}

    void setWord(string word_val) {  // Set the word
        word = word_val;
    }

    string getWord() {  // Get the word
        return word;
    }

    void setChapterWordCounts(vector<pair<string, int>> chapter_word_counts_val) {  // Set the list of (chapter, word_count) tuples
        chapter_word_counts = chapter_word_counts_val;
    }

    vector<pair<string, int>> getChapterWordCounts() {  // Get the list of (chapter, word_count) tuples
        return chapter_word_counts;
    }
    void add_data(pair<string,int> name){
        chapter_word_counts.push_back(name);
    }
    void increase_count(string chname){
        for (int i=0;i<chapter_word_counts.size();i++){
            if (chapter_word_counts[i].first==chname){chapter_word_counts[i].second++;break;}
        }
    }
    bool allpresent(){
        for (int i=0;i<chapter_word_counts.size();i++){
            if (chapter_word_counts[i].second==0) return false;
        }
        return true;
    }
};
class HybridNode {
public:
    string key;     // Word
    string element;    // Chapter
    IndexEntry* indexentry;
    HybridNode* parent;   // Parent node
    HybridNode* left_child;  // Left child node
    HybridNode* right_child;  // Right child node
    HybridNode* next_node;  // Next node in the linked list
    string color = "black";    // Color of the node

    HybridNode(string key_val, string element_val){
        key = key_val; element = element_val; indexentry=nullptr;
        parent=nullptr; left_child=nullptr; right_child=nullptr; next_node=nullptr;
    }
};

class RedBlackTree {
private:
    HybridNode* root;   // Root node

    HybridNode* getuncle(HybridNode* child){
        if (child->parent->parent->right_child == child->parent) return child->parent->parent->left_child;
        return child->parent->parent->right_child;
    }
    
    int left_rotate(HybridNode* address){
        HybridNode* rightchild = address->right_child;
        HybridNode* parents = address->parent;
        address->right_child = rightchild->left_child;
        if (address->right_child!=nullptr){address->right_child->parent = address;}
        rightchild->left_child = address;
        address->parent = rightchild;

        rightchild->parent = parents;
        if (parents==nullptr){root = rightchild;}
        else if (parents->left_child==address){parents->left_child = rightchild;}
        else if (parents->right_child==address){parents->right_child = rightchild;}

        return 0;
    }
    int right_rotate(HybridNode* address){
        HybridNode* leftchild = address->left_child;
        HybridNode* parents = address->parent;
        address->left_child = leftchild->right_child;
        if (leftchild->right_child!=nullptr){leftchild->right_child->parent = address;}
        leftchild->right_child = address;
        address->parent = leftchild;

        if (parents==nullptr){root = leftchild;leftchild->parent = nullptr;}
        else if (parents->left_child==address){parents->left_child = leftchild;leftchild->parent = parents;}
        else if (parents->right_child==address){parents->right_child = leftchild;leftchild->parent = parents;}

        return 0;
    }

    int correct(HybridNode* address){
        if (address==nullptr) return 0;
        HybridNode* uncle;
        while (address->parent->color=="red"){
            uncle = getuncle(address);
            if (uncle!=nullptr and uncle->color=="red"){
                uncle->color="black";
                address->parent->color="black";
                address->parent->parent->color="red";
                address = address->parent->parent;
            }
            else{
                if (address->parent==address->parent->parent->left_child){
                    if (address==address->parent->right_child){
                        left_rotate(address->parent);
                        address = address->left_child;
                    }
                    right_rotate(address->parent->parent);

                    address->parent->color="black"; address->parent->right_child->color="red";address->parent->left_child->color="red";
                    break;
                }
                else{
                    if (address==address->parent->left_child){
                        right_rotate(address->parent);
                        address = address->right_child;
                    }
                    left_rotate(address->parent->parent);

                    address->parent->color="black"; address->parent->left_child->color = "red";address->parent->right_child->color="red";
                    break;
                }
            }
            if (address==root) break;
        }
        root->color="black";
        return 0;
    }
    int deletefix(HybridNode* dbparent,bool rights){
        while (dbparent!=nullptr){
            if (rights){
                if (dbparent->left_child->color=="red"){
                    dbparent->color = "red";
                    dbparent->left_child->color = "false";
                    right_rotate(dbparent);
                }
                else{
                    if ((dbparent->left_child->left_child==nullptr or dbparent->left_child->left_child->color=="black") and (dbparent->left_child->right_child==nullptr or dbparent->left_child->right_child->color=="black")){
                        dbparent->left_child->color = "red";
                        if (dbparent!=root and dbparent->parent->left_child==dbparent){rights = false;}
                        else if (dbparent!=root){rights = true;}
                        if (dbparent->color=="red"){dbparent->color="black"; return 0;}
                        dbparent = dbparent->parent;
                    }
                    else{
                        if (dbparent->left_child->left_child==nullptr or dbparent->left_child->left_child->color=="black"){
                            dbparent->left_child->color="red"; dbparent->left_child->right_child->color="black";
                            left_rotate(dbparent->left_child);
                        }
                        dbparent->left_child->color = dbparent->color;
                        dbparent->color="black";
                        dbparent->left_child->left_child->color="black";
                        right_rotate(dbparent);
                        dbparent = nullptr;
                    }
                }
            }
            else{
                if (dbparent->right_child->color=="red"){
                    dbparent->color="red";
                    dbparent->right_child->color="black";
                    left_rotate(dbparent);
                }
                else{
                    if ((dbparent->right_child->left_child==nullptr or dbparent->right_child->left_child->color=="black") and (dbparent->right_child->right_child==nullptr or dbparent->right_child->right_child->color=="black")){
                        dbparent->right_child->color="red";
                        if (dbparent!=root and dbparent->parent->left_child==dbparent){rights = false;}
                        else if (dbparent!=root){rights = true;}
                        if (dbparent->color=="red"){dbparent->color="black"; return 0;}
                        dbparent = dbparent->parent;
                    }
                    else{
                        if (dbparent->right_child->right_child==nullptr or dbparent->right_child->right_child->color=="black"){
                            dbparent->right_child->color="red"; dbparent->right_child->left_child->color="black";
                            right_rotate(dbparent->right_child);
                        }
                        dbparent->right_child->color = dbparent->color;;
                        dbparent->color="black";
                        dbparent->right_child->right_child->color="black";
                        left_rotate(dbparent);
                        dbparent = nullptr;
                    }
                }
            }
        }
        root->color="black";
        return 0;
    }

public:
    RedBlackTree() : root(nullptr) {}

    HybridNode* getRoot() {
        return root;  // Return the root node
    }

    void setRoot(HybridNode* node) {
        root = node;  // Set the root node
    }

    HybridNode* insert(string key, string element) {
        // Implement Red-Black Tree insertion
        if (root==nullptr){root = new HybridNode(key,element); return root;}
        HybridNode* temp = root;
        bool flag = true;
        while (flag){
            if (key>temp->key){
                if (temp->right_child==nullptr){
                    temp->right_child = new HybridNode(key,element);
                    temp->right_child->parent = temp; temp->right_child->color="red";
                    flag = false;
                }
                temp = temp->right_child;
            }   
            else if (key<temp->key){
                if (temp->left_child==nullptr){
                    temp->left_child = new HybridNode(key,element);
                    temp->left_child->parent = temp; temp->left_child->color="red";
                    flag = false;
                }
                temp = temp->left_child;
            }
            else{
                temp->indexentry->increase_count(element);
                return nullptr;
            }
        }
        correct(temp);
        return temp;
    }

    bool deleteNode(string key) {
        // Implement Red-Black Tree deletion
        HybridNode* temp = root;
        bool rights=true;
        while(temp!=nullptr){
            if (key>temp->key){
                temp = temp->right_child;
                rights = true;
            }
            else if (key<temp->key){
                temp = temp->left_child;
                rights = false;
            }
            else{
                if (temp->left_child==nullptr and temp->right_child==nullptr and temp->color=="red"){
                    if (rights){temp->parent->right_child=nullptr;}
                    else {temp->parent->left_child = nullptr;}
                    delete temp; return true;
                }
                if (temp->left_child==nullptr and temp->right_child==nullptr){
                    if (rights){temp->parent->right_child=nullptr;}
                    else{temp->parent->left_child=nullptr;}
                    HybridNode* p = temp->parent;
                    delete temp;
                    deletefix(p,rights); return true;
                }
                else if (temp->left_child==nullptr){
                    temp->key = temp->right_child->key;
                    temp->element = temp->right_child->element;
                    temp->indexentry = temp->right_child->indexentry;
                    delete temp->right_child;
                    temp->right_child = nullptr;
                    return true;
                }
                else if (temp->right_child==nullptr){
                    temp->key = temp->left_child->key;
                    temp->element = temp->left_child->element;
                    temp->indexentry = temp->left_child->indexentry;
                    delete temp->left_child;
                    temp->left_child = nullptr;
                    return true;
                }
                else{
                    HybridNode* temporary = temp->right_child;
                    while (temporary->left_child!=nullptr){
                        temporary = temporary->left_child;
                    }
                    temp->key = temporary->key;
                    temp->element = temporary->element;
                    temp->indexentry = temporary->indexentry;
                    if (temporary->right_child!=nullptr){
                        temporary->key = temporary->right_child->key;
                        temporary->element = temporary->right_child->element;
                        temporary->indexentry = temporary->right_child->indexentry;
                        delete temporary->right_child;
                        temporary->right_child = nullptr;
                        return true;
                    }
                    if (temporary->color=="red"){
                        HybridNode* p = temporary->parent;
                        delete temporary;
                        if (p==temp) p->right_child = nullptr;
                        else p->left_child = nullptr;
                        return true;
                    }
                    if (temporary->parent==temp){
                        temp->right_child = nullptr;
                        delete temporary;
                        deletefix(temp,true);
                    }
                    else{
                        temporary->parent->left_child = nullptr;
                        HybridNode* p = temporary->parent;
                        delete temporary;
                        deletefix(p,false);
                    }
                    return true;
                }
            }
        }
        return false;
    }

    vector<HybridNode*> traverseUp(HybridNode* node) {
        // Traverse up the tree from the given node to the root
        // Return the vector of nodes in the path
        vector<HybridNode*> output;
        HybridNode* temp = node;
        while (temp!=nullptr){
            output.push_back(temp);
            temp = temp->parent;
        }
        return output;
    }

    vector<HybridNode*> traverseDown(HybridNode* node, string bit_sequence) {
        // Traverse down the tree based on the bit sequence
        // Return the vector of nodes in the path
        vector<HybridNode*> output; 
        HybridNode* temp = node;
        for (int i=0;i<bit_sequence.size();i++){
            output.push_back(temp);
            if (bit_sequence[i]=='0') temp = temp->right_child;
            else temp = temp->left_child;
        }
        output.push_back(temp);
        return output;
    }
    vector<HybridNode*> preOrderTraversal(HybridNode* node, int depth) {
        // Perform pre-order traversal staying within specified depth
        if (depth==-1) return {};
        if (node==nullptr) return {};
        vector<HybridNode*> ans = {};
        ans.push_back(node);
        vector<HybridNode*> ans1;
        ans1 = preOrderTraversal(node->left_child,depth-1);
        ans.insert(ans.end(),ans1.begin(),ans1.end());
        ans1 = preOrderTraversal(node->right_child,depth-1);
        ans.insert(ans.end(),ans1.begin(),ans1.end());
        return ans;
    }
    HybridNode* search(string key) {
        // Implement Red-Black Tree search
        HybridNode* temp = root;
        while (temp!=nullptr){
            if (key>temp->key) temp = temp->right_child;
            else if (key<temp->key) temp = temp->left_child;
            else return temp;
        }
        return nullptr;
    }
    
    int blackheight(HybridNode* node){
        // Implement blackheight
        HybridNode* temp = node;
        int count=0;
        while (temp!=nullptr){
            if (temp->color=="black") count++;
            temp = temp->left_child;
        }
        return count;
    }

    vector<IndexEntry> inorder_index(HybridNode* node){
        if (node==nullptr) return {};
        vector<IndexEntry> output = inorder_index(node->left_child);
        output.push_back(*node->indexentry);
        vector<IndexEntry> output2 = inorder_index(node->right_child);
        output.insert(output.end(),output2.begin(),output2.end());
        return output;
    }

    vector<string> tobedeleted(HybridNode* node){
        if (node==nullptr) return {};
        vector<string> output;
        if (node->indexentry->allpresent()) output.push_back(node->key);
        vector<string> output2;
        output2 = tobedeleted(node->left_child);
        output.insert(output.end(),output2.begin(),output2.end());
        output2 = tobedeleted(node->right_child);
        output.insert(output.end(),output2.begin(),output2.end());
        return output;
    }
};

class Lexicon {
private:
    RedBlackTree red_black_tree; // Red-Black Tree

public:
    Lexicon() {}

    void setRedBlackTree(RedBlackTree tree) {  // Set the Red-Black Tree
        red_black_tree = tree;
    }

    RedBlackTree getRedBlackTree() {  // Get the Red-Black Tree
        return red_black_tree;
    }

    void readChapters(vector<string> chapter_names) {  
        // Process words from a chapter and update the Red-Black Tree
        // chapter_names is a vector of chapter names
        string chname,row,word;
        for (int i=0;i<chapter_names.size();i++){
            chapter_names[i] = chapter_names[i].substr(0,chapter_names[i].size()-4);
        } 
        for (int i=0;i<chapter_names.size();i++){
            chname = chapter_names[i];
            ifstream chapter(chname+".txt");
            if (chapter.is_open()){
                while (!chapter.eof()){
                    getline(chapter,row,'\n');
                    stringstream row2(row);
                    while (!row2.eof()){
                        getline(row2,word,' ');
                        word = lowercase(word);
                        HybridNode* output = red_black_tree.insert(word,chname);
                        if (output!=nullptr){
                            IndexEntry* newhist = new IndexEntry(word);
                            pair<string,int> value;
                            for (int i=0;i<chapter_names.size();i++){
                                value.first = chapter_names[i];
                                if (chapter_names[i]==chname) value.second = 1;
                                else value.second = 0;
                                newhist->add_data(value);
                            }
                            output->indexentry = newhist;
                        }
                    }
                }
            }
        }
        vector<string> deletedwords = red_black_tree.tobedeleted(red_black_tree.getRoot());
        for (int i=0;i<deletedwords.size();i++){
            red_black_tree.deleteNode(deletedwords[i]);
        }
    }

    vector<IndexEntry> buildIndex() {
        // Build the index using the remaining words in the Red-Black Tree
        vector<IndexEntry> output = red_black_tree.inorder_index(red_black_tree.getRoot());
        return output;
    }
};
