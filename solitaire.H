// Coloca aquí tu nombre y tu cédula.

Color card_color(const Card & c)
{
  return Color::NonColor;
}

size_t card_value(const Card & c)
{
  return 0;
}

SLList<Card> remove_card(const SLList<Card> & cs, const Card & c)
{
  return SLList<Card>();
}

bool all_same_color(const SLList<Card> & cs)
{
  return false;
}

size_t sum_cards(const SLList<Card> & cs)
{
  return 0;
}

size_t score(const SLList<Card> & cs, size_t goal)
{
  return 0;
}

size_t officiate(SLList<Card> cs, SLList<MovePtr> ms, size_t goal)
{
  return 0;
}

SLList<MovePtr> careful_player(SLList<Card> cs, size_t goal)
{
  return SLList<MovePtr>();
}
