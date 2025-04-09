#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "basic_io.h"
#include <time.h>
#include <stdlib.h>

// Definindo o protótipo das tarefas (.h)
void vTask1(void *pvParameters);
void vTask2(void *pvParameters);
void vTask3(void* pvParameters);

// Criando a variável para o semáforo
SemaphoreHandle_t xSemaphore;

// Criando um buffer global para display compartilhado
char buffer[20];

int main_(void)
{

		// Função para criar um semáforo binário
	    xSemaphore = xSemaphoreCreateMutex();

		// Criando as tarefas (todas com a mesma prioridade)
		xTaskCreate(vTask1, "TarefaDATA", 1000, NULL, 1, NULL);
		xTaskCreate(vTask2, "TarefaHORA", 1000, NULL, 1, NULL);
		xTaskCreate(vTask3, "TarefaCIDADE", 1000, NULL, 1, NULL);

		// Inicialização do escalonador
		vTaskStartScheduler();

	for (;; );
	return 0;
}

void vTask1(void* pvParameters)
{

	for (;; )
	{
		// Aloca o tempo em segundos
		time_t segundos;

		// Ponteiro para a struct tempo
		struct tm* dateTimeNow;

		// Obtenção dos segundos
		time(&segundos);

		// Conversão de segundos para o tempo local
		dateTimeNow = localtime(&segundos);

		int dia = dateTimeNow->tm_mday;
		int mes = dateTimeNow->tm_mon + 1;
		int ano = dateTimeNow->tm_year + 1900;

		// Verificando se o semáforo foi criado antes de utilizá-lo
		if (xSemaphore != NULL) {

			// Verifica se o semáforo está disponível, caso o semáforo esteja  disponível ele obtém o semáforo
			// Caso o semáforo estiver sendo utilizado este aguarde 10 ticks para ver o semáforo é liberado.
			if (xSemaphoreTake(xSemaphore, (portTickType)10) == pdTRUE) {
				
				// Aloca a string com os dados no buffer
				sprintf(buffer, "Data: %02d/%02d/%04d\n", dia, mes, ano);

				// Imprime o buffer
				vPrintString(buffer);
				
				// Liberação do semáforo
				xSemaphoreGive(xSemaphore);
			}
		}
		else
		{
			// imprime a mensagem caso o semáforo não tenha sido criado
			printf("O semáforo não foi criado\n");
		}
		// Efetua um delay na tarefa a cada 100 ticks
		vTaskDelay(portTICK_RATE_MS * 100);
	}
	vTaskDelete(NULL);
}

void vTask2(void* pvParameters)
{

	for (;; )
	{
		// Aloca o tempo em segundos
		time_t segundos;

		// Ponteiro para a struct tempo
		struct tm* dateTimeNow;

		// Obtenção dos segundos
		time(&segundos);

		// Conversão de segundos para o tempo local
		dateTimeNow = localtime(&segundos);

		int hora = dateTimeNow->tm_hour;
		int min = dateTimeNow->tm_min;
		int sec = dateTimeNow->tm_sec;

		if (xSemaphore != NULL) {
			if (xSemaphoreTake(xSemaphore, (portTickType)10) == pdTRUE) {

				// Aloca a string com os dados no buffer
				sprintf(buffer, "Hora: %02d:%02d:%02d\n", hora, min, sec);

				vPrintString(buffer);

				xSemaphoreGive(xSemaphore);
			}
		}
		else
		{
			printf("O semáforo não foi criado\n");
		}
		vTaskDelay(portTICK_RATE_MS * 100);
	}
	vTaskDelete(NULL);
}

void vTask3(void* pvParameters)
{
	float maxTemp = 42.0;

	for (;; )
	{
		// Geração aleatória de temperatura
		float temp = ((float)rand() / (float)(RAND_MAX)) * maxTemp;
		
		if (xSemaphore != NULL) {
			if (xSemaphoreTake(xSemaphore, (portTickType)10) == pdTRUE) {

				sprintf(buffer, "Curitiba, %.2f ºC\n", temp);

				vPrintString(buffer);

				xSemaphoreGive(xSemaphore);
			}
		}
		else
		{
			printf("O semáforo não foi criado\n");
		}
		vTaskDelay(portTICK_RATE_MS * 100);
	}
	vTaskDelete(NULL);
}
