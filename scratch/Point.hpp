#ifndef INCL_POINT_HPP__
#define INCL_POINT_HPP__

namespace Go
{

class Stone;

class Point final
{
 private:
 	Stone * m_stone = nullptr; // Non-owning, optional value. DO NOT DELETE!!!

 public:
 	void playStone (const Stone & stone);

 	bool canPlayStone ();
};

}

#endif /* end of include guard: INCL_POINT_HPP__ */