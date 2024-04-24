# PAA_Project_UnrealChess
Realizzazione di un semplice client per il gioco degli scacchi (2D) in Unreal Engine 5.2
## Specifiche che il progetto deve rispettare
Steps:
- [X] Griglia con scacchi graficamente corretti
- [X] Il gioco funziona a turni e termina quando un giocatore vince
- [X] Suggerimenti delle mosse possibili per ciascun pezzo cliccando sullo stesso
- [X] AI utilizzando mosse random (fra quelle possibili)
- [ ] AI utilizzando minimax
- [ ] Storico delle mosse con interfaccia grafica 
	- [Notazione su chess.com](https://www.chess.com/terms/chess-notation)
- [ ] Replay (cliccando su una mossa nello storico lo stato della scacchiera viene riportato indietro a quello stato)
	- **TIP:** Tenere un array che conserva gli stati della scacchiera (oppure risalire le mosse precedenti)

Misc:
- [ ] Compila correttamente
- [ ] Codice ben commentato
- [ ] Codice ben strutturato 
## Note per il progetto
Per lo sviluppo del progetto si utilizza:
- Unreal Engine 5.2
- Codice di programmazione C++
- Utilizzo di Blueprint solo dove strettamente necessario
NON VERRANNO VALUTATI PROGETTI:]
- SVILUPPATI CON UN ALTRO MOTORE GRAFICO 
- SVILUPPATI CON UNA VERSIONE DI UNREAL ENGINE DIFFERENTI DALLA 5.2
- SVILUPPATI CON CODICE DIVERSO DA C++
- SVILUPPATO INTERAMENTE UTILIZZANDO BLUEPRINT
- CHE DANNO ERRORE IN FASE DI COMPILAZIONE

## Risorse che ho utilizzato
- [Set dei pezzi: kiwen-suwi](https://github.com/lichess-org/lila/tree/master/public/piece)
- [PNG Import](https://www.youtube.com/watch?v=g9x1xljJau0)

## Set di risorse per la logica del gioco
- [ ] https://www.youtube.com/playlist?list=PLFk1_lkqT8MahHPi40ON-jyo5wiqnyHsL
## Risorsa utile per minimax
- [ ] https://lichess.org/@/JoaoTx/blog/making-a-simple-chess-engine/fGBIAfGB
## Altro
Idea iniziale di come realizzare le classi dei pezzi ![Pieces_UML](./Ideas/PiecesUML)
- [ ] [Avere la scacchiera perpendicolare alla telecamera](https://www.youtube.com/watch?v=yaVKOwaMoLY)