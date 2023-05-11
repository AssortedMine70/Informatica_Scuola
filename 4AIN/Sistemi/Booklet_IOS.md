
# Booklet sulla Comandistica Cisco
Federico Santucci, 2022
***
### Pulsanti Utili
1. **TAB**
    Autocompleta il comando se non ambiguo. Operazione evitabile premendo direttamente Invio.
2. **Freccia Su / Freccia Giù**
    Utilizzabili per navigare la cronologia dei comandi già inseriti precedentemente.
### Comandi Generici
1. **?**
Lista di Comandidisponibili in quella modalità o di seguito a quel comando. Si possono navigare i risultati mostrati con `SPACE`, che avanzerà di pagina per pagina, o con `RETURN`, che avanzerà di riga in riga.
    ```
    SW>telnet ?
        WORD    IP address or hostname of remote system
    ```
2. **do** (d)
Esegue il comando che lo segue al livello in cui si era in precedenza.
    ```
    Switch(config)#do show clock
    *0:9:5.983 UTC Mon Mar 1 1993
    ```
3. **exit** ( )
Esce dalla modalità corrente per tornare alla precedente.
    ```
    Switch(config)#exit
    Switch#
    ```
 
### User Exec (>)
1. **enable** (en)
    Passa a **Priviledged Excec**.
    ```
    SW>enable
    SW#
    ```
2. **show** ( )
    Stampa a schermo.
    - **clock** ( )
        Mostra l'orologio di sistema.
        ```
        SW>show clock
        *0:9:5.983 UTC Mon Mar 1 1993
        ```

### Priviledged Exec (#)
Molti comandi eseguibili in **User Exec** sono comunque ancora eseguibili.
1. **disable** (en)
    Passa a **User Excec**.
    ```
    SW#disable
    SW>
    ```
2. **clock** ( )
    Impostazioni riguardanti l'orologio di sistemia.
    - **set** (s) HH:MM:SS DAY MONTH YEAR
        Imposta l'orologio di sistema.
        ```
        SW#clock set 22:20:00 3 NOV 2022
        ```
3. **configure** (conf)
    -  **terminal** (t)
        Passa a **Configure > Terminal**.
        ```
        SW#configure terminal
        SW(config)#
        ```
4. **copy** ( ) SRC DST
    Copia il file `SRC` nel file `DST`.
   ```
   SW#copy running-config startup-config
   ```
5. **show** ( )
    Stampa a schermo.
    - **ip** ()
	    - **route** ()
		   Mostra la rabella di routing del Router.
		   ```
		  Router#show ip route
		  ```
### Configure
- **Comandi Generici**
    1. **no** (n)
        nega un comando precedentemente scritto, togliendolo quindi dalla **Running Config**.
        ```
        SW(config)#no enable secret
        ```
- **Terminal**
	1. **enable** (ena)
    Imposta una password per il passaggio da **User Exec** a **Priviledged Exec**.
        - **password** \(p\) PASSWORD
            Salvataggio in chiaro della password nel **Running Config**.
            ```
            SW(config)#enable password PASSWORD
            ```
        - **secret** (s) PASSWORD
            Sakvataggio criptato della password nel **Running Config**.
            ```
            SW(config)#enable secret PASSWORD
	2. **line** ( )
        - **console**/**vty <0-n>**
            Passa alla configurazione di un metodo di accesso al dispositivo.
            ```
            SW(config)#line vty 3-5
            SW(config-line)#
            ```
            Dentro **config-line**:
            - **password** () PASSWORD
                Imposta una password per accedere all'interfaccia che si sta configurando.
                ```
                SW(config-line)#password PASSWORD
                ```
            - **login** ()
                Abilita l'accesso a quella porta.
                ```
                SW(config-line)#login
                ```
	3. **interface** () 
        - **vlan <0-n>**
            Passa alla configurazione di un interfaccia.
            ```
            SW(config)#interface vlan 7-10
            SW(config-if)#
            ```
            Dentro **config-if**:
            - **ip address** IP SUBNETMASK
            Imposta IP e Subnet Mask del dispositivo.
                ```
                SW(config-if)#ip address 192.168.0.254 255.255.255.0
                ```
	4. **service** (se)
        Serve per abilitare diversi servizi.
        - **password-encryption** \(p\)
            Abilita il servizio di criptazione delle password, che quindi cripterà tutte le password salvate nel **Running Config** e cripterà quelle che poi verranno impostate successivamente.
         ```
        SW(config)#service password-ecryption
        ```
	5. **banner** (ba) **motd** (m) LINE
        Imposta il banner, che verrà visualizzato ad ogni riavvio del dispositivo. Il primo carattere di LINE sarà un delimitatore, che quando verrà riscritto indicherà la fine di LINE (nell'esempio `"`).
        ```
        SW(config)#banner motd "LINE"
        ```
	6. **hostname** ( ) HOSTNAME
        Configura l'Hostname.
        ```
        SW(config)#hostname HOSTNAME
        ```
	7. **ip** ( )
		- **route** ( )  NETWORK NETMASK GATEWAY
		   Aggiunge una rotta statica al router.
		```
        Router(config)#ip route 192.168.5.0 255.255.255.0 192.168.10.254
        ```
