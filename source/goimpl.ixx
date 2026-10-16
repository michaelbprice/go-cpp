module;

#include <cassert>
#include "LoggerMacros.hpp"

export module goimpl;

import std;

export namespace Go {

enum class StoneColor : unsigned char
{
    BLACK,
    WHITE
};

StoneColor getOpposingColor (StoneColor color);

class Stone final
{
 public:
    static const std::size_t kDefaultBlackCount = 21;
    static const std::size_t kDefaultWhiteCount = 20;
 private:
    StoneColor m_color;
 public:
    Stone (StoneColor color) : m_color(color) { }
    StoneColor getColor () const;
};

using Stones = std::vector<Stone>;

std::ostream & operator<< (std::ostream & out, const std::optional<Stone> & stone);

struct PointCoords final
{
    PointCoords () = default;
    PointCoords (std::size_t r, std::size_t c) : row(r), column(c) { }
    bool operator==(const PointCoords&) const = default;

    std::size_t row = 0;
    std::size_t column = 0;
};

class Point;
std::ostream & operator<< (std::ostream & out, const PointCoords & coords);
std::ostream & operator<< (std::ostream & out, const Point & point);

class Point final
{
 friend std::ostream & operator<< (std::ostream & out, const Point & point);
 private:
    std::optional<Stone> m_stone;
 public:
    PointCoords coordinates;
    const std::optional<Stone> & getStone() const;
    void playStone (const Stone & stone);
    bool canPlayStone () const;
    void removeStone ();
};

using PointSet = std::unordered_set<Point*>;
using ConstPointSet = std::unordered_set<const Point*>;
using PointVisitorFn = std::function<void(const Point &)>;

class Chain;

class Board final
{
 public:
    static const int BOARD_SIZE = 19;
 private:
    template <typename T, std::size_t X, std::size_t Y>
    using multi_array = std::array<std::array<T, X>, Y>;

    multi_array<Point, BOARD_SIZE, BOARD_SIZE> m_points;
    std::pair<bool, std::reference_wrapper<const Point>> m_koState;
 public:
    Board ();
    ~Board () = default;
    Board (const Board &) = delete;
    Board & operator= (const Board &) = delete;
    Board (Board &&) = delete;
    Board & operator= (Board &&) = delete;

    std::vector<Chain> getAllEmptyChains ();
    const std::optional<Stone> & getStoneAt (const PointCoords & coords) const;
    bool isOccupiedPoint (const PointCoords & coords);
    bool isValidMove (StoneColor color, const PointCoords & coords) const;
    void placeStoneAt (const PointCoords & coords, Stone stone);
    std::vector<PointCoords> removeCapturedStones (StoneColor colorToCapture);

    void visitNeighboringPoints (const Point & point, const PointVisitorFn & visitorFn) const
    {
        visitorFn(getPointAbove(point));
        visitorFn(getPointBelow(point));
        visitorFn(getPointLeft(point));
        visitorFn(getPointRight(point));
    }

 private:
    Chain calculateChain (const PointCoords & coords);
    bool doesKoRuleApply (const Chain & chain) const;
    const Point & getPointAbove (const Point & point) const;
    const Point & getPointBelow (const Point & point) const;
    const Point & getPointLeft (const Point & point) const;
    const Point & getPointRight (const Point & point) const;
};

class Chain
{
 private:
    std::unordered_map<std::optional<StoneColor>, ConstPointSet> m_chainAndNeighbors;
    const Point & m_startPoint;
    std::optional<StoneColor> m_color;
 public:
    struct PointVisitedAlreadyException { };

    Chain (const Point & startPoint, const Board & board, ConstPointSet * pointsToIgnore);
    Chain (const std::optional<StoneColor> & stoneColor, const Point & startPoint,
           const Board & board, ConstPointSet * pointsToIgnore);
    ~Chain () = default;
    Chain (const Chain &) = default;

    std::size_t borderCountOf (const std::optional<StoneColor> & color);
    const std::optional<StoneColor> & color () const;
    bool containsPoint (const Point & point) const;

    void forEachPoint (const PointVisitorFn & visitorFn)
    {
        forEachSurroundingPoint(m_color, visitorFn);
    }

    void forEachSurroundingPoint (const std::optional<StoneColor> & color, const PointVisitorFn & visitorFn)
    {
        for (auto & p : m_chainAndNeighbors[color])
            visitorFn(*p);
    }

