#define MAIN_CPP

#include <memory>

#include "ConsoleUI.hpp"
#include "GameController.hpp"
#include "Logger.hpp"
#include "Player.hpp"

using namespace Go;

int main (int argc, char * argv[])
{
    using namespace std;

    //assert(argc > 0 && argc <= 2);

    LOGFUNCTION(cout, "main()");

//    logger.log(LogLevel::kHigh, cout, "Entering main() function"); 

    unique_ptr<IPlayer> one{new Player<ConsoleUI>{"Player 1"}};
    unique_ptr<IPlayer> two{new Player<ConsoleUI>{"Player 2"}};

    GameController controller(*one, *two);

    controller.start();
    controller.waitForStop();

//    logger.log(LogLevel::kHigh, cout, "Exiting main() function"); 

    return 0;
}

