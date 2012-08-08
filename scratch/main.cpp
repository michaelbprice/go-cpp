
#include "GameController.hpp"
#include "Player.hpp"
#include "ConsoleUI.hpp"

///////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////

using namespace Go;

using Stones = vector<Stone>;

int main (int argc, char * argv[])
{
	//assert(argc > 0 && argc <= 2);

	unique_ptr<IPlayer> one = new Player<ConsoleUI>{};
	unique_ptr<IPlayer> two = new Player<ConsoleUI>{};

	GameController controller(one, two);

	controller.start();
	controller.waitForStop();

	return 0;
}