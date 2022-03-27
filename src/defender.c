// Standard headers
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

// Internal headers
#include "direction.h"
#include "attacker.h"
#include "position.h"
#include "spy.h"

// Main header
#include "defender.h"

// Macros
#define UNUSED(x) (void)(x) // Auxiliary to avoid error of unused parameter

enum {up, down};

/*----------------------------------------------------------------------------*/
/*                              PUBLIC FUNCTIONS                              */
/*----------------------------------------------------------------------------*/
bool equal_directions_d(direction_t d1, direction_t d2) {
  if(d1.i == d2.i && d1.j == d2.j)
    return true;

  return false;
}

direction_t execute_defender_strategy(
    position_t defender_position, Spy attacker_spy) {

  // TODO: Implement Defender logic here
  //static int seed;
  static direction_t result;
  static position_t ultima_pos;
  static direction_t ultima_dir;
  static position_t attacker_position;
  static bool stay;
  static int rodada = 0;

  if(!rodada) {
    srand(time(0));
    //seed = rand()%2;

    if(rand()%2 == up)
      result = (direction_t) DIR_UP;
    else
      result = (direction_t) DIR_DOWN;

  }

  else {
    if(equal_positions(ultima_pos, defender_position)) {

      if(equal_directions_d(ultima_dir,(direction_t) DIR_UP))
        result = (direction_t) DIR_DOWN;
      else
        result = (direction_t) DIR_UP;
    }
    else
      result = ultima_dir;
  }

  rodada++;
  ultima_dir = result;
  ultima_pos = defender_position;
  return result;
}

/*----------------------------------------------------------------------------*/
