
#include "GameController.hpp"
#include "Player.hpp"
#include "ConsoleUI.hpp"
#include <memory>

///////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////

using namespace Go;

int main (int argc, char * argv[])
{

    //assert(argc > 0 && argc <= 2);

    std::unique_ptr<IPlayer> one{new Player<ConsoleUI>{"Player 1"}};
    std::unique_ptr<IPlayer> two{new Player<ConsoleUI>{"Player 2"}};

    GameController controller(*one, *two);

    controller.start();
    controller.waitForStop();

    return 0;
}
