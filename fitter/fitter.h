#pragma once
#include <vector>

#define FITTER_X_MAX	20
#define FITTER_Y_MAX	20

class Vector2d{
	private:
		float x, y;
	public:
		Vector2d(float x, float y);
		Vector2d();
		~Vector2d();
		float get_x();
		float get_y();
		void set_x(float x);
		void set_y(float y);
		float mag();
		Vector2d copy();
		Vector2d& mult(float n);
		Vector2d& sub(Vector2d& other);
		Vector2d& add(Vector2d& other);
		Vector2d& div(float n);
};

class Node{
	public:
		Vector2d net_force;
		Vector2d location;

	public:
		Node();
		~Node();
		virtual Vector2d get_location() = 0;
		virtual void  set_location(Vector2d location) = 0;
		virtual float get_mass() = 0;
};

class Connection{
	public:
		Node& node1;
		Node& node2;
	public:
		Connection(Node& from, Node& to);
		~Connection();
		// void apply_forces();
};

class Fitter{

	public:
		Fitter();
		~Fitter();

		void layout(std::vector<Node> nodes, std::vector<Connection> connections);
};
