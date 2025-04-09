# FreeRTOS - Sistema de Tempo Real - Data, Hora e Cidade & Temperatura

Este projeto demonstra uma aplicação embarcada baseada em **FreeRTOS**, onde três tarefas simultâneas exibem:

- 📅 Data atual
- 🕒 Hora atual
- 🌡️ Temperatura simulada para a cidade

As tarefas compartilham um buffer global que funciona como um display e utilizam **semáforo** para garantir acesso exclusivo à região crítica.

---

## 🚀 Visão Geral

O sistema é composto por 3 tarefas com prioridade igual:

| Tarefa         | Função                                    |
|----------------|--------------------------------------------|
| `vTask1`       | Exibe a **data** atual (dia/mês/ano)       |
| `vTask2`       | Exibe a **hora** atual (hora:min:seg)      |
| `vTask3`       | Gera uma **temperatura aleatória**         |

Todas as tarefas utilizam um **mutex** (`xSemaphore`) para sincronizar o acesso ao **buffer global** (`char buffer[20]`), onde formatam a mensagem a ser impressa com `vPrintString()`.

---

## 🧰 Tecnologias Utilizadas

### 🧠 FreeRTOS

[**FreeRTOS**](https://www.freertos.org/) é um sistema operacional de tempo real de código aberto, amplamente utilizado em sistemas embarcados.

Neste projeto, usamos **FreeRTOS** para:
- Gerenciar e escalonar 3 tarefas concorrentes.
- Utilizar semáforo mutex (`xSemaphoreCreateMutex`) para controle de acesso ao buffer de texto.
- Realizar atrasos não bloqueantes com `vTaskDelay`.

### 💻 Linguagem C

O projeto foi totalmente desenvolvido em **C**, linguagem de programação padrão para sistemas embarcados.

---
