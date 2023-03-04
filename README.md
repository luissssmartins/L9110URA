# L9110URA (conhecido como URINHA)

![1](https://raw.githubusercontent.com/luissssmartins/L9110URA/main/images/L9110URA.jpg)

## Comandos básicos

* FRT: anda para frente;
* TRS: anda para trás;
* DIR: vira para direita em torno de seu próprio eixo;
* ESQ: vira para esquerda em torno de seu próprio eixo;
* PAR: para o robô;
* FTT: anda para frente durante um X tempo determinado;
* TRT: anda para trás durante um X tempo determinado;
* DRT: anda para direita durante um X tempo determinado em torno de seu próprio eixo;
* EST: anda para esquerda durante um X tempo determinado em torno de seu próprio eixo;

## Comandos avançados:

* MTP: ajusta a "potência" de ambos os motores entre valores -100 (mais lento) à 100 (mais rápido);
* Programação: possui intuito de realizar uma sequência de comandos separados por ponto e vírgula ';'. Para se iniciar uma programação requer
a primeira instrução dada por 'PRG';

## Configuração de todos os pinos referentes ao GPIO

### Ponte H 

| Ponte H L9110  | ESP32 |
| --------------- | --------------- | 
| B-1A | D5 |
| B-1B | D23 |
| G  | GND  | 
| VCC | Vin (5v) | 
| A-1A | D13 | 
| A-1B | D12 | 

### Sensor de distância (Ultrassônico) 

| Sensor de distância | ESP32 |
| --------------- | --------------- | 
| GND | GND  | 
| Trig  | D19 | 
| Echo  | D18 |
| Vcc | 3.3v | 

### Sensores de linha 

| Sensor de Linha Esquerdo | ESP32 |
| --------------- | --------------- | 
| G  | GND  | 
| V+ | 3.3v | 
| S  | D14 | 


| Sensor de Linha Direito | ESP32 |
| --------------- | --------------- | 
| G  | GND  | 
| V+ | 3.3v | 
| S  | D27 |

## Configuração dentro do MCU

```bash
{
    "ssid" : "SSID",
    "ssid_password": "PASSWORD",
    "mqtt_address": "XXX.XXX.XXX.XXX",
    "mqtt_port": 1883,
    "mqtt_user": "USER",
    "mqtt_password": "PASSWORD",
    "topic_sub": "URA0XX/input",
    "topic_pub": "URA0XX/output"
}

```

## Configuração do Web Repl

```bash

# Utilizando seu IDE de preferência, abra o terminal do Python e siga o passo a passo padrão definido pelo setup:

>> import webrepl_setup

# Por padrão o Web Repl é desativado ao iniciar o ESP, portanto, habilite-o.

WebREPL daemon auto-start status: disabled

Would you like to (E)nable or (D)isable it running on boot?
(Empty line to quit the setup)

> E

# É recomendado adicionar uma senha para ser logada no sistema interno.

To enable WebREPL, you must set password for it
New password: <defina uma senha>
Confirm password: <repita a senha>

# Após, a conclusão do passo a passo, reinicie o esp-32 para aplicar as alterações.

Changes will be activated after reboot
Would you like to reboot now? (y/n) y

```

## Baixando a interface WebRepl

* Baixe o repositório do client web repl neste repositório [Client WebRepl](https://github.com/micropython/webrepl)


