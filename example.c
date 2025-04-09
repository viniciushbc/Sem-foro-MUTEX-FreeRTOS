#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "basic_io.h"
#include <time.h>
#include <stdlib.h>

// Definindo o prot�tipo das tarefas (.h)
void vTask1(void *pvParameters);
void vTask2(void *pvParameters);
void vTask3(void* pvParameters);

// Criando a vari�vel para o sem�foro
SemaphoreHandle_t xSemaphore;

// Criando um buffer global para display compartilhado
char buffer[20];

int main_(void)
{

		// Fun��o para criar um sem�foro bin�rio
	    xSemaphore = xSemaphoreCreateMutex();

		// Criando as tarefas (todas com a mesma prioridade)
		xTaskCreate(vTask1, "TarefaDATA", 1000, NULL, 1, NULL);
		xTaskCreate(vTask2, "TarefaHORA", 1000, NULL, 1, NULL);
		xTaskCreate(vTask3, "TarefaCIDADE", 1000, NULL, 1, NULL);

		// Inicializa��o do escalonador
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

		// Obten��o dos segundos
		time(&segundos);

		// Convers�o de segundos para o tempo local
		dateTimeNow = localtime(&segundos);

		int dia = dateTimeNow->tm_mday;
		int mes = dateTimeNow->tm_mon + 1;
		int ano = dateTimeNow->tm_year + 1900;

		// Verificando se o sem�foro foi criado antes de utiliz�-lo
		if (xSemaphore != NULL) {

			// Verifica se o sem�foro est� dispon�vel, caso o sem�foro esteja  dispon�vel ele obt�m o sem�foro
			// Caso o sem�foro estiver sendo utilizado este aguarde 10 ticks para ver o sem�foro � liberado.
			if (xSemaphoreTake(xSemaphore, (portTickType)10) == pdTRUE) {
				
				// Aloca a string com os dados no buffer
				sprintf(buffer, "Data: %02d/%02d/%04d\n", dia, mes, ano);

				// Imprime o buffer
				vPrintString(buffer);
				
				// Libera��o do sem�foro
				xSemaphoreGive(xSemaphore);
			}
		}
		else
		{
			// imprime a mensagem caso o sem�foro n�o tenha sido criado
			printf("O sem�foro n�o foi criado\n");
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

		// Obten��o dos segundos
		time(&segundos);

		// Convers�o de segundos para o tempo local
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
			printf("O sem�foro n�o foi criado\n");
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
		// Gera��o aleat�ria de temperatura
		float temp = ((float)rand() / (float)(RAND_MAX)) * maxTemp;
		
		if (xSemaphore != NULL) {
			if (xSemaphoreTake(xSemaphore, (portTickType)10) == pdTRUE) {

				sprintf(buffer, "Curitiba, %.2f �C\n", temp);

				vPrintString(buffer);

				xSemaphoreGive(xSemaphore);
			}
		}
		else
		{
			printf("O sem�foro n�o foi criado\n");
		}
		vTaskDelay(portTICK_RATE_MS * 100);
	}
	vTaskDelete(NULL);
}
