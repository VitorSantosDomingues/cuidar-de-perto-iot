# Cuidar de Perto — IoT

**Global Solution 2026/2 — CitizenTech**  
**Disciplina:** Disruptive Architectures: IoT, IoB & Generative IA  
**Turma:** 2TDSPR

## Sobre o projeto

O Cuidar de Perto foi pensado para ajudar famílias e cuidadores a acompanhar idosos que moram sozinhos. A ideia é perceber situações fora da rotina, como um período muito longo sem movimento ou um pedido de socorro, sem depender de câmeras dentro de casa.

Nesta parte da Global Solution, montamos um circuito no Tinkercad com Arduino Uno. Ele lê um sensor de movimento e dois botões, acende LEDs de acordo com a situação e usa um buzzer para avisar quando há um alerta. As mensagens também aparecem no Monitor Serial.

O protótipo representa a parte de sensores da solução que estamos desenvolvendo em .NET e Database. Ele funciona dentro da simulação, mas **não envia alertas pela internet**. A comunicação com a API foi planejada e está descrita mais adiante.

## Circuito e componentes

Usamos um Arduino Uno R3, uma protoboard, um sensor PIR, dois botões, LEDs verde e vermelho, dois resistores de 220 Ω e um buzzer piezoelétrico.

| Componente | Conexão no Arduino |
|---|---|
| PIR (sinal) | D2 |
| Botão de socorro | D3 e GND |
| Botão para reconhecer o alerta | D4 e GND |
| LED verde | D5, resistor de 220 Ω e GND |
| LED vermelho | D6, resistor de 220 Ω e GND |
| Buzzer | D9 (+) e GND (−) |
| Alimentação do PIR | 5V e GND |

Os botões usam `INPUT_PULLUP`, então não precisam de resistores externos. Os resistores de 220 Ω ficam em série com os LEDs para limitar a corrente.

## Como funciona

Em condições normais, o LED verde fica aceso. Quando o PIR percebe movimento, o Arduino atualiza o tempo da última detecção. Se passar **20 segundos sem movimento**, acende o LED vermelho, liga o buzzer e registra `ALERTA: INATIVIDADE` no Monitor Serial.

O botão da esquerda funciona como pedido de socorro. Ao mantê-lo pressionado por **2 segundos**, o circuito emite o alerta `ALERTA: PEDIDO DE SOCORRO`, também com LED vermelho e buzzer.

O botão da direita serve para reconhecer qualquer um dos alertas. Ao pressioná-lo, o som para, o LED vermelho apaga, o verde volta a acender e a mensagem `Alerta reconhecido` aparece no Monitor Serial. Se houver movimento durante um alerta de inatividade, o código também encerra esse alerta.

Esses tempos foram reduzidos para facilitar a demonstração no Tinkercad. Os 20 segundos **não são um parâmetro adequado para monitoramento real**.

## Executando no Tinkercad

