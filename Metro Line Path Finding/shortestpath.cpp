#include <iostream>
#include <vector>
#include <string>
#include<bits/stdc++.h>
#include <fstream>
using namespace std;

// Forward declarations
class MetroStop;
class MetroLine;
class AVLNode;

// MetroStop class
class MetroStop{
private:
    std::string stopName;
    MetroStop* nextStop;
    MetroStop* prevStop;
    MetroLine* line;
    int fare;

public:
    MetroStop(std::string name, MetroLine* metroLine, int fares){
    	stopName = name; fare = fares; line = metroLine;
    	nextStop = nullptr; prevStop = nullptr;
    }
    // Getter methods
    std::string getStopName() const{
    	return stopName;
    }
    MetroStop* getNextStop() const{
    	return nextStop;
    }
    MetroStop* getPrevStop() const{
    	return prevStop;
    }
    MetroLine* getLine() const{
    	return line;
    }
    int getFare() const{
    	return fare;
    }
    // Setter methods
    void setNextStop(MetroStop* next){
    	nextStop = next;
    }
    void setPrevStop(MetroStop* prev){
    	prevStop = prev;
    }
};

// MetroLine class
class MetroLine {
private:
    std::string lineName;
    MetroStop* node;

public:
    MetroLine(std::string name){
    	lineName = name; node = nullptr;
    }
    // Getter methods
    std::string getLineName() const{
    	return lineName;
    }
    MetroStop* getNode() const{
    	return node;
    }
    // Setter methods
    void setNode(MetroStop* nodes){
    	node = nodes;
    }

    void populateLine(std::string filename){
    	ifstream new_file(filename);
    	if (new_file.is_open()){
    		while (!new_file.eof()){
    			string row;
	    		getline(new_file,row,'\n');
                if (row[row.length()-1]==',') row = row.substr(0,row.length()-1);
                if (row[row.length()-1]==',') row = row.substr(0,row.length()-1);
	    		int index = row.length()-1;
	    		int fare = 0; int count = 1;
	    		while (row[index]>='0' && row[index]<='9'){
	    			fare+=count*(row[index]-'0'); count*=10;
	    			index--;
	    		}
	    		string name = row.substr(0,index);
	    		MetroStop* tempnode = new MetroStop(name,this,fare);
	    		tempnode->setNextStop(node);
	    		if (node!=nullptr) node->setPrevStop(tempnode);
	    		node = tempnode;
    		}
    		new_file.close();
    	}
    }
    // helper function
    void printLine() const{
    	MetroStop* stop = node;
	    while (stop != nullptr) {
	        cout << stop->getStopName() << endl;
	        stop = stop->getNextStop();
	    }
    }
    int getTotalStops() const{
    	MetroStop* stop = node; int count = 0;
    	while (stop!=nullptr){
    		count++; stop = stop->getNextStop();
    	}
    	return count;
    }
};

// AVLNode class
class AVLNode {
private:
    std::string stopName;
    std::vector<MetroStop*> stops;
    AVLNode* left;
    AVLNode* right;
    AVLNode* parent;

public:
    AVLNode(std::string name){
    	stopName = name; left = nullptr; right = nullptr; parent = nullptr;
    }
    // Getter methods
    std::string getStopName() const{
    	return stopName;
    }
    const std::vector<MetroStop*>& getStops() const{
    	return stops;
    }
    AVLNode* getLeft() const{
    	return left;
    }
    AVLNode* getRight() const{
    	return right;
    }
    AVLNode* getParent() const{
    	return parent;
    }
    // Setter methods
    void addMetroStop(MetroStop* metroStop){
    	stops.push_back(metroStop);
    }
    void setLeft(AVLNode* lefts){
    	left = lefts;
    }
    void setRight(AVLNode* rights){
    	right = rights;
    }
    void setParent(AVLNode* parents){
    	parent = parents;
    }
};

// AVLTree class
class AVLTree {
private:
    AVLNode* root;

public:
    AVLTree(){
        root = nullptr;
    }
    // getter methods
    AVLNode* getRoot() const{
    	return root;
    }

    // setter methods
    void setRoot(AVLNode* roots){
    	root = roots;
    }

