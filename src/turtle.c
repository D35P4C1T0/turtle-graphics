#include <stdio.h>
#include <string.h>

#define MAXW 100
#define MAXH 25

#define simboloTartaruga 'O'
#define simboloPenna '|'
#define stroke '*'

struct Cursore {
  char simbolo;
  char direzione;  // N, S, W, E per su, giù, sinistra e destra
  int x, y;
  int inSrittura;
  char carattereCalpestato;
} cursore = {.simbolo = simboloTartaruga,
             .direzione = 'N',
             .x = 1,
             .y = 1,
             .carattereCalpestato = ' '};

char tela[MAXH][MAXW];

/////////////// pre-dichiaro le funzioni ////////////////
void alzaPenna() {
  cursore.simbolo = simboloTartaruga;
  cursore.inSrittura = 0;
}
void abbassaPenna() {
  cursore.simbolo = simboloPenna;
  cursore.inSrittura = 1;
}
void liberaSchermo() { printf("\e[1;1H\e[2J"); }  // unix only
////////////////////////////////////////////////////////
void preparaTela(int h, int w);
void stampaTela(int h, int w);
int trasla(int passi, int h, int w);
void cambiaDirezioneDi90Gradi(int clockwise);
void disegna(int passi, int h, int w);
////////////////////////////////////////////////////////

int main() {
  int larghezzaTela = 1, altezzaTela = 1;
  printf(
      "Inserisci la larghezza e l'altezza della tela separati da uno spazio: ");
  scanf("%d %d", &larghezzaTela, &altezzaTela);

  // misura forzata della tela se sopra o sotto i valori predisposti
  larghezzaTela = larghezzaTela < MAXW ? larghezzaTela : MAXW;
  altezzaTela = altezzaTela < MAXH ? altezzaTela : MAXH;
  larghezzaTela = larghezzaTela > 2 ? larghezzaTela : 3;
  altezzaTela = altezzaTela > 2 ? altezzaTela : 3;
  cursore.x = larghezzaTela / 2;
  cursore.y = altezzaTela / 2;

  // il gioco inizia
  char scelta;
  int passi = 0;
  preparaTela(altezzaTela, larghezzaTela);  // bordi estetici

  while (scelta != '9') {
    stampaTela(altezzaTela, larghezzaTela);
    printf(
        "Comanda la tartaruga con la tastiera.\nOrientamento attuale "
        "tartaruga: %c \n1 alza\n2 abbassa\n3 gira in senso orario\n4 gira in "
        "sensoantiorario\n5,n avanti di n\n9 esci\nComando: ",
        cursore.direzione);

    scanf("%c,%d", &scelta, &passi);

    switch (scelta) {
      case '1':
        alzaPenna();
        break;

      case '2':
        abbassaPenna();
        break;

      case '3':
        cambiaDirezioneDi90Gradi(1);  // orario
        break;

      case '4':
        cambiaDirezioneDi90Gradi(0);  // antiorario
        break;

      case '5':
        if (cursore.inSrittura)
          disegna(passi, altezzaTela, larghezzaTela);
        else
          trasla(passi, altezzaTela, larghezzaTela);

      default:
        break;
    }
  }
  return 0;
}

void preparaTela(int h, int w) {
  int i, j;
  for (i = 0; i < h; i++)
    for (j = 0; j < w; j++) tela[i][j] = ' ';

  for (i = 0; i < h; i++) {
    tela[i][0] = '|';
    tela[i][w - 1] = '|';
  }
  for (i = 0; i < w; i++) {
    tela[0][i] = '-';
    tela[h - 1][i] = '-';
  }
}

void stampaTela(int h, int w) {
  liberaSchermo();
  tela[cursore.y][cursore.x] = cursore.simbolo;
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) printf("%c", tela[i][j]);
    printf("\n");
  }
}

int movimentoValido(int passi, int h, int w) {
  switch (cursore.direzione) {
    case 'N':
      if (cursore.y - passi < 1) return 0;
      break;

    case 'S':
      if (cursore.y + passi > h - 1) return 0;
      break;

    case 'W':
      if (cursore.x - passi < 1) return 0;
      break;

    case 'E':
      if (cursore.x + passi > w - 1) return 0;
      break;

    default:
      break;
  }
  return 1;  // caso positivo
}

int trasla(int passi, int h, int w) {  // 1 se true
  if (movimentoValido(passi, h, w)) {
    int precedenteX = cursore.x;
    int precedenteY = cursore.y;
    switch (cursore.direzione) {
      case 'N':
        cursore.y -= passi;
        break;

      case 'S':
        cursore.y += passi;
        break;

      case 'W':
        cursore.x -= passi;
        break;

      case 'E':
        cursore.x += passi;
        break;

      default:
        break;
    }

    /*
    Siccome la tartaruga si sposta e il suo carattere copre la tavola, può
    capitare che la tartaruga si metta sopra ad un tratto disegnato.
    Immagazzinare il carattere sopra cui la tartaruga si è poggiata mi serve per
    poter muoverla senza che essa cancelli banalmente il pezzo di tavola che
    prima dello spostamento occupava.
    */
    tela[precedenteY][precedenteX] = cursore.carattereCalpestato;
    cursore.carattereCalpestato = tela[cursore.y][cursore.x];
    return 1;
  }
  return 0;  // caso negativo
}

void cambiaDirezioneDi90Gradi(int clockwise) {
  switch (cursore.direzione) {
    case 'N':
      cursore.direzione = clockwise == 1 ? 'E' : 'W';
      break;

    case 'S':
      cursore.direzione = clockwise == 1 ? 'W' : 'E';
      break;

    case 'W':
      cursore.direzione = clockwise == 1 ? 'N' : 'S';
      break;

    case 'E':
      cursore.direzione = clockwise == 1 ? 'S' : 'N';
      break;

    default:
      break;
  }
}

void disegna(int passi, int h, int w) {
  int passiEseguiti = 0;
  if (movimentoValido(passi, h, w)) {
    switch (cursore.direzione) {
      case 'N':
        for (int i = cursore.y; passiEseguiti != passi; i--) {
          tela[i][cursore.x] = stroke;
          passiEseguiti++;
        }
        passiEseguiti = 0;
        break;

      case 'S':
        for (int i = cursore.y; passiEseguiti != passi; i++) {
          tela[i][cursore.x] = stroke;
          passiEseguiti++;
        }
        passiEseguiti = 0;
        break;

      case 'W':
        for (int i = cursore.x; passiEseguiti != passi; i--) {
          tela[cursore.y][i] = stroke;
          passiEseguiti++;
        }
        passiEseguiti = 0;
        break;

      case 'E':
        for (int i = cursore.x; passiEseguiti != passi; i++) {
          tela[cursore.y][i] = stroke;
          passiEseguiti++;
        }
        passiEseguiti = 0;
        break;

      default:
        break;
    }
    cursore.carattereCalpestato = stroke;
    // la tartaruga sta sull'ultimo pezzo del tratto
    // dopo aver disegnato la riga sposto il cursore alla
    // fine della riga
    trasla(passi, h, w);
  }
}