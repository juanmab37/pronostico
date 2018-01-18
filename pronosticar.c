#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//TRUE 1
//FALSE 0

void delay(int secs) {
	int i=0;
	for(i = (time(NULL) + secs); time(NULL) != i; time(NULL));
}

float temperatura(FILE *archivo) //archivo debe estar abierto
{
	char* res2;
	float res=0;
	res2 = (char*) malloc(sizeof(char)*4);
	char cadena[80];
	
	while(!feof(archivo)) {
		//printf("Leyendo\n");
		fscanf(archivo,"%s",cadena);
		if(strcmp(cadena,"style='font-family:Arial;color:white'>&nbsp;TEMPERATURA</span></b></p>") == 0) //encontramos
		{		
			while(!feof(archivo)) {
				fscanf(archivo,"%s",cadena);
				if(strcmp(cadena,"font-family:Arial'>Actual&nbsp;") == 0) //encontramos
				{
					while(!feof(archivo)) {
						fscanf(archivo,"%s",cadena);
						if(strcmp(cadena,"style='font-size:10.0pt;") == 0) //encontramos
						{
							fscanf(archivo,"%s",cadena);

							res2[0] = cadena[19];
							res2[1] = cadena[20];
							res2[2] = cadena[21];
							res2[3] = cadena[22]; 
							res = atof(res2);
												
							break; //salimos del while
						}
					}
					break; //salimos del while
				}
				if(strcmp(cadena,"font-family:Arial'>Mínima</span></b></p>>") == 0) //nos pasamos
				{
					printf("No se encontro\n");
					break;
				}
			}
			break; //salimos del while
		}
		
		if(strcmp(cadena,"font-family:Arial'>Mínima</span></b></p>>") == 0) //nos pasamos
		{
			printf("No se encontro\n");
			break;
		}
	} 
	
	return res;
}

float presion(FILE *archivo) //archivo debe estar abierto
{
	char* res2;
	float res=0;
	res2 = (char*) calloc(10,sizeof(char));
	char cadena[80];
	
	while(!feof(archivo)) {
		//printf("Leyendo\n");
		fscanf(archivo,"%s",cadena);
		if(strcmp(cadena,"style='font-family:Arial;color:white'>&nbsp;PRESION") == 0) //encontramos
		{		
			while(!feof(archivo)) {
				fscanf(archivo,"%s",cadena);
				if(strcmp(cadena,"font-family:Arial'>Actual&nbsp;&nbsp;</span></b><o:p></o:p></p>") == 0) //encontramos
				{
					while(!feof(archivo)) {
						fscanf(archivo,"%s",cadena);
						if(strcmp(cadena,"style='font-size:10.0pt;") == 0) //encontramos
						{
							fscanf(archivo,"%s",cadena);

							res2[0] = cadena[19];
							res2[1] = cadena[20];
							res2[2] = cadena[21];
							res2[3] = cadena[22]; 
							res2[4] = cadena[23]; 

							res = atof(res2);
												
							break; //salimos del while font-family:Arial'>997.2hPa&nbsp;</span></p>
						}
					}
					break; //salimos del while
				}
				if(strcmp(cadena,"style='font-size:10.0pt;font-family:Arial'>PRESION") == 0) //nos pasamos
				{
					printf("No se encontro\n");
					break;
				}
			}
			break; //salimos del while
		}
		
		if(strcmp(cadena,"style='font-size:10.0pt;font-family:Arial'>PRESION") == 0) //nos pasamos
		{
			printf("No se encontro\n");
			break;
		}
	} 
	
	return res;
}


int main(void)
{
	FILE *archivo;
	char buf[10];
	float temperatura_actual=0, temperatura_anterior=0;
	float presion_actual=0, presion_anterior=0;
	int bajando_t=0,bajando_p=0,subiendo_t=0,subiendo_p=0,estacionaria_t=0,estacionaria_p=0;
	int bandera=0;
	
	system("./simple > pronostico.html");
	
	sprintf(buf, "pronostico.html");

	if ( (archivo = fopen(buf,"r")) == NULL )
	{
		printf("No se pudo abrir %s\n",buf);
		exit(1);
	}
	
	temperatura_anterior = temperatura(archivo);
	presion_anterior = presion(archivo);
	printf("Temperatura Inicial %.1f\n",temperatura_anterior);
	printf("Presion Inicial %.1f\n",presion_anterior);
	
	fclose(archivo);
	
	
	for(;;) {
	delay(300);
	
	system("./simple > pronostico.html");
	
	sprintf(buf, "pronostico.html");

	if ( (archivo = fopen(buf,"r")) == NULL )
	{
		printf("No se pudo abrir %s\n",buf);
		exit(1);
	}
	
	temperatura_actual = temperatura(archivo);
	presion_actual = presion(archivo);
	
	bajando_t = temperatura_actual < temperatura_anterior;
	subiendo_t = temperatura_actual > temperatura_anterior;
	estacionaria_t = temperatura_actual == temperatura_anterior;
	
	bajando_p = presion_actual < presion_anterior;
	subiendo_p = presion_actual > presion_anterior; 
	estacionaria_p = presion_actual == presion_anterior;
	
	
	if(bajando_p && bajando_t) {
		if(bandera != 1)
			printf("LLUVIA ABUNDANTE \n Temp = %.1f Pres = %.1f \n",temperatura_actual,presion_actual);
		bandera=1;
	}	
	if(bajando_p && estacionaria_t) {
		if(bandera != 2)
			printf("PROBABLES LLUVIAS \n Temp = %.1f Pres = %.1f \n",temperatura_actual,presion_actual);	
		bandera=2;
	}	
	
	if(bajando_p && subiendo_t) { 
		if(bandera != 3)
			printf("TIEMPO INCIERTO \n Temp = %.1f Pres = %.1f \n",temperatura_actual,presion_actual);
		bandera=3;
	}
	
	if(estacionaria_p && bajando_t) {
		if(bandera != 4)
			printf("PROBABLES LLUVIAS \n Temp = %.1f  Pres = %.1f \n",temperatura_actual,presion_actual);	
		bandera=4;
	}
		
	if(estacionaria_p && estacionaria_t) {
		//if(bandera != 5)
			//printf("SE MANTIENE \n Temp = %.1f  Pres = %.1f \n",temperatura_actual,presion_actual);		
		bandera=5;
	}
	
	if(estacionaria_p && subiendo_t) {
		if(bandera != 6)
			printf("TIENDE A BUEN TIEMPO \n Temp = %.1f  Pres = %.1f \n",temperatura_actual,presion_actual);	
		bandera=6;
	}
	
	if(subiendo_p && bajando_t) {
		if(bandera != 7)
			printf("VIENTO POLAR \n Temp = %.1f  Pres = %.1f \n",temperatura_actual,presion_actual);	
		bandera=7;
	}
		
	if(subiendo_p && estacionaria_t) {
		if(bandera != 8)
			printf("BUEN TIEMPO \n Temp = %.1f  Pres = %.1f \n",temperatura_actual,presion_actual);	
		bandera=8;
	}
		
	if(subiendo_p && subiendo_t) {
		if(bandera != 9)
			printf("CALUROSO, SECO, VIENTOS FUERTES DE ZONA ECUATORIAL \n Temp = %.1f  Pres = %.1f \n",temperatura_actual,presion_actual);	
		bandera=9;
	}
	
	temperatura_anterior = temperatura_actual;
	presion_anterior = presion_actual;
	
	}
	fclose(archivo);
	
	return 0;
}

