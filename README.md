# Turtle Graphics

Questo programma implementa un semplice strumento di grafica turtle in C. Consente di disegnare su una griglia rettangolare con una tartaruga che può muoversi in quattro direzioni: alto, basso, destra e sinistra. La griglia è di dimensioni massime 100x25, con la possibilità di specificare le dimensioni durante l'esecuzione del programma.

## Comandi della Tartaruga

La tartaruga può eseguire i seguenti comandi:

- **Alzare la penna**: la tartaruga smette di disegnare mentre si sposta sulla griglia.
- **Abbassare la penna**: la tartaruga inizia a disegnare mentre si sposta sulla griglia.
- **Girare a destra**: la tartaruga cambia direzione di 90 gradi verso destra.
- **Girare a sinistra**: la tartaruga cambia direzione di 90 gradi verso sinistra.
- **Andare avanti**: la tartaruga si sposta in avanti di un numero specificato di spazi.
- **Uscire dal programma**: termina l'esecuzione del programma.

## Caratteristiche della Griglia

- La griglia è inizialmente vuota.
- La griglia è visualizzata completamente ogni volta che viene inserito un nuovo comando.
- I confini della griglia sono delimitati da una cornice.
- La tartaruga è rappresentata con il simbolo "O" quando la penna è alzata e con il simbolo "I" quando la penna è abbassata.
- La traccia lasciata dalla tartaruga con la penna abbassata è rappresentata dal simbolo "*".

## Build del Programma

Per compilare il programma, basta digitare `make` nel terminale. Assicurati di avere un compilatore C installato nel tuo sistema.

## Esecuzione del Programma

Dopo aver compilato il programma, puoi eseguirlo direttamente dal terminale. Segui le istruzioni visualizzate per interagire con la tartaruga e disegnare sulla griglia.

### Note

- La tartaruga non può uscire dai confini della griglia. Se si tenta di spostarla oltre i confini, verrà spostata al confine della griglia.
- La dimensione massima della griglia è 100x25.

Divertiti a disegnare con la tua tartaruga! 🐢🎨
