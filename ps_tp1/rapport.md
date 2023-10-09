# Rapport tp1

## 1

### 1.1

On remarque que le PGRP est le même que le PID, il y a donc par défaut un groupe créé par processus

### 1.2

La fonction stop_handler est exécutée et remplace le comportement par défaut si le bon signal est envoyé (ici SIGINT au début ou SIGTERM si kill est utilisé sans rien). kill -9 en revanche envoie un signal qui ne peut pas être utilisé et qui interromp donc toujours le processus.