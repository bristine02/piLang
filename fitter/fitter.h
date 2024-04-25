#include <vector>

class FitterLocation{
	private:
		float x, y;
	public:
		FitterLocation(float x, float y);
		~FitterLocation();
		float get_x();
		float get_y();
		void set_x(float x);
		void set_y(float y);
		
}

class Node{
	public:
		Node();
		~Node();
		virtual FitterLocation get_location();
		virtual void  set_location(FitterLocation location);
		virtual float get_mass();

}

class Fitter{

	public:
		Fitter();
		~Fitter();

		void layout(std::vector<Node> nodes);
}
