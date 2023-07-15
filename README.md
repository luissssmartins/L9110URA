# L9110URA (conhecido como URINHA)

![1](https://raw.githubusercontent.com/luissssmartins/L9110URA/main/images/L9110URA.jpg)

## Repositório do URA

Também existem outras versões disponíveis

* [Natalnet](https://github.com/Natalnet/ura-codes/)

## Versões disponíveis

Atualmente há duas versões do projeto disponível, veja abaixo:

* [C++](https://github.com/luissssmartins/L9110URA/tree/main/c%2B%2B)
* [MicroPython](https://github.com/luissssmartins/L9110URA/tree/main/micropython)

## Entendendo e configurando a versão em MicroPython:

### Comandos básicos

* FRT: anda para frente;
* TRS: anda para trás;
* DIR: vira para direita em torno de seu próprio eixo;
* ESQ: vira para esquerda em torno de seu próprio eixo;
* PAR: para o robô;
* FTT: anda para frente durante um X tempo determinado;
* TRT: anda para trás durante um X tempo determinado;
* DRT: anda para direita durante um X tempo determinado em torno de seu próprio eixo;
* EST: anda para esquerda durante um X tempo determinado em torno de seu próprio eixo;

### Comandos avançados:

* MTP: ajusta a "potência" de ambos os motores entre valores -100 (mais lento) à 100 (mais rápido);
* Programação: possui intuito de realizar uma sequência de comandos separados por ponto e vírgula ';'. Para se iniciar uma programação requer
a primeira instrução dada por 'PRG';

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

### Configuração do Web Repl

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

### Baixando a interface Web Repl

* Baixe o repositório do client web repl neste repositório [Web Repl Web Interface](https://github.com/micropython/webrepl)

### Acessando o ESP-32 de forma remota:

* Após baixar e abrir o client web repl, essa será sua tela inicial:

![2](https://github.com/luissssmartins/L9110URA/blob/main/images/webrepl.png)

* No campo ws://<IP>, insira o IP no qual seu ESP-32 está conectado, seja em rede local ou em uma rede wi-fi.

* Após isso basta se logar com a senha criada no WebREPL e acessar remotamente seu ESP-32.

## Entendendo e configurando a versão em C++:

### Preparando o ambiente

* Baixe a extensão do [PlatformIO](https://platformio.org/install/ide?install=vscode) em seu VS Code.

* Após instalar, clone esse projeto e abra-o no VS Code com a extensão do PlatformIO:

![3](https://github.com/luissssmartins/L9110URA/blob/main/images/platformio_1.png)

* Abrindo o projeto, certifique-se que há o arquivo "platformio.ini", nele contém as dependências do projeto:

![4](https://github.com/luissssmartins/L9110URA/blob/main/images/platformio_2.png)

### Criando uma imagem personalizada para o ESP-32
    
![5](https://github.com/luissssmartins/L9110URA/blob/main/images/platformio_3.png)

* Após o download automático das dependências do projeto, acesse a parte da extensão do PlatformIO, abra a pasta "esp32dev", abra a sub-pasta "Platform", e aperte em "Erase Flash".

* Após ter limpado a memória interna de seu ESP-32, aperte em "Build Filesystem Image", construindo o arquivo de firmware personalizado.

* Depois de ter concluído os dois passos acima, aperte em "Upload Filesystem Image", isso fará com que a imagem que foi construída seja enviada ao ESP-32.
 
![6](https://github.com/luissssmartins/L9110URA/blob/main/images/platformio_4.png)

### Configuração dentro do MCU (SPIFFS)

```bash
{
    "ssid": "URA000",
    "password": "PASSWORD"
}
```

* Você pode modificar o nome do robô alterando o "ssid" para algum nome que você deseja.
* A senha não pode ser menor que 6 caracteres por padrão do firmware do microcontrolador.

### Compilando o projeto

* Para compilar o projeto, primeiramente é necessário apertar em "build", veja no canto inferior a opção de build:

![7](https://github.com/luissssmartins/L9110URA/blob/main/images/platformio_5.png)

* Logo após ter realizado o build do projeto, vamos enviá-lo ao ESP-32:

![8](https://github.com/luissssmartins/L9110URA/blob/main/images/platformio_6.png)

* Depois de ter concluído os dois passos acima, se conecte a rede Wi-Fi que foi gerada baseada na configuração realizada anteriormente.

* Abrindo qualquer navegador, insira o endereço de IP **192.168.4.1** na barra de navegação, essa deverá ser o site acessado:

![9](https://github.com/luissssmartins/L9110URA/blob/main/images/ura-complete.png)

### Comandos básicos

* Botão "Frente" (verde): anda para frente;
* Botão "Trás" (amarelo): anda para trás;
* Botão "Direita" (azul): vira para direita em torno de seu próprio eixo;
* Botão "Esquerda" (vermelho): vira para a esquerda em torno de seu próprio eixo;
* Botão "Parar" (stop): interrompe qualquer sequência de comandos clicados, fazendo o robô parar;

![10](https://github.com/luissssmartins/L9110URA/blob/main/images/ura-joystick.png)
 
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
