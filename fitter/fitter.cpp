#include "fitter.h"

#define FITTER_MAX_CONN_LENGTH		20
#define FITTER_GRAVITY_CONST		2
#define FITTER_FORCE_CONST		2



Fitter::Fitter(){}
Fitter::~Fitter(){}

void Fitter::layout(std::vector<Node> nodes, std::vector<Connection> connections){
	for (auto node = nodes.begin(); node != nodes.end(); ++node)
	{
		Vector2d gravity = node->location.copy().mult(-FITTER_GRAVITY_CONST);
		node->net_force = gravity;
	}
	// Repulsive forces between nodes
	for (std::size_t i = 0; i < nodes.size(); i++)
	{
		for (std::size_t j = i + 1; j < nodes.size(); j++)
		{
			Vector2d loc = nodes.at(i).location;
			Vector2d dir = nodes.at(j).location;
			Vector2d force = dir.copy();
			force.sub(loc).div(dir.mag() * dir.mag());
			force.mult(FITTER_FORCE_CONST);
			nodes.at(i).net_force.sub(force);
			nodes.at(j).net_force.add(force);
		}
	}
	
	// Forces applied by connections
	for (auto con = connections.begin(); con != connections.end(); ++con)
	{
		Vector2d dist = con->node1.location.copy();
		dist.sub(con->node2.location);
		con->node1.net_force.sub(dist);
		con->node2.net_force.add(dist);
	}
	
	// Update node positions
	for (auto node = nodes.begin(); node != nodes.end(); ++node)
	{
		Vector2d velocity = node->net_force.copy();
		velocity.div(node->get_mass());
		node->location.add(velocity);
	}

	
}