    // helper functions
    int height(AVLNode* node){
    	if (node==nullptr) return 0;
    	if (node->getLeft()==nullptr && node->getRight()==nullptr) return 0;
    	int a = height(node->getLeft());
    	int b = height(node->getRight());
    	if (a>=b) return 1+a;
    	return 1+b;
    }
    int balanceFactor(AVLNode* node){
    	int a = height(node->getLeft());
    	int b = height(node->getRight());
    	if (a>b) return a-b;
    	return b-a;
    }
    void rotateLeft(AVLNode* node){
    	AVLNode* rightchild = node->getRight();
		AVLNode* parents = node->getParent();
		node->setRight(rightchild->getLeft());
		if (node->getRight()!=nullptr){node->getRight()->setParent(node);}
		rightchild->setLeft(node);
		node->setParent(rightchild);

		rightchild->setParent(parents);
		if (parents==nullptr){root = rightchild;}
		else if (parents->getLeft()==node){parents->setLeft(rightchild);}
		else if (parents->getRight()==node){parents->setRight(rightchild);}
    }
    void rotateRight(AVLNode* node){
    	AVLNode* leftchild = node->getLeft();
		AVLNode* parents = node->getParent();
		node->setLeft(leftchild->getRight());
		if (node->getLeft()!=nullptr){node->getLeft()->setParent(node);}
		leftchild->setRight(node);
		node->setParent(leftchild);

		leftchild->setParent(parents);
		if (parents==nullptr){root = leftchild;}
		else if (parents->getLeft()==node){parents->setLeft(leftchild);}
		else if (parents->getRight()==node){parents->setRight(leftchild);}
    }
    void balance(AVLNode* node){
    	AVLNode* grandparent = node->getParent()->getParent();
    	bool rights1=false,rights2=false;
    	if (node->getParent()->getRight()==node) rights1 = true;
    	if (node->getParent()!=root && grandparent->getRight()==node->getParent()) rights2 = true;
    	while (1){
    		if (grandparent==nullptr) return;
    		if (balanceFactor(grandparent)<=1){
    			rights1 = rights2;
    			if (grandparent->getParent()!=nullptr && grandparent->getParent()->getRight()==grandparent) rights2 = true;
                else rights2 = false;
    			grandparent = grandparent->getParent();
    		}
    		else{
    			if (rights2){
    				if (!rights1) rotateRight(grandparent->getRight());
    				rotateLeft(grandparent);
    			}
    			else{
    				if (rights1) rotateLeft(grandparent->getLeft());
    				rotateRight(grandparent);
    			}
                return;
    		}
    	}
    }
    int stringCompare(string s1, string s2){
    	char *c1 = new char[s1.length() + 1];
	    strcpy(c1, s1.c_str());

	    char *c2 = new char[s2.length() + 1];
	    strcpy(c2, s2.c_str());

	    int result = strcmp(c1, c2);
	    return result;
    }
    AVLNode* searchStop(string name){
        AVLNode* temp = root;
        while (temp!=nullptr){
            if (stringCompare(name,temp->getStopName())>0){
                temp = temp->getRight();
            }
            else if (stringCompare(name,temp->getStopName())<0){
                temp = temp->getLeft();
            }
            else return temp;
        }
        return nullptr;
    }
    void insert(AVLNode* node, MetroStop* metroStop){

    }
    void populateTree(MetroLine* metroLine){
    	MetroStop* temp = metroLine->getNode();
    	while (temp!=nullptr){
    		if (root==nullptr){
    			root=new AVLNode(temp->getStopName());
    			root->addMetroStop(temp);
    			root->setParent(nullptr);
                temp = temp->getNextStop();
                continue;
    		}
            AVLNode* avlnode = root;
    		while (1){
    			if (stringCompare(temp->getStopName(),avlnode->getStopName())>0){
    				if (avlnode->getRight()!=nullptr){avlnode = avlnode->getRight();}
    				else{
                        AVLNode* newn = new AVLNode(temp->getStopName());
                        newn->setParent(avlnode);
                        newn->addMetroStop(temp);
    					avlnode->setRight(newn);
    					balance(avlnode->getRight());
                        temp = temp->getNextStop();
    					break;
    				}
    			}
    			else if (stringCompare(temp->getStopName(),avlnode->getStopName())<0){
    				if (avlnode->getLeft()!=nullptr){avlnode = avlnode->getLeft();}
    				else{
    					AVLNode* newn = new AVLNode(temp->getStopName());
                        newn->setParent(avlnode);
                        newn->addMetroStop(temp);
                        avlnode->setLeft(newn);
    					balance(avlnode->getLeft());
                        temp = temp->getNextStop();
    					break;
    				}
    			}
    			else{
    				avlnode->addMetroStop(temp);
                    temp = temp->getNextStop();
    				break;
    			}
    		}

    	}
    }
    void inOrderTraversal(AVLNode* node){
        if (node==nullptr) return;
        inOrderTraversal(node->getLeft());
        cout<<node->getStopName()<<'\n';
        inOrderTraversal(node->getRight());
    }
    int getTotalNodes(AVLNode* node){
    	if (node==nullptr) return 0;
        return 1+getTotalNodes(node->getRight())+getTotalNodes(node->getLeft());
    }
};