1. Abra o [Tinkercad Circuits](https://www.tinkercad.com/circuits) e monte o circuito seguindo a tabela de pinos.
2. Entre em **Código**, escolha o modo **Texto** e cole o conteúdo de `CuidarDePerto_IoT.ino`.
3. Inicie a simulação e abra o **Monitor Serial** a 9600 baud.
4. Teste a ausência de movimento no PIR, segure o botão SOS por 2 segundos e use o segundo botão para reconhecer os alertas.

O código está no arquivo `CuidarDePerto_IoT.ino`, na pasta principal do projeto. Não é necessário instalar bibliotecas adicionais.

## Testes realizados

Testamos os dois tipos de alerta e o reconhecimento de cada um. Os resultados apareceram no Monitor Serial e os LEDs mudaram de estado como esperado. Durante os testes, o buzzer tocou ao disparar os alertas e parou quando o botão de reconhecimento foi pressionado.

| Teste | Mensagem observada | Imagem |
|---|---|---|
| Inatividade | `ALERTA: INATIVIDADE` | [Ver captura](evidencias/teste_inatividade.png) |
| Pedido de socorro | `ALERTA: PEDIDO DE SOCORRO` | [Ver captura](evidencias/teste_sos.png) |
| Reconhecimento da inatividade | `Alerta reconhecido` | [Ver captura](evidencias/teste_reconhecimento_inatividade.png) |
| Reconhecimento do SOS | `Alerta reconhecido` | [Ver captura](evidencias/teste_reconhecimento_sos.png) |

A [montagem completa](evidencias/montagem_tinkercad.png) e os detalhes dos procedimentos estão nas pastas `evidencias` e `testes`. As capturas mostram o funcionamento visual e o Monitor Serial; o áudio foi conferido durante a execução da simulação.

## Proposta de comunicação em rede

O Arduino Uno utilizado no Tinkercad não tem Wi-Fi integrado, e nesta versão não fizemos uma conexão direta com a API. Para conectar o dispositivo ao restante do Cuidar de Perto, pensamos em um **gateway**, como um computador ligado ao Arduino por USB.

O caminho previsto seria:

**Sensor ou botão → Arduino → USB/Serial → gateway → rede/Internet → API .NET → banco Oracle → sistema do cuidador**

O gateway leria as mensagens da porta serial e enviaria os eventos por HTTPS, com identificação do idoso e tipo de alerta. A API receberia esses dados e poderia registrá-los no banco. Esta é uma **proposta de integração**, não uma funcionalidade testada no circuito.

O diagrama está em [`diagramas/arquitetura_comunicacao.png`](diagramas/arquitetura_comunicacao.png). Explicamos os dispositivos, meios de comunicação e cuidados de segurança em [`documentacao/comunicacao_rede.md`](documentacao/comunicacao_rede.md).

## Relação com o .NET e o banco de dados

O projeto das outras disciplinas já trabalha com idosos, alertas, cuidadores e atendimentos. Na arquitetura proposta, um evento do Arduino daria origem a um registro em `T_CDP_ALERTA`, associado ao idoso em `T_CDP_IDOSO`. O cuidador de `T_CDP_CUIDADOR` poderia acompanhar o caso, e `T_CDP_ATENDIMENTO` serviria para registrar o atendimento.

Essa ligação ajuda a mostrar como cada disciplina contribui para a mesma solução, mesmo que a comunicação automática entre Arduino e .NET não tenha sido implementada nesta etapa.

## Escolhas e limitações

Escolhemos o PIR porque é simples e permite detectar movimento sem capturar imagens ou áudio. O botão físico torna o pedido de ajuda mais acessível para quem não quer depender de um aplicativo. Os LEDs e o buzzer dão uma resposta imediata, mesmo sem conexão com a internet.

Por outro lado, o PIR **não identifica a pessoa nem detecta quedas**. Ficar sem movimento também não significa necessariamente que houve uma emergência. Além disso, o protótipo ainda não tem envio de dados por rede, armazenamento de eventos durante falhas de conexão ou notificações remotas. Em uma versão real, precisaríamos revisar os limites de tempo, a cobertura dos sensores e a segurança das informações dos usuários.

A proposta se relaciona com o **ODS 3 (Saúde e Bem-Estar)** e o **ODS 10 (Redução das Desigualdades)**, ao buscar uma forma simples e acessível de apoiar o cuidado de idosos. O circuito é apenas uma prova de conceito acadêmica, não um dispositivo médico ou serviço de emergência.

## Ferramentas de apoio

Utilizamos o Tinkercad para montar e testar o circuito e o ChatGPT como apoio para entender as ligações, preparar o código inicial e revisar a documentação. As conexões e os cenários de alerta foram conferidos na simulação.

## Integrantes

- Felipe Cuesta Puerta de Oliveira — RM 567703
- Vitor Costa de Godoi — RM 568448
- Vitor Santos Domingues — RM 568375
- João Victor De Souza Braz — RM 566862
- Lucas Marcelino Pompeu — RM 567010
