// Solution by Alejandro J. Mujica (aledrums@gmail.com)

Color card_color(const Card & c)
{
  return static_cast<int>(get<0>(c)) <= 1 ? Color::Black : Color::Red;
}

size_t card_value(const Card & c)
{
  switch (get<1>(c))
    {
    case Rank::Ace:                 return 11;
    case Rank::Jack ... Rank::King: return 10;
    default:                        return static_cast<size_t>(get<1>(c)) + 1;
    }
}

SLList<Card> remove_card(const SLList<Card> & cs, const Card & c)
{
  auto ret = cs.filter([c] (auto cc) { return c != cc; });
  
  if (ret.size() == cs.size()) throw CardExcept::IllegalMove;

  return ret;
}

bool all_same_color(const SLList<Card> & cs)
{
  if (cs.is_unitarian_or_empty()) return true;
  
  Color color = card_color(cs.get_first());
  
  return cs.all([color] (auto c) { return card_color(c) == color; });
}

size_t sum_cards(const SLList<Card> & cs)
{
  return cs.fold(0UL, [] (auto c, auto acc) { return card_value(c) + acc; });
}

size_t score(const SLList<Card> & cs, size_t goal)
{
  auto sum    = sum_cards(cs);
  auto result = (sum > goal) ? 3 * (sum - goal) : (goal - sum);

  if (all_same_color(cs))
    result /= 2;

  return result;
}

size_t officiate(SLList<Card> cs, SLList<MovePtr> ms, size_t goal)
{
  SLList<Card> hs;
  
  while (not ms.is_empty())
    {
      auto m = ms.remove_first();

      if (*m) // Discard
	{
	  hs = remove_card(hs, m->card());
	  continue;
	}

      // Draw
      if (cs.is_empty())
	return score(hs, goal);

      hs.insert(cs.remove_first());

      if (sum_cards(hs) > goal)
	return score(hs, goal);
    }
  
  return score(hs, goal);
}

SLList<MovePtr> careful_player(SLList<Card> cs, size_t goal)
{
  SLList<Card>    hs;
  SLList<MovePtr> ms;

  while (score(hs, goal) != 0)
    {
      if (cs.is_empty())
	{
	  ms.append(create_draw_move());
	  return ms;
	}

      if (goal > (sum_cards(hs) + 10))
	{
	  hs.insert(cs.remove_first());
	  ms.append(create_draw_move());
	}
      else
	{
	  auto sum = sum_cards(hs) + card_value(cs.get_first());

	  if (sum <= goal)
	    {
	      hs.insert(cs.remove_first());
	      ms.append(create_draw_move());
	    }
	  else if (hs.is_empty())
	    {
	      ms.append(create_draw_move());
	      return ms;
	    }
	  else
	    ms.append(create_discard_move(hs.remove_first()));
	}
    }

  return ms;
}