// Exploration class
class Trip {
private:
    MetroStop* node;
    Trip* prev;

public:
    Trip(MetroStop* metroStop, Trip* previousTrip){
        node = metroStop;
        prev = previousTrip;
    }

    // Getter methods
    MetroStop* getNode() const{
        return node;
    }
    Trip* getPrev() const{
        return prev;
    }
};

// Exploration class is a queue that stores unexplored Trip objects
class Exploration {
private:

    std::queue<Trip*> trips;

public:

    // Getter methods
    std::queue<Trip*> getTrips() const{
        return trips;
    }

    // Setter methods
    void enqueue(Trip* trip){
        trips.push(trip);
    }
    Trip* dequeue(){
        if (trips.empty()) {
            return nullptr;
        }
        Trip* trip = trips.front();
        trips.pop();
        cout << "Dequeued: " << trip->getNode()->getStopName() << endl;
        return trip;
    }
    bool isEmpty() const{
        return trips.empty();
    }
};

class Path {
private:
    std::vector<MetroStop*> stops;
    int totalFare;

public:
    Path(){
        totalFare = 0;
    }
    // Getter methods
    std::vector<MetroStop*> getStops(){
        return stops;
    }
    int getTotalFare() const{
        return totalFare;
    }
    // Setter methods
    void addStop(MetroStop* stop){
        stops.push_back(stop);
    }
    void setTotalFare(int fare){
        totalFare = fare;
    }
    // helper functions
    void printPath() const{
        for (auto stop : stops) {
            cout << stop->getStopName() << endl;
        }
    }
};

// PathFinder class
class PathFinder {
private:
    AVLTree* tree;
    std::vector<MetroLine*> lines;

public:
    PathFinder(AVLTree* avlTree, const std::vector<MetroLine*>& metroLines){
        tree = avlTree; lines = metroLines;
    }
    void createAVLTree(){
        for (auto line : lines) {
            if (tree->getRoot() == nullptr) {
                tree->setRoot(new AVLNode(line->getNode()->getStopName()));
            }
            tree->populateTree(line);
        }
    }

    vector<Path*> allpathrec(MetroStop* station, string destination, int direction,vector<MetroLine*> linesreached){
        if (station==nullptr) return {};
        if (station->getStopName()==destination){
            vector<Path*> pathlist; pathlist.push_back(new Path());
            pathlist[0]->addStop(station);
            return pathlist;
        }
        vector<Path*> pathlist;
        if (direction){
            pathlist = allpathrec(station->getNextStop(),destination,1,linesreached);
            for (int i=0;i<pathlist.size();i++){
                pathlist[i]->addStop(station);
                pathlist[i]->setTotalFare(pathlist[i]->getTotalFare()+station->getFare()-station->getNextStop()->getFare());
            }
        }
        else{
            pathlist = allpathrec(station->getPrevStop(),destination,0,linesreached);
            for (int i=0;i<pathlist.size();i++){
                pathlist[i]->addStop(station);
                pathlist[i]->setTotalFare(pathlist[i]->getTotalFare()+station->getPrevStop()->getFare()-station->getFare());
            }
        }
        AVLNode* temp = tree->searchStop(station->getStopName());
        for (int i=0;i<temp->getStops().size();i++){
            MetroLine* linen = temp->getStops()[i]->getLine();
            int flag = 1;
            for (int j = 0;j<linesreached.size();j++){
                if (linesreached[j]==linen){flag = 0;break;}
            }
            if (flag){
                linesreached.push_back(linen);
                vector<Path*> onepath = allpathrec(temp->getStops()[i],destination,1,linesreached);
                pathlist.insert(pathlist.end(),onepath.begin(),onepath.end());
                onepath = allpathrec(temp->getStops()[i],destination,0,linesreached);
                pathlist.insert(pathlist.end(),onepath.begin(),onepath.end());
                linesreached.pop_back();
            }
        }
        return pathlist;
    }