    std::size_t libertyCount () const;
    std::size_t size () const;
 private:
    void doChainCalculation (const Point & point, const Board & board, ConstPointSet & pointsToIgnore);
};

class IPlayer
{
 public:
    virtual void addToCaptured (std::size_t numCaptured) = 0;
    virtual std::size_t calculateScore () const = 0;
    virtual void chooseName () = 0;
    virtual StoneColor chooseStoneColor () = 0;
    virtual const Board & getGameBoard () const = 0;
    virtual const std::string & getName () const = 0;
    virtual StoneColor getStoneColor () = 0;
    virtual bool hasStones () const = 0;
    virtual void notifyGameReady () = 0;
    virtual void notifyLost () = 0;
    virtual void notifyTied () = 0;
    virtual void notifyTurn () = 0;
    virtual void notifyWon () = 0;
    virtual void setGameBoard (Board & board) = 0;
    virtual void setStoneColor (StoneColor color) = 0;
    virtual PointCoords playStone () = 0;
    virtual void placeStoneAt (PointCoords point) = 0;
};

using PlayerPair = std::pair<std::reference_wrapper<IPlayer>, std::reference_wrapper<IPlayer>>;

class ConsoleUI
{
 private:
    const IPlayer & m_player;
    short m_updateCount = 0;
 public:
    ConsoleUI (const IPlayer & player);
    void onInvalidMove(const PointCoords & invalidMove);
    void onWin ();
    void onLoss ();
    void onTie ();
    PointCoords promptForMove ();
    std::string promptForName ();
    StoneColor promptForStoneColor ();
    void updateGameState ();
};

template <typename TyPlayerUI>
class Player final : public IPlayer
{
 private:
    TyPlayerUI m_ui;
    Board * m_pBoard = nullptr; // Non-owning pointer... do NOT delete!
    std::optional<StoneColor> m_stoneColor;
    std::string m_name;
    Stones m_stones;
    std::size_t m_capturedCount = 0;
 public:
    Player (const std::string & name);
    virtual void addToCaptured (std::size_t numCaptured) override;
    virtual std::size_t calculateScore () const override;
    virtual void chooseName () override;
    virtual StoneColor chooseStoneColor () override;
    virtual const Board & getGameBoard () const override;
    virtual const std::string & getName () const override;
    virtual StoneColor getStoneColor () override;
    virtual bool hasStones () const override;
    virtual void notifyGameReady () override;
    virtual void notifyLost () override;
    virtual void notifyTied () override;
    virtual void notifyTurn () override;
    virtual void notifyWon () override;
    virtual void setGameBoard (Board & board) override;
    virtual void setStoneColor (StoneColor color) override;
    virtual PointCoords playStone () override;
    virtual void placeStoneAt (PointCoords point) override;
};

class GameController final
{
 private:
    Board m_board;
    IPlayer & m_playerOne;
    IPlayer & m_playerTwo;
 public:
    GameController (IPlayer & one, IPlayer & two);
    void start ();
 private:
    void doGameLoop (PlayerPair & playerPair);
    void doScoring ();
};

enum class LogLevel : unsigned char
{
    kNone = 0,
    kLow = 1,
    kMedium = 2,
    kHigh = 3,
    kFirehose = 4
};

class Logger final
{
 private:
    LogLevel m_level = LogLevel::kNone;
 public:
    Logger (LogLevel level)
      : m_level(level)
    { }

    template <typename ... Args>
    std::ostream & log (LogLevel level, std::ostream & out, Args && ...args)
    {
        if (level <= m_level)
        {
            out << "LOG(" << static_cast<unsigned short>(level) << "): ";
            return doLog(level, out, std::forward<Args>(args)...);
        }
        return out;
    }

 private:
    template <typename T, typename ... Args>
    std::ostream & doLog (LogLevel level, std::ostream & out, T && t, Args && ...args)
    {
        return doLog(level, out << t, std::forward<Args>(args)...);
    }

    template <typename T>
    std::ostream & doLog (LogLevel level, std::ostream & out, T && t)
    {
        return out << t << std::endl;
    }
};

} // namespace Go

export extern Go::Logger gLogger;

export namespace Go {

struct FunctionLogger final
{
    FunctionLogger (LogLevel level, std::ostream & out, const char * methodName)
      : m_level{level}
      , m_out{out}
      , m_name{methodName}
    {
        gLogger.log(m_level, m_out, std::string(kIndention * nestingLevel, '='), ">> ", m_name);
        ++nestingLevel;
    }

    ~FunctionLogger ()
    {
        --nestingLevel;
        gLogger.log(m_level, m_out, "<<", std::string(kIndention * nestingLevel, '='), " ", m_name);
    }

    LogLevel m_level = LogLevel::kHigh;
    std::ostream & m_out;
    const char * m_name = nullptr;
    static const std::size_t kIndention = 2;
    static std::size_t nestingLevel;
};

} // namespace Go

#include "Player.tpp"
