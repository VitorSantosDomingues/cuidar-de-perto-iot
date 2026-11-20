# Testes do circuito

**Ambiente:** Tinkercad Circuits, Arduino Uno R3  
**Data:** 19/11/2026

Testamos o pedido de socorro, o alerta por inatividade e o botão usado para reconhecer os avisos. Em todos esses casos, o Monitor Serial apresentou as mensagens esperadas. O buzzer também foi ouvido durante os alertas e desligou após o reconhecimento.

| Caso | Como testamos | Resultado | Evidência |
|---|---|---|---|
| T01 — SOS | Seguramos o primeiro botão por 2 segundos | Mensagem `ALERTA: PEDIDO DE SOCORRO`, LED vermelho e buzzer | [Imagem](../evidencias/teste_sos.png) |
| T02 — Inatividade | Deixamos o PIR sem detectar movimento por 20 segundos | Mensagem `ALERTA: INATIVIDADE`, LED vermelho e buzzer | [Imagem](../evidencias/teste_inatividade.png) |
| T03 — Reconhecimento do SOS | Apertamos o segundo botão após o SOS | Mensagem `Alerta reconhecido`, LED verde e buzzer desligado | [Imagem](../evidencias/teste_reconhecimento_sos.png) |
| T04 — Reconhecimento da inatividade | Apertamos o segundo botão após o aviso de inatividade | Mensagem `Alerta reconhecido`, LED verde e buzzer desligado | [Imagem](../evidencias/teste_reconhecimento_inatividade.png) |

Os quatro testes principais funcionaram na simulação. Ainda não registramos uma captura separada da mensagem de movimento do PIR, embora esse sensor tenha sido utilizado para testar a inatividade.

## O que não foi testado

Os testes se limitaram ao circuito do Tinkercad. Não houve transmissão por Wi-Fi, chamadas HTTP, registro automático no Oracle nem notificação para um cuidador. Essas etapas aparecem apenas na proposta de arquitetura de rede.

O intervalo de 20 segundos é usado somente para demonstração. Ausência de movimento não comprova uma emergência, e este protótipo não substitui acompanhamento humano ou serviço de socorro.
