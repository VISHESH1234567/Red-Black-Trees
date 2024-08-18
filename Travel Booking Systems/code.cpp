#include <iostream>
#include <cassert>
#include <bits/stdc++.h>  
#include <map>
#include <vector>
using namespace std;

class Vehicle;

class Trip {
private:
    Vehicle* vehicle;
    std::string pick_up_location;
    std::string drop_location;
    int departure_time;
    int booked_seats;
public:
    Trip(Vehicle* vehicle, std::string pick_up_location, std::string drop_location, int departure_time)
        : vehicle(vehicle), pick_up_location(pick_up_location), drop_location(drop_location), departure_time(departure_time), booked_seats(0) {}

    // Getter functions
    Vehicle* getVehicle() const {
        return vehicle;
    }

    std::string getPickUpLocation() const {
        return pick_up_location;
    }

    std::string getDropLocation() const {
        return drop_location;
    }

    int getDepartureTime() const {
        return departure_time;
    }

    int getBookedSeats() const {
        return booked_seats;
    }

    // Setter functions
    void setVehicle(Vehicle* v) {
        vehicle = v;
    }

    void setPickUpLocation(std::string location) {
        pick_up_location = location;
    }

    void setDropLocation(std::string location) {
        drop_location = location;
    }

    void setDepartureTime(int time) {
        departure_time = time;
    }

    void setBookedSeats(int seats) {
        booked_seats = seats;
    }

};

class BinaryTreeNode {
private:
    BinaryTreeNode* leftptr;
    BinaryTreeNode* rightptr;
    BinaryTreeNode* parentptr;
    int departuretime;
    Trip* tripnodeptr;
public:
    BinaryTreeNode(int departuretime = 0, Trip* tripenodeptr = nullptr, BinaryTreeNode* parentptr = nullptr)
        : leftptr(nullptr), rightptr(nullptr), parentptr(parentptr), departuretime(departuretime), tripnodeptr(tripenodeptr) {}

    // Getter functions
    BinaryTreeNode* getLeftPtr() const {
        return leftptr;
    }

    BinaryTreeNode* getRightPtr() const {
        return rightptr;
    }

    BinaryTreeNode* getParentPtr() const {
        return parentptr;
    }

    int getDepartureTime() const {
        return departuretime;
    }

    Trip* getTripNodePtr() const {
        return tripnodeptr;
    }

    // Setter functions
    void setLeftPtr(BinaryTreeNode* left) {
        leftptr = left;
    }

    void setRightPtr(BinaryTreeNode* right) {
        rightptr = right;
    }

    void setParentPtr(BinaryTreeNode* parent) {
        parentptr = parent;
    }

    void setDepartureTime(int time) {
        departuretime = time;
    }

    void setTripNodePtr(Trip* trip) {
        tripnodeptr = trip;
    }

};

class TransportService {
private:
    std::string name;
    BinaryTreeNode* BSThead;
public:
    TransportService(std::string name) : name(name), BSThead(nullptr) {}

    // Getter functions
    std::string getName() const {
        return name;
    }

    BinaryTreeNode* getBSTHead() const {
        return BSThead;
    }

    // Setter functions
    void setName(std::string service_name) {
        name = service_name;
    }

    void setBSTHead(BinaryTreeNode* node) {
        BSThead = node;
    }

    void addTrip(int key, Trip* trip){
    	if (BSThead==nullptr){BSThead = new BinaryTreeNode(key,trip); return;}
    	BinaryTreeNode* temp = BSThead;
    	while (1){
    		if (key>temp->getDepartureTime() and temp->getRightPtr()!=nullptr) temp = temp->getRightPtr();
    		else if (key>temp->getDepartureTime()){
    			temp->setRightPtr(new BinaryTreeNode(key,trip,temp));
    			return;
    		}
    		else if (key<=temp->getDepartureTime() and temp->getLeftPtr()!=nullptr) temp = temp->getLeftPtr();
    		else{
    			temp->setLeftPtr(new BinaryTreeNode(key,trip,temp));
    			return;
    		}
    	}
    }

    void deletenode(BinaryTreeNode* address){
    	if (address->getLeftPtr()==nullptr and address->getRightPtr()==nullptr){
    		if (address->getParentPtr()->getRightPtr()==address){
    			address->getParentPtr()->setRightPtr(nullptr);
    			delete address;
    		}
    		else{
    			address->getParentPtr()->setLeftPtr(nullptr);
    			delete address;
    		}
    	}
    	else if (address->getRightPtr()!=nullptr){
    		BinaryTreeNode* temp = address->getRightPtr();
    		while (temp->getLeftPtr()!=nullptr){
    			temp = temp->getLeftPtr();
    		}
    		address->setTripNodePtr(temp->getTripNodePtr());
    		deletenode(temp);
    	}
    	else{
    		BinaryTreeNode* temp = address->getLeftPtr();
    		while (temp->getRightPtr()!=nullptr){
    			temp = temp->getRightPtr();
    		}
    		address->setTripNodePtr(temp->getTripNodePtr());
    		deletenode(temp);
    	}
    }
    vector<Trip*> searchshowtrips(BinaryTreeNode* address,int aftertime,int beforetime){
    	if (address==nullptr) return {};
    	vector<Trip*> output;
    	if (address->getTripNodePtr()->getDepartureTime()<aftertime){
    		return searchshowtrips(address->getRightPtr(),aftertime,beforetime);
    	}
    	else if (address->getTripNodePtr()->getDepartureTime()>=beforetime){
    		return searchshowtrips(address->getLeftPtr(),aftertime,beforetime);
    	}
    	else{
    		output.push_back(address->getTripNodePtr());
    		vector<Trip*> a= searchshowtrips(address->getLeftPtr(),aftertime,beforetime);
    		vector<Trip*> b= searchshowtrips(address->getRightPtr(),aftertime,beforetime);
    		output.insert(output.end(),a.begin(),a.end());
    		output.insert(output.end(),b.begin(),b.end());
    		return output;
    	}
    }

};

class Vehicle {
private:
    std::string vehicle_number;
    int seating_capacity;
    std::vector<Trip*> trips;
public:
    Vehicle(std::string vehicle_number, int seating_capacity)
        : vehicle_number(vehicle_number), seating_capacity(seating_capacity){}

    // Getter functions
    std::string getVehicleNumber() const {
        return vehicle_number;
    }

    int getSeatingCapacity() const {
        return seating_capacity;
    }

    // Setter functions
    void setVehicleNumber(std::string number) {
        vehicle_number = number;
    }

    void setSeatingCapacity(int capacity) {
        seating_capacity = capacity;
    }

    void addTrip(Trip* trip) {
        trips.push_back(trip);
    }
    bool checkrepeattrips(Trip* trip){
    	for (int i=0;i<trips.size();i++){
    		if (trips[i]->getPickUpLocation()==trip->getPickUpLocation() and trips[i]->getDropLocation()==trip->getDropLocation() and trips[i]->getDepartureTime()==trip->getDepartureTime()){
    			return true;
    		}
    	}
    	return false;
    }
    void deletetrips(Trip* trip){
    	for (int i=0;i<trips.size();i++){
    		if (trips[i]==trip){
    			trips.erase(trips.begin()+i);
    			break;
    		}
    	}
    }
    vector<Trip*> getTrips(){
    	return trips;
    }
};

class Location {
private:
    std::string name;
    std::vector<Trip*> trips;
public:
	std::vector<TransportService*> serviceptrs;
    Location(std::string name) : name(name) {}

    // Getter functions
    std::string getName() const {
        return name;
    }

    TransportService* getServicePtr(std::string droplocation) const {
    	for (int i=0;i<serviceptrs.size();i++){
    		if (serviceptrs[i]->getName()==droplocation){
    			return serviceptrs[i];
    		}
    	}
        return nullptr;
    }

    // Setter functions
    void setName(std::string location_name) {
        name = location_name;
    }

    TransportService* setServicePtr(std::string droplocation) {
    	serviceptrs.push_back(new TransportService(droplocation));
        return serviceptrs[serviceptrs.size()-1];
    }

    void addTrip(Trip* trip) {
        trips.push_back(trip);
    }

};

class BinaryTree {
protected:
    BinaryTreeNode* root;

public:
    BinaryTree() : root(nullptr) {}

