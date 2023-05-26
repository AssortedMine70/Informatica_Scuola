# Routing e Network Configuration su Debian

## 1. File di configurazione di rete

### 1.1. Mostrare la configurazione corrente
` ip a `

### 1.2. Path per modificare la configurazione
` /etc/network/interfaces `

<aside>
💡 /etc/network/interfaces necessita di sudo per essere modificato.
    
</aside>

#### Configurazione di esempio
``` interfaces
allow hotplug ens33
auto ens33
iface ens33 inet static
    address 192.168.1.1
    netmask 255.255.255.0
    network 192.168.1.0
    broadcast 192.168.1.255
    gateway 192.168.1.100
```

## 2. Configurazione delle rotte statiche

### 2.1. Aggiunta di una rotta
` ip route add DESTINATION_NETWORK/NM via NEXT_HOP dev ENS `

### 2.2. Aggiunta di una rotta di default
` ip route add default via NEXT_HOP `

### 2.3. Rimozione di una rotta
` ip route delete ... `

### 2.4. Show delle rotte configurate
` ip route show `

## 3. Configurazione dell'IP forwarding
in ` /etc/sysctl.conf ` scommenta:
```
net.ipv4.ip_forward=1
```

<aside>
💡 /etc/sysctl.conf necessita di sudo per essere modificato.
    
</aside>

## 4. Comandi per riavviare servizi

### 4.1. Networking Service
` service networking restart ` (necessario per net config)

oppure

` systemctl restart networking `

### 4.2. Systctl
` service systemd-sysctl restart ` (necessario per IPv4 forwarding)

# Comandi Utili su Windows

## 1. ipconfig
` ipconfig ` mostra la configurazione delle varie interfacce di rete.

## 2. route

` route print ` stampa a schermo le rotte impostate.
` route ADD <destination_network> MASK <subnet_mask> <gateway_ip> [metric_cost] ` per impostare una nuova rotta statica.

<aside>
💡 Le rotte impostate in questo modo vengono perse ad un eventuale riavvio.
    
</aside>
