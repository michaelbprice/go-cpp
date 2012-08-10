#ifndef INCL_POINT_HPP__
#define INCL_POINT_HPP__

namespace Go
{

class Stone;

class Point final
{
 private:
// TODO: figure out constness
    Stone * m_pStone = nullptr; // Non-owning, optional value. DO NOT DELETE!!!

 public:
    void playStone (Stone & stone);

    bool canPlayStone () const;
};

}

#endif /* end of include guard: INCL_POINT_HPP__ */
