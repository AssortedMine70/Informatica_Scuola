# Routing e Network Configuration su Debian

## 1. File di configurazione di rete

### 1.1. Mostrare la configurazione corrente
` ip a `

### 1.2. Path per modificare la configurazione
` etc/network/interfaces `

#### Configurazione di esempio
``` interfaces
allow hotplug ens33
auto ens33
iface ens33 inet static
    address 192.168.1.1
    netmask 255.255.255.0
    broadcast 192.168.1.255
    gateway address 192.168.1.100
```

## 2. Configurazione delle rotte statiche

### 2.1. Aggiunta di una rotta
` ip route add DESTINATION_NETWORK via NEXT_HOP dev ENS `

### 2.2. Rimozione di una rotta
` ip route delete ... `

### 2.3. Show delle rotte configurate
` ip route show `

## 3. Configurazione dell'IP forwarding
in ` /etc/sysctl.conf ` scommenta:
```
net.ipv4.ip_forward=1
```

## 4. Comandi per riavviare servizi

### 4.1. Networking Service
` service networking restart ` (necessario per net config)

### 4.2 Systctl
` service systemd-sysctl restart ` (necessario per IPv4 forwarding)

Usefull info:

/etc/network/interfaces and /etc/sysctl.conf need sudo to edit

first net iface is ens33, second is usally ens36

routers need routes only for nets they are not interfaced with
