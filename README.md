# **PROGETTO DI PRINCIPI E ALGORITMI DELL'INFORMATICA**


# 🚗 Pianificazione Percorso su Autostrada

Progetto finale di **Algoritmi e Strutture Dati** (A.A. 2022–2023).  
Il programma simula una rete di stazioni di servizio con veicoli elettrici a noleggio e consente di pianificare il **percorso ottimale** tra due stazioni, minimizzando il numero di tappe e rispettando le autonomie dei veicoli disponibili.

## 🧠 Descrizione del problema

Ogni stazione è posizionata a una certa distanza (intero positivo) dall'inizio dell’autostrada ed è dotata di un numero di veicoli elettrici, ciascuno con una propria autonomia. Il conducente può noleggiare un veicolo da una stazione per raggiungere altre stazioni, ma non può tornare indietro e deve noleggiare un nuovo veicolo a ogni tappa.

L'obiettivo è pianificare il percorso tra due stazioni minimizzando il numero di tappe. Se esistono più percorsi equivalenti, si privilegia quello che utilizza le stazioni più vicine all’inizio dell’autostrada.

## 📄 Formato dei comandi

Il programma legge da **standard input** una sequenza di comandi testuali. Ogni comando produce una stampa su standard output.

### Comandi disponibili

- `aggiungi-stazione D N A1 A2 ... AN`  
  Aggiunge una stazione alla distanza `D` con `N` veicoli di autonomia `A1, A2, ..., AN`.  
  **Risposta:** `aggiunta` oppure `non aggiunta`.

- `demolisci-stazione D`  
  Rimuove la stazione alla distanza `D`.  
  **Risposta:** `demolita` oppure `non demolita`.

- `aggiungi-auto D A`  
  Aggiunge un'auto con autonomia `A` alla stazione in `D`.  
  **Risposta:** `aggiunta` oppure `non aggiunta`.

- `rottama-auto D A`  
  Rimuove un'auto con autonomia `A` dalla stazione in `D`.  
  **Risposta:** `rottamata` oppure `non rottamata`.

- `pianifica-percorso S T`  
  Pianifica il percorso da `S` a `T`.  
  **Risposta:** una sequenza di distanze delle stazioni visitate o `nessun percorso`.

## ▶️ Esecuzione

### Compilazione

Il progetto è scritto in **C**. Per compilare:

```bash
gcc -o autostrada progettoFInal.c
```

### Esecuzione

Puoi eseguire il programma leggendo da file:

```bash
./autostrada < input.txt
```

Oppure interattivamente inserendo i comandi da tastiera.

## 🧱 Strutture dati utilizzate

- **Albero binario di ricerca (BST)** per gestire le stazioni ordinate per distanza.
- **Alberi BST** per gestire i veicoli all'interno di ciascuna stazione.
- **Array** per rappresentare i percorsi possibili nella pianificazione.
- Algoritmo di **visita a larghezza limitata** per trovare il percorso ottimale.

## 📚 Esempio di utilizzo

### Input

```
aggiungi-stazione 20 2 5 10
aggiungi-stazione 30 1 20
aggiungi-stazione 45 1 40
aggiungi-stazione 50 1 30
pianifica-percorso 20 50
```

### Output

```
aggiunta
aggiunta
aggiunta
aggiunta
20 30 50 
```

## 👨‍💻 Autore

*Leonardo Lei.*