    Path* findPath(std::string origin, std::string destination){
        AVLNode* start = tree->searchStop(origin);
        if (start==nullptr) return nullptr;
        vector<Path*> allpaths;
        for (int i=0;i<start->getStops().size();i++){
            vector<MetroLine*> linesreached;
            vector<Path*> onepath;
            linesreached.push_back(start->getStops()[i]->getLine());
            onepath = allpathrec(start->getStops()[i],destination,1,linesreached);
            allpaths.insert(allpaths.end(),onepath.begin(),onepath.end());
            onepath = allpathrec(start->getStops()[i],destination,0,linesreached);
            allpaths.insert(allpaths.end(),onepath.begin(),onepath.end());
        }
        if (allpaths.size()==0) return nullptr;
        //cout<<allpaths.size()<<'\n';
        Path* minfarepath = allpaths[0];
        for (int i=1;i<allpaths.size();i++){
            if (allpaths[i]->getTotalFare()<minfarepath->getTotalFare()) minfarepath = allpaths[i];
        }
        return minfarepath;
    }

    // Getter methods
    AVLTree* getTree() const{
        return tree;
    }
    const std::vector<MetroLine*>& getLines() const{
        return lines;
    }
};

//test_cases
vector<MetroLine*> lines;

vector<string> getFileNames() {
    vector<string> filenames;
    filenames.push_back("blue.txt");
    filenames.push_back("green.txt");
    filenames.push_back("magenta.txt");
    filenames.push_back("orange.txt");
    filenames.push_back("red.txt");
    filenames.push_back("violet.txt");
    filenames.push_back("yellow.txt");
    return filenames;
}

void testPopulateLine() {
    cout<<"Testing populateLine()"<<endl;
    vector<string> filenames = getFileNames();
    int expectedTotalStops[] = {44, 21, 25, 6, 29,38, 62};
    for (int i = 0; i < filenames.size(); i++) {
        string lineName = filenames[i].substr(0, filenames[i].length() - 4);
        MetroLine* metroLine = new MetroLine(lineName);
        metroLine->populateLine(filenames[i]);
        lines.push_back(metroLine);
        cout << "Line name: " << metroLine->getLineName() << endl;
        cout << "Total stops: " << metroLine->getTotalStops() << endl;
        cout << endl;
        assert(metroLine->getTotalStops() == expectedTotalStops[i]);
        metroLine->printLine();
    }
}

void testPopulateTree() {
    cout<<"Testing populateTree()"<<endl;
    vector<string> filenames = getFileNames();
    AVLTree* tree = new AVLTree();
    tree->setRoot(nullptr);
    for (auto line : lines) {
        if (tree->getRoot() == nullptr) {
            tree->setRoot(new AVLNode(line->getNode()->getStopName()));
        }
        tree->populateTree(line);
    }
    cout << "Height of tree: " << tree->height(tree->getRoot()) << endl;
    cout << "Total nodes in tree: " << tree->getTotalNodes(tree->getRoot()) << endl;
    assert(tree->height(tree->getRoot()) == 9);
    assert(tree->getTotalNodes(tree->getRoot()) == 211);
}

vector<string> getExpectedPath() {
    vector<string> expectedPath;
    expectedPath.push_back("Pul Bangash");
    expectedPath.push_back("Pratap Nagar");
    expectedPath.push_back("Shastri Nagar");
    expectedPath.push_back("Inder Lok");
    expectedPath.push_back("Kanhaiya Nagar");
    expectedPath.push_back("Keshav Puram");
    expectedPath.push_back("Netaji Subhash Place");
    expectedPath.push_back("Kohat Enclave");
    expectedPath.push_back("Pitampura");

    return expectedPath;
}

void testFindPath() {
    PathFinder* pathFinder = new PathFinder(new AVLTree(), lines);
    pathFinder->createAVLTree();
    Path* path = pathFinder->findPath("Pitampura", "Pul Bangash");
    assert(path != nullptr);
    cout << "Total fare: " << path->getTotalFare() << endl;
    path->printPath();
    vector<string> expectedPath = getExpectedPath();
    for (int i = 0; i < expectedPath.size(); i++) {
        assert(path->getStops()[i]->getStopName() == expectedPath[i]);
    }
}

int main() {
    vector<void(*)()> tests;
    tests.push_back(&testPopulateLine);
    tests.push_back(&testPopulateTree);
    tests.push_back(&testFindPath);

    for (auto test : tests) {
        test();
    }
    cout<<'\n';
    PathFinder* pathFinders = new PathFinder(new AVLTree(), lines);
    pathFinders->createAVLTree();
    Path* paths = pathFinders->findPath("Moti Nagar","GTB Nagar");
    paths->printPath();
    cout<<paths->getTotalFare()<<'\n';
    return 0;
}