    int getHeightrec(BinaryTreeNode* address){
    	if (address==nullptr) return 0;
    	int a = getHeightrec(address->getLeftPtr());
    	int b = getHeightrec(address->getRightPtr());
    	if (a>=b) return 1+a;
    	return 1+b;
    }
    int getHeight(){
        // Implement this function to return the height of the tree
        if (root==nullptr) return -1;
        return getHeightrec(root)-1;
    }

    int getNumberOfNodesrec(BinaryTreeNode* address){
    	if (address==nullptr) return 0;
    	return 1+getNumberOfNodesrec(address->getLeftPtr())+getNumberOfNodesrec(address->getRightPtr());
    }
    int getNumberOfNodes(){
        // Implement this function to return the number of nodes in the tree
        if (root==nullptr) return 0; // Placeholder
        return getNumberOfNodesrec(root);
    }
};

class BinarySearchTree : public BinaryTree {
public:
    BinarySearchTree(){}

    BinaryTreeNode* getElementWithMinimumKey() const {
        // Implement this function to return the element with the minimum key
        if (root==nullptr) return nullptr;
        BinaryTreeNode* temp = root;
        while (temp->getLeftPtr()!=nullptr){
        	temp = temp->getLeftPtr();
        }
        return temp;
    }

    BinaryTreeNode* getElementWithMaximumKey() const {
        // Implement this function to return the element with the maximum key
        if (root==nullptr) return nullptr;
        BinaryTreeNode* temp = root;
        while (temp->getRightPtr()!=nullptr){
        	temp = temp->getRightPtr();
        }
        return temp;
    }

    BinaryTreeNode* searchNodeWithKey(int key) const {
        // Implement this function to search for a node with the given key or the next larger key
        if (root==nullptr) return nullptr; // Placeholder
        BinaryTreeNode* temp = root;
        while (temp!=nullptr){
        	if (key>temp->getDepartureTime()) temp = temp->getRightPtr();
        	else if (key<temp->getDepartureTime()) temp = temp->getLeftPtr();
        	else return temp;
        }
        return nullptr;
    }

    BinaryTreeNode* getSuccessorNode(BinaryTreeNode* node) const {
        // Implement this function to return the successor node of the given node
        return nullptr; // Placeholder
    }

    BinaryTreeNode* getSuccessorNodeByKey(int key) const {
        // Implement this function to return the successor node by key
        return nullptr; // Placeholder
    }

    BinaryTreeNode* getPredecessorNode(BinaryTreeNode* node) const {
        // Implement this function to return the predecessor node of the given node
        return nullptr; // Placeholder
    }

    BinaryTreeNode* getPredecessorNodeByKey(int key) const {
        // Implement this function to return the predecessor node by key
        return nullptr; // Placeholder
    }
};

class TravelDesk {
private:
    std::vector<Vehicle*> vehicles;
    std::vector<Location*> locations;
public:
    void addTrip(std::string vehicle_number, int seating_capacity, std::string pick_up_location, std::string drop_location, int departure_time) {
        // Implement this function to add a trip
        bool flag = 1;int i;Vehicle* newveh;
        for (i=0;i<vehicles.size();i++){
        	if (vehicles[i]->getVehicleNumber()==vehicle_number){flag = 0; break;}
        }
        if (flag){newveh = new Vehicle(vehicle_number,seating_capacity);vehicles.push_back(newveh);}
        else newveh = vehicles[i];
        Trip* newtrip = new Trip(newveh,pick_up_location,drop_location,departure_time);
        if (newveh->checkrepeattrips(newtrip)) return;
        newveh->addTrip(newtrip);
        for (i=0;i<locations.size();i++){
        	if (locations[i]->getName()==pick_up_location){
        		TransportService* temp = locations[i]->getServicePtr(drop_location);
        		locations[i]->addTrip(newtrip);
        		if (temp==nullptr){
        			temp = locations[i]->setServicePtr(drop_location);
        		}
        		temp->addTrip(departure_time, newtrip);
        		return;
        	}
        }
        if (i==locations.size()){
        	locations.push_back(new Location(pick_up_location));
        	locations[i]->addTrip(newtrip);
        	TransportService* temp = locations[i]->setServicePtr(drop_location);
        	temp->addTrip(departure_time,newtrip);
        	return;
        }
    }

    std::vector<Trip*> showTrips(std::string pick_up_location, int after_time, int before_time) {
        // Implement this function to retrieve trips within a specified time range
        if (after_time>before_time){
        	int t = after_time;
        	after_time = before_time; before_time = t;
        }
        vector<Trip*> output;
        for (int i=0;i<locations.size();i++){
        	if (locations[i]->getName()==pick_up_location){
        		for (int j=0;j<locations[i]->serviceptrs.size();j++){
        			vector<Trip*> temp = locations[i]->serviceptrs[j]->searchshowtrips(locations[i]->serviceptrs[j]->getBSTHead(),after_time,before_time);
        			output.insert(output.end(),temp.begin(),temp.end());
        		}
        	}
        }
        return output; // Placeholder
    }
    std::vector<Trip*> showTripsbydestination(std::string pick_up_location, std::string destination,int after_time, int before_time){
        // Implement this function to retrieve trips within a specified time range form pickup to droplocatin
        if (after_time>before_time){
        	int t = after_time;
        	after_time = before_time; before_time = t;
        }
        vector<Trip*> output;
        for (int i=0;i<locations.size();i++){
        	if (locations[i]->getName()==pick_up_location){
        		TransportService* temporary = locations[i]->getServicePtr(destination);
        		output = temporary->searchshowtrips(temporary->getBSTHead(),after_time,before_time);
        	}
        }
        return output; // Placeholder
    }

    Trip* bookTrip(std::string pick_up_location, std::string drop_location, std::string vehicle_number, int departure_time) {
        // Implement this function to book a trip
        for (int i=0;i<locations.size();i++){
        	if (locations[i]->getName()==pick_up_location){
        		TransportService* temporary = locations[i]->getServicePtr(drop_location);
        		BinaryTreeNode* temp = temporary->getBSTHead();
        		while (temp!=nullptr){
        			if (departure_time>temp->getTripNodePtr()->getDepartureTime()) temp = temp->getRightPtr();
        			else if (departure_time<temp->getTripNodePtr()->getDepartureTime()) temp = temp->getLeftPtr();
        			else{
        				if (temp->getTripNodePtr()->getVehicle()->getVehicleNumber()==vehicle_number){
        					if (temp->getTripNodePtr()->getBookedSeats()==temp->getTripNodePtr()->getVehicle()->getSeatingCapacity()){return nullptr;}
        					temp->getTripNodePtr()->setBookedSeats(temp->getTripNodePtr()->getBookedSeats()+1);
        					return temp->getTripNodePtr();
        					//delete the node here
        					/*for (int i=0;i<vehicles.size();i++){
        						if (vehicles[i]->getVehicleNumber()==vehicle_number){vehicles[i]->deletetrips(temp->getTripNodePtr());break;}
        					}
        					temporary->deletenode(temp);
        					return nullptr;*/
        				}
        				temp = temp->getLeftPtr();
        			}
        		}
        	}
        }
        return nullptr; // Placeholder
    }
    Location* getLocation(std::string location){
    	for (int i=0;i<locations.size();i++){
    		if (locations[i]->getName()==location) return locations[i];
    	}
        return nullptr;
    }

};

int testCasesPassed = 0;


// Utility function to check BST property recursively
bool isBSTUtil(BinaryTreeNode* node, int minValue, int maxValue) {
    if (node == nullptr)
        return true;

    int nodeValue = node->getDepartureTime();
    if (nodeValue < minValue || nodeValue > maxValue)
        return false;

    return isBSTUtil(node->getLeftPtr(), minValue, nodeValue - 1) &&
           isBSTUtil(node->getRightPtr(), nodeValue + 1, maxValue);
}
// Function to check if a tree is a proper BST
bool isBST(BinaryTreeNode* node) {
    return isBSTUtil(node, INT_MIN, INT_MAX);
}


