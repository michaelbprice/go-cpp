#include <memory>

#include "ConsoleUI.hpp"
#include "GameController.hpp"
#include "Logger.hpp"
#include "Player.hpp"

using namespace Go;

int main (int argc, char * argv[])
{
    using namespace std;

    LOG_FUNCTION(cout, "main()");

    unique_ptr<IPlayer> one{new Player<ConsoleUI>{"Player 1"}};
    unique_ptr<IPlayer> two{new Player<ConsoleUI>{"Player 2"}};

    GameController controller(*one, *two);

    controller.start();

    return 0;
}

