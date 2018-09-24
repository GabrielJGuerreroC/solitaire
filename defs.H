# ifndef DEFS_H
# define DEFS_H

enum class Suit { Spades, Clubs, Hearts, Diamonds };

enum class Rank : size_t
{ Ace, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King };

enum class Color { NonColor, Red, Black };

enum class CardExcept { IllegalMove };

using Card = tuple<Suit, Rank>;

class Move
{
public:
  virtual explicit operator bool() const = 0;

  virtual const Card & card() const = 0;

  virtual bool operator == (const Move &) const = 0;
};

class Draw : public Move
{
public:
  explicit operator bool() const override
  {
    return false;
  }

  const Card & card() const override
  {
    throw std::logic_error("Move draw has not an associated card");
  }

  bool operator == (const Move &) const override
  {
    // Two draw moves are always equals.
    return true;
  }
};

class Discard : public Move
{
  Card c;
  
public:
  Discard(const Card & _c) : c(_c) { /* empty */ }
  
  explicit operator bool() const override
  {
    return true;
  }

  const Card & card() const override
  {
    return c;
  }

  bool operator == (const Move & d) const override
  {
    return c == static_cast<const Discard &>(d).c;
  }
};

using MovePtr = shared_ptr<Move>;

shared_ptr<Move> create_draw_move()
{
  return MovePtr(new Draw);
}

shared_ptr<Move> create_discard_move(const Card & c)
{
  return MovePtr(new Discard(c));
}

# endif // DEFS_H
