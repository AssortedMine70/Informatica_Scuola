# Livello Transport

## Indice

1 - Caratteristiche dei Servizi Offerti a livello Transport
	
	1.1 - Segmentazione all'interno dell'incapsulamento verticale
	
	1.2 - Livello che ha la funzione di multiplexing del mutliplexing
		
		1.2.1 - concetto di porta logica introdotto da questo livello		
		
			1.2.1.1 - concetto di socket
			
	1.3 - Perchè si dice che è il primo livello che presenta la comunicazione end-to-end a differenza dei livelli sottostanti
		
		1.3.1 - concetto di porta logica introdotto da questo livello		
			
			1.3.1.1 - concetto di socket
			
2 - Elenco protocolli del livello

	2.1 - TCP
	
		2.1.1 - concetto di connessione
		
	2.2 - UDP
	
3 - Caratteristiche principali dei protocolli del livello e confronto

4 - Header dei protocolli del livello

## 1. Caratteristiche dei servizi offerti a livello Transport

Il livello Transport è responsabile della creazione di una sessione di comunicazione temporanea tra due applicazioni e della consegna dei dati tra di esse. Un'applicazione genera dati che vengono inviati da un'applicazione in un host di origine a un'applicazione in un host di destinazione. Questo avviene indipendentemente dal tipo di host di destinazione, dal tipo di supporto di comunicazione per la trasmissione dei dati, dal percorso seguito, dalla congestione in un collegamento o dalle dimensioni della rete. Il livello Transport rappresenta il collegamento tra il livello applicazione e i livelli inferiori responsabili della trasmissione di rete.

### 1.1. Monitoraggio di singole conversazioni

A livello Transport, l'insieme di dati che vengono scambiati per far comunicare i due dispositivi viene definito **conversazione**: questo livello è responsabile del monitoraggio e della gestione delle conversazioni di cui un Host può disporre simultaneamente. Ogni applicazione che comunica via rete dispone infatti della sua propria conversazione.

### 1.2. Segmentazione dei dati e riassemblaggio dei segmenti

Perchè i dati del livello Application siano inviabili su internet secondo le limitazioni dei protocolli sottostanti e dei supporti di comunicazione, il livello Transport dispone di appositi servizi per svolgere una funzione di **segmentazione** dei dati ricevuti dal livello Application in dimensioni appropriate. Viene poi aggiunto un header che varia dal protocollo utilizzato di livello Transport. Questi header contengono anche le informazioni con cui riassembleare i segmenti una volta ricevuti dall'altro Host e permettono .

### 1.3. Identificazione delle applicazioni

Per trasmettere i flussi di dati alle applicazioni appropriate, il livello Transport deve identificare l'applicazione di destinazione. A tale scopo, assegna a ogni applicazione un identificatore chiamato numero di porta. Tutti i processi software che devono accedere alla rete ricevono un numero di porta univoco nell'Host.

## 1.4. Multiplexing delle conversazioni

In una rete, l'invio di alcuni tipi di dati come un unico flusso di comunicazione può consumare tutta la larghezza di banda disponibile, ostacolando il funzionamento di altre comunicazioni contemporanee, oltre a complicare il recupero degli errori e la ritrasmissione di dati danneggiati. Il frazionamento dei dati in segmenti più piccoli consente che molte comunicazioni diverse provenienti da molti utenti diversi possano essere intrecciate (multiplexing) sulla stessa rete.

// REVISIONA

Per identificare ogni segmento dei dati, il livello trasporto aggiunge un header contenente dati binari organizzati in diversi campi. I valori contenuti in questi campi permettono ai diversi protocolli del livello trasporto di eseguire diverse funzioni nella gestione della comunicazione dei dati.