// Test Case: Adding more trips and accessing the root of the tree by location and service
void test_addTrip() {
    TravelDesk travelDesk;

    // Add trips
    for (int i = 0; i < 10; ++i) {
        std::string vehicleNumber = "A" + std::to_string(i);
        travelDesk.addTrip(vehicleNumber, 4, "LocationA", "LocationB", 1000 + i * 100);
    }

    // Add trips for LocationX
    for (int i = 0; i < 10; ++i) {
        std::string vehicleNumber = "X" + std::to_string(i);
        travelDesk.addTrip(vehicleNumber, 3, "LocationX", "LocationY", 1500 + i * 100);
    }
    
    // Verify that the tree is a proper BST
    BinaryTreeNode* rootLocationA = travelDesk.getLocation("LocationA")->getServicePtr("LocationB")->getBSTHead(); // Add a function to get root by location
    assert(isBST(rootLocationA));

    BinaryTreeNode* rootLocationX = travelDesk.getLocation("LocationX")->getServicePtr("LocationY")->getBSTHead(); // Add a function to get root by location
    assert(isBST(rootLocationX));

    std::vector<Trip*> tripsFromLocationA = travelDesk.showTrips("LocationA", 0, 2000);
    std::vector<Trip*> tripsFromLocationX = travelDesk.showTrips("LocationX", 0, 2000);

    // Assert the number of trips from LocationA and LocationX
    assert(tripsFromLocationA.size() == 10);
    assert(tripsFromLocationX.size() == 5);

    testCasesPassed++;
}


// Test Case 2: Booking a trip and checking booked seats
void test_bookTrip() {
    TravelDesk travelDesk;
    travelDesk.addTrip("XYZ789", 3, "LocationX", "LocationY", 1500);

    Trip* bookedTrip = travelDesk.bookTrip("LocationX", "LocationY", "XYZ789", 1500);
    assert(bookedTrip != nullptr);
    assert(bookedTrip->getBookedSeats() == 1);
    testCasesPassed++;
}

// Test Case 3: Trying to book more seats than available
void test_bookTrip_max_capacity() {
    TravelDesk travelDesk;
    travelDesk.addTrip("LMN456", 2, "LocationP", "LocationQ", 1200);

    Trip* bookedTrip = travelDesk.bookTrip("LocationP", "LocationQ", "LMN456", 1200);
    assert(bookedTrip != nullptr);
    assert(bookedTrip->getBookedSeats() == 1);

    Trip* secondBooking = travelDesk.bookTrip("LocationP", "LocationQ", "LMN456", 1200);
    assert(secondBooking != nullptr);
    assert(secondBooking->getBookedSeats() == 2);
    testCasesPassed++;
}

// Test Case 4: Showing trips within a specific time range
void test_showTrips_by_time() {
    TravelDesk travelDesk;
    travelDesk.addTrip("ABC123", 4, "LocationA", "LocationB", 1000);
    travelDesk.addTrip("XYZ789", 3, "LocationX", "LocationY", 1500);

    std::vector<Trip*> trips = travelDesk.showTrips("LocationA", 800, 1200);
    assert(trips.size() == 1);
    testCasesPassed++;
}

// Test Case 5: Setting and getting the location name
void test_location_name() {
    Location location("LocationC");
    assert(location.getName() == "LocationC");

    location.setName("NewLocation");
    assert(location.getName() == "NewLocation");
    testCasesPassed++;
}

// Test Case 6: Adding a trip to a vehicle
void test_addTrip_to_vehicle() {
    Vehicle vehicle("ABC123", 4);
    Trip trip(&vehicle, "LocationA", "LocationB", 1000);

    vehicle.addTrip(&trip);
    const std::vector<Trip*>& trips = vehicle.getTrips();
    assert(trips.size() == 1);
    testCasesPassed++;
}

// Test Case 7: Setting and getting the departure time of a trip
void test_trip_departure_time() {
    Vehicle vehicle("ABC123", 4);
    Trip trip(&vehicle, "LocationA", "LocationB", 1000);

    trip.setDepartureTime(1100);
    assert(trip.getDepartureTime() == 1100);
    testCasesPassed++;
}



int main() {
    // Run the test cases
    test_addTrip();
    test_bookTrip();
    test_bookTrip_max_capacity();
    test_showTrips_by_time();
    test_location_name();
    test_addTrip_to_vehicle();
    test_trip_departure_time();
    std::cout << "Number of test cases passed: " << testCasesPassed << "/" << 8 << std::endl;
    
    return 0;
}