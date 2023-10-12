# Rapport tp1

## 1

### 1.1

On remarque que le PGRP est le même que le PID, il y a donc par défaut un groupe créé par processus

### 1.2

La fonction stop_handler est exécutée et remplace le comportement par défaut si le bon signal est envoyé (ici SIGINT au début ou SIGTERM si kill est utilisé sans rien). kill -9 en revanche envoie un signal qui ne peut pas être utilisé et qui interromp donc toujours le processus.

### 1.3

atexit est activée peut importe le signal sauf avec kill -9

## 2

### 2.1

tous les processus d'un même groupe s'arrêtent en même temps car le terminal envoie le signal à tous les processus du groupe actif de la session. Selon la doc:

> If a signal is generated from the
       terminal (e.g., typing the interrupt key to generate SIGINT),
       that signal is sent to the foreground process group.

le processus fils est zombifié lorsqu'il est kill jusqu'a ce que le processus père soit kill.

Lorsqu'on tue le père le fils est adopté par le grand père.

### 2.2

On remarque bien que par défaut Ctrl + C et kill sur l'un des 2 autres kill le deuxième. On doit juste ajouter un sigaction au père pour le cas où l'enfant est kill afin qu'il affiche toujours son lessage de fin.

## 3

### 3.1

On a le comportement attendu. Le serveur commence la communication en envoyant son pid et envoie un message de fin de communication sur le fifo quand il est kill.

## 4

### 4.1

