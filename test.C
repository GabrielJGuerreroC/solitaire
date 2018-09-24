# include <cassert>
# include <iostream>
# include <sstream>
# include <tuple>
# include <stdexcept>
# include <memory>

using namespace std;

# include <list.H>

using namespace Designar;

# include <defs.H>
# include <solitaire.H>

int main()
{
  assert(card_color(Card(Suit::Spades, Rank::Jack)) == Color::Black);
  
  assert(card_value(Card(Suit::Spades, Rank::Ace)) == 11);
  
  assert(remove_card({Card(Suit::Hearts, Rank::King)},
		     Card(Suit::Hearts, Rank::King)).equal(SLList<Card>()));
  
  assert(all_same_color({Card(Suit::Spades, Rank::Three)}));
  
  assert(sum_cards({Card(Suit::Spades, Rank::Three)}) == 3);
  
  assert(score({Card(Suit::Hearts, Rank::Two),
	  Card(Suit::Clubs, Rank::Four)}, 10) == 4);
  
  assert(officiate({Card(Suit::Hearts, Rank::Two),
	  Card(Suit::Clubs, Rank::Four)},
      {create_draw_move()}, 15) == 6);
  

  /* Note que careful_player retorna una lista de MovePtr
     (a.k.a. std::shared_ptr<Move>). A la lista resultante se le llama
     al método equal con otra lista (podría ser cualquier otro contenedor). Este
     método está instrumentado en conaineralgorithms.H y se basa en
     el implementado en italgorithms.H. Por omisión el compara con el operador
     == las claves almacenadas en los contenedores. Debemos recordar que la
     lista de movimientos almacena apuntadores, comparar apuntadores sería 
     incorrecto. Por esa razón se pasa como segundo parámetro el criterio de
     comparación que se encarga de decir que debe comparar lo apuntado.
  */
  assert(careful_player({Card(Suit::Clubs,Rank::Ace),
	  Card(Suit::Spades,Rank::Ace),
	  Card(Suit::Clubs,Rank::Ace),Card(Suit::Spades,Rank::Ace)}, 42).
    equal({create_draw_move(),create_draw_move(),create_draw_move(),
	  create_discard_move(Card(Suit::Clubs,Rank::Ace)),create_draw_move(),
	  create_draw_move()}, [] (auto mp1, auto mp2) {return *mp1 == *mp2;}));
  
  SLList<Card> cs = {Card(Suit::Clubs,Rank::Ace),
		     Card(Suit::Spades,Rank::Ace),
		     Card(Suit::Clubs,Rank::Ace),
		     Card(Suit::Spades,Rank::Ace)};
  
  assert(officiate(cs, {create_draw_move(),create_draw_move(),create_draw_move(),
	  create_draw_move(),create_draw_move()}, 42) == 3);
  
  cout << "Everything ok!\n";
  
  return 0;
}
