#include <iostream>
#include <math.h>
#include <tuple>

using namespace std;

// Node is a start and/or end point of a road
class Node
{
private:
	unsigned short level;													// Node level
	float x, y;																// x and y coordinates
public:
	Node(float X, float Y, unsigned short lvl) : x(X), y(Y), level(lvl) {};	// Constructor 1
	Node(float X, float Y) : x(X), y(Y), level(0) {};						// Constructor 2
	Node() : x(0.0), y(0.0), level(0) {};									// Constructor 3
	pair<float, float> get_cords() { return make_pair(x, y); };				// Returns x and y coordinates
	float get_Xcord() { return x; };										// Returns x coordiante
	float get_Ycord() { return y; };										// Returns y coordinate
	unsigned short get_lvl() { return level; };								// Returns level
	void set_X(float x) { this->x = x; };									// Changes x coordinate
	void set_Y(float x) { this->y = x; };									// Changes y coordinate
	void set_cords(float X, float Y) { this->x = X; this->y = Y; };			// Changes both x and y coordinates
	void set_level(unsigned short level) { this->level = level; };			// Changes node level
};

// Connection is a road between two nodes
class Connection
{
private:
	Node* origin;															// Pointer to the start point
	Node* destination;														// Pointer to the end point
	unsigned short numLanes;												// Number of Lanes
	bool oneWay;															// true - one way road; false - two ways road
	float distance;															// Length of connection
	void calc_dist()														// Updates distance
	{
		distance = (float)
			sqrt(pow(origin->get_Xcord() - destination->get_Xcord(), 2.0) +
				pow(origin->get_Ycord() - destination->get_Ycord(), 2.0));
	};
public:
	Connection(Node& orig, Node& dest) : 
		origin(&orig), 
		destination(&dest), 
		numLanes(1),
		oneWay(true)
	{ calc_dist(); };																			// Constructor. Nodes are compulsory
	void set_origin(Node& origin) { this->origin = &origin; calc_dist(); };						// Changes start node
	void set_destination(Node& destination) { this->destination = &destination; calc_dist(); };	// Changes end node
	void set_pair(Node& origin, Node& destination) { this->origin = &origin; this->destination = &destination; calc_dist(); };			// Changes both start and end nodes
	void set_numLanes(unsigned short lanes) { this->numLanes = lanes; };						// Changes number of lanes
	void set_oneWay(bool oneway) { this->oneWay = oneway; };									// true: one way road; false: two ways road
	float get_dist() { this->calc_dist(); return distance; };											// Returns the distance
	bool get_oneWay() { return oneWay; };														// true: one way road; false: two ways road
	unsigned short get_numLanes() { return numLanes; };											// Returns number of lanes	

};
// add more constructors for class connection (with num lanes)
// or probably keep default 1 and then change to required number after created using class function?
// 


// Route is a collection of consequetive connections that represent number of vehicles that take those routes
/*
class Route
{
public:

private:
};
*/

// Vehicle moves on connections
class Vehicle
{
private:
	Connection* road;
	float max_speed;			// Max possible speed (km/h). Can be slower due to road geometry and traffic lights, but it's not considered here
	float travel_time;				// unit: seconds
	void calc_traveltime() { travel_time = (float)3.6 * road->get_dist() / max_speed; };		// Time in seconds
public:
	Vehicle(Connection &segment) : 
		road(&segment),
		max_speed(60.0)
	{
		calc_traveltime();
	};																				// Constructor 1
	float get_maxspeed() { return max_speed; };										// Returns max speed in km/h
	float get_traveltime() { calc_traveltime(); return travel_time; };	// Returns travel time in seconds
	float get_length() { return road->get_dist(); };											// Returns the segment length in meters
	void set_maxspeed(float speed) { max_speed = speed; calc_traveltime(); };		// Sets max speed in km/h
	void set_travel_time(float time) { travel_time = time; }						// Sets travel time in seconds. Not recommended to use
};
// add more overloading 


/*
class veh
{
private:
	Connection road[20];	
	float max_speed = 60;			// Max possible speed (km/h). Can be slower due to road geometry and traffic lights
	float travel_time;				// unit: seconds
	float length;					// unit: meters
	void calc_traveltime() { travel_time = (float) 3.6 * length / max_speed; };		// Time in seconds
public:
	veh(Connection arr_roads[]);

};

veh::veh(Connection arr_roads[]) {
	int size = sizeof(arr_roads) / sizeof(arr_roads[0]);
	for (int i = 0; i < size; i++) road[i] = arr_roads[i];
}
*/



int main()
{
	// Craeeting 3 nodes
	Node A(10.0, 10.0);
	Node B(50.0, 0.0);
	Node C(173.4, 765.4);

	cout << sizeof(A) << endl;

	float b1, b2;
	tie(b1, b2) = B.get_cords();
	cout << b1 << " " << b2 << endl;
	cout << B.get_Xcord() << endl;
	cout << B.get_Ycord() << endl;
	cout << B.get_lvl() << endl;

	Connection AB(A, B);
	cout << AB.get_dist() << endl;
	Vehicle car(AB);
	cout << car.get_traveltime() << endl;

	AB.set_origin(C);
	cout << AB.get_dist() << endl;
	cout << car.get_traveltime() << endl;

	AB.set_destination(A);
	cout << AB.get_dist() << endl;
	cout << car.get_traveltime() << endl;

	AB.set_pair(A, B);
	cout << AB.get_dist() << endl;
	cout << car.get_traveltime() << endl;

	AB.set_numLanes(2);
	cout << AB.get_numLanes() << endl;

	AB.set_oneWay(false);

	cout << sizeof(short) << endl;

	system("pause");
	return 0;
};

