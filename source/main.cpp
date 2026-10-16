import std;
import goimpl;

using namespace Go;

int main (int argc, char * argv[])
{
    using namespace std;

    FunctionLogger functionLogger {LogLevel::kHigh, cout, "main()"};

    unique_ptr<IPlayer> one{new Player<ConsoleUI>{"Player 1"}};
    unique_ptr<IPlayer> two{new Player<ConsoleUI>{"Player 2"}};

    GameController controller(*one, *two);

    controller.start();

    return 0;
}
