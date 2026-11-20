# Comunicação em rede — proposta para o Cuidar de Perto

No Tinkercad, o Arduino lê o sensor PIR e os botões, controla os LEDs e o buzzer e escreve mensagens no Monitor Serial. Essa parte já foi simulada. Para chegar ao aplicativo do cuidador, seria preciso acrescentar uma forma de conexão com a rede.

## Dispositivos e comunicação

| Etapa | Componentes | Meio utilizado ou previsto | Situação |
|---|---|---|---|
| Entrada de dados | PIR, botões e Arduino Uno | Pinos digitais D2, D3 e D4 | Simulado |
| Aviso local | Arduino, LEDs e buzzer | Pinos D5, D6 e D9 | Simulado |
| Mensagens do circuito | Arduino e Monitor Serial | Comunicação serial a 9600 baud | Simulado |
| Envio para um gateway | Arduino e computador | Cabo USB / serial | Proposta |
| Acesso à rede | Gateway e roteador | Ethernet ou Wi-Fi, usando TCP/IP | Proposta |
| Recebimento dos alertas | Gateway e API REST .NET | Requisição HTTPS com dados do evento | Proposta |
| Registro e consulta | API, Oracle e sistema do cuidador | Acesso ao banco e requisições da aplicação | Proposta para integração IoT |

## Caminho dos dados

Quando há um pedido de socorro ou o tempo de inatividade é atingido, o Arduino aciona o alerta local e escreve uma mensagem como `ALERTA: PEDIDO DE SOCORRO`. Em uma versão conectada, um programa no computador leria essa mensagem pela porta serial. Esse programa, chamado aqui de gateway, identificaria a qual idoso o dispositivo pertence e encaminharia os dados para a API.

A comunicação entre o gateway e a API poderia usar HTTPS, com a identificação do dispositivo, o tipo de alerta e o momento da ocorrência. A aplicação então faria a validação dos dados e o registro no Oracle. O cuidador poderia consultar os alertas por meio do sistema.

**Essa integração não faz parte do circuito executado no Tinkercad.** O código atual apenas mostra mensagens de texto no Monitor Serial. Não existe envio de JSON ou de requisições HTTP implementado.

## Cuidados para uma versão conectada

Seria necessário autenticar os dispositivos, proteger a comunicação com TLS, controlar quem consulta os alertas e armazenar somente os dados necessários. Também seria importante tratar quedas de conexão, evitar registros duplicados e guardar eventos para enviá-los quando a Internet voltasse.

O diagrama dessa proposta está em [`../diagramas/arquitetura_comunicacao.png`](../diagramas/arquitetura_comunicacao.png).
