// Standard headers
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

// Internal headers
#include "direction.h"
#include "position.h"
#include "spy.h"

// Main header
#include "attacker.h"

// Added *

// Macros
#define UNUSED(x) (void)(x) // Auxiliary to avoid error of unused parameter

/*----------------------------------------------------------------------------*/
/*                              PUBLIC FUNCTIONS                              */
/*----------------------------------------------------------------------------*/

enum {up, down};

int sorteia_numero() {
  return rand();
}

bool equal_directions(direction_t d1, direction_t d2) {
  if(d1.i == d2.i && d1.j == d2.j)
    return true;

  return false;
}

void atualiza_ult_dir(direction_t ultima_dir[3], direction_t atual) {
  ultima_dir[2] = ultima_dir[1];
  ultima_dir[1] = ultima_dir[0];
  ultima_dir[0] = atual;
}

direction_t execute_attacker_strategy(
    position_t attacker_position, Spy defender_spy) {
  // TODO: unused parameters, remove these lines later
  UNUSED(defender_spy);

  // TODO: Implement Attacker logic here
  int aux; 
  int seed;
  direction_t result;
  static int rodada = 0;
  static int rounds_parado = 0;
  static direction_t ini_dir;
  static direction_t ultima_dir[3];
  static position_t ultima_pos;

  if(!rodada) {
    srand(time(0));
    seed = rand()%2;

    ultima_dir[2] = ultima_dir[1] = ultima_dir[0] = (direction_t) DIR_STAY;

    switch(seed){
      case up: 
        ini_dir = (direction_t) DIR_UP;
        break;

      case down:
        ini_dir = (direction_t) DIR_DOWN;
        break;

      default:
        ini_dir = (direction_t) DIR_STAY;
    }

    result = ini_dir;
  }

  else {

    if(equal_positions(ultima_pos, attacker_position)) {
      rounds_parado++;

      switch(rounds_parado) {
        case 1:

          if (equal_directions(ultima_dir[0], (direction_t) DIR_UP) ||
              equal_directions(ultima_dir[0], (direction_t) DIR_DOWN)) {
              if(equal_directions(ultima_dir[1], (direction_t) DIR_LEFT))
                result = (direction_t) DIR_LEFT;
              else 
                result = (direction_t) DIR_RIGHT;
            }

          
          else {
            if(equal_directions(ini_dir, (direction_t) DIR_DOWN))
              result = (direction_t) DIR_UP;
            else
              result = (direction_t) DIR_DOWN;
          }
          break;

        case 2:
          if (equal_directions(ultima_dir[0], (direction_t) DIR_UP))
            result = (direction_t) DIR_DOWN;
          else if (equal_directions(ultima_dir[0], (direction_t) DIR_DOWN))
            result = (direction_t) DIR_UP;
          else
            result = (direction_t) DIR_LEFT;
          break;
          
        case 3:
          if (equal_directions(ultima_dir[3], (direction_t) DIR_UP))
            result = (direction_t) DIR_DOWN;
          else if (equal_directions(ultima_dir[3], (direction_t) DIR_DOWN))
            result = (direction_t) DIR_UP;
          else if (equal_directions(ultima_dir[3], (direction_t) DIR_RIGHT))
            result = (direction_t) DIR_LEFT;
          else result = (direction_t) DIR_RIGHT;
          break;

        default:
          printf("Erro. Valor inesperado.\n");
          result = (direction_t) DIR_STAY;
      }

    }

    else {
      rounds_parado = 0;

      if(equal_directions(ultima_dir[0], (direction_t) DIR_LEFT)) {
        aux = rand()%2;
        if (aux == up)
          result = (direction_t) DIR_UP;
        else
          result = (direction_t) DIR_DOWN;

      } else
        result = ultima_dir[0];
    }

  }

  rodada++;
  ultima_pos = attacker_position;
  atualiza_ult_dir(ultima_dir, result);

  return result;
}

/*----------------------------------------------------------------------------*/
