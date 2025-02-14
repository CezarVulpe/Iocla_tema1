#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include <string.h>

sensor *sortare(sensor *senzor, int nrsenzori)
{
	sensor *copie;
	int cnt = 0;
	copie = malloc(nrsenzori * sizeof(sensor));
	for (int i = 0; i < nrsenzori; i++)
	{
		int tip;
		if (senzor[i].sensor_type == TIRE)
		{
			tip = 0;
		}
		else
		{
			tip = 1;
		}
		if (tip == 1)
		{
			power_management_unit *datepmu, *datepmuoriginal;
			datepmu = malloc(sizeof(power_management_unit));
			datepmuoriginal = (power_management_unit *)senzor[i].sensor_data;
			copie[cnt].sensor_type = PMU;
			datepmu->voltage = datepmuoriginal->voltage;
			datepmu->current = datepmuoriginal->current;
			datepmu->power_consumption = datepmuoriginal->power_consumption;
			datepmu->energy_regen = datepmuoriginal->energy_regen;
			datepmu->energy_storage = datepmuoriginal->energy_storage;
			copie[cnt].sensor_data = datepmu;
			copie[cnt].nr_operations = senzor[i].nr_operations;
			copie[cnt].operations_idxs = malloc(copie[cnt].nr_operations * sizeof(int));
			for (int j = 0; j < copie[cnt].nr_operations; j++)
			{
				copie[cnt].operations_idxs[j] = senzor[i].operations_idxs[j];
			}
			cnt++;
		}
	}
	for (int i = 0; i < nrsenzori; i++)
	{
		int tip;
		if (senzor[i].sensor_type == TIRE)
		{
			tip = 0;
		}
		else
		{
			tip = 1;
		}
		if (tip == 0)
		{
			tire_sensor *dateroata, *dateroataoriginal;
			dateroata = malloc(sizeof(tire_sensor));
			dateroataoriginal = (tire_sensor *)senzor[i].sensor_data;
			copie[cnt].sensor_type = TIRE;
			dateroata->pressure = dateroataoriginal->pressure;
			dateroata->temperature = dateroataoriginal->temperature;
			dateroata->wear_level = dateroataoriginal->wear_level;
			dateroata->performace_score = dateroataoriginal->performace_score;
			copie[cnt].sensor_data = dateroata;
			copie[cnt].nr_operations = senzor[i].nr_operations;
			copie[cnt].operations_idxs = malloc(copie[cnt].nr_operations * sizeof(int));
			for (int j = 0; j < copie[cnt].nr_operations; j++)
			{
				copie[cnt].operations_idxs[j] = senzor[i].operations_idxs[j];
			}
			cnt++;
		}
	}
	return copie;
}
void eliberare(sensor *senzor, int nrsenzori)
{
	for (int i = 0; i < nrsenzori; i++)
	{
		int tip;
		if (senzor[i].sensor_type == TIRE)
		{
			tip = 0;
		}
		else
		{
			tip = 1;
		}
		if (tip == 0)
		{
			tire_sensor *dateroata;
			dateroata = (tire_sensor *)senzor[i].sensor_data;
			free(senzor[i].operations_idxs);
			free(dateroata);
		}
		else
		{
			power_management_unit *datepmu;
			datepmu = (power_management_unit *)senzor[i].sensor_data;
			free(senzor[i].operations_idxs);
			free(datepmu);
		}
	}
	free(senzor);
}

int verifclear(sensor *senzor, int nrsenzori, int i)
{

	int tip;
	if (senzor[i].sensor_type == TIRE)
	{
		tip = 0;
	}
	else
	{
		tip = 1;
	}
	if (tip == 0)
	{
		// pressure: between 19 and 28 psi
		// temperature: between 0°C and 120°C
		// wear_level: between 0% and 100%
		tire_sensor *dateroata;
		dateroata = (tire_sensor *)senzor[i].sensor_data;
		if (dateroata->pressure < 19 || dateroata->pressure > 28)
			return 0;
		if (dateroata->temperature < 0 || dateroata->temperature > 120)
			return 0;
		if (dateroata->wear_level < 0 || dateroata->wear_level > 100)
			return 0;
	}
	else
	{
		// Power Management Unit Sensor:
		// voltage: between 10V and 20V
		// current: between -100A and 100A
		// power_consumption: between 0kW and 1000kW
		// energy_regen: between 0% and 100%
		// energy_storage: between 0% and 100%
		power_management_unit *datepmu;
		datepmu = (power_management_unit *)senzor[i].sensor_data;
		if (datepmu->voltage < 10 || datepmu->voltage > 20)
			return 0;
		if (datepmu->current < -100 || datepmu->current > 100)
			return 0;
		if (datepmu->power_consumption < 0 || datepmu->power_consumption > 1000)
			return 0;
		if (datepmu->energy_regen < 0 || datepmu->energy_regen > 100)
			return 0;
		if (datepmu->energy_storage < 0 || datepmu->energy_storage > 100)
			return 0;
	}
	return 1;
}
void clear(sensor *senzor, int *nrsenzori)
{
	for (int k = 0; k < *nrsenzori; k++)
	{
		if (verifclear(senzor, *nrsenzori, k) == 0)
		{
			int tip1 = 0;
			tip1++;
			if (senzor[k].sensor_type == TIRE)
			{
				tip1 = 0;
			}
			else
			{
				tip1 = 1;
			}
			sensor *copie;
			int cnt = 0;
			copie = malloc((*nrsenzori - 1) * sizeof(sensor));
			for (int i = 0; i < *nrsenzori; i++)
			{
				int tip;
				if (senzor[i].sensor_type == TIRE)
				{
					tip = 0;
				}
				else
				{
					tip = 1;
				}
				if (i != k)
				{
					if (tip == 1)
					{
						power_management_unit *datepmu, *datepmuoriginal;
						datepmu = malloc(sizeof(power_management_unit));
						datepmuoriginal = (power_management_unit *)senzor[i].sensor_data;
						copie[cnt].sensor_type = PMU;
						datepmu->voltage = datepmuoriginal->voltage;
						datepmu->current = datepmuoriginal->current;
						datepmu->power_consumption = datepmuoriginal->power_consumption;
						datepmu->energy_regen = datepmuoriginal->energy_regen;
						datepmu->energy_storage = datepmuoriginal->energy_storage;
						copie[cnt].sensor_data = datepmu;
						copie[cnt].nr_operations = senzor[i].nr_operations;
						copie[cnt].operations_idxs = malloc(copie[cnt].nr_operations * sizeof(int));
						for (int j = 0; j < copie[cnt].nr_operations; j++)
						{
							copie[cnt].operations_idxs[j] = senzor[i].operations_idxs[j];
						}
						cnt++;
					}
					if (tip == 0)
					{
						tire_sensor *dateroata, *dateroataoriginal;
						dateroata = malloc(sizeof(tire_sensor));
						dateroataoriginal = (tire_sensor *)senzor[i].sensor_data;
						copie[cnt].sensor_type = TIRE;
						dateroata->pressure = dateroataoriginal->pressure;
						dateroata->temperature = dateroataoriginal->temperature;
						dateroata->wear_level = dateroataoriginal->wear_level;
						dateroata->performace_score = dateroataoriginal->performace_score;
						copie[cnt].sensor_data = dateroata;
						copie[cnt].nr_operations = senzor[i].nr_operations;
						copie[cnt].operations_idxs = malloc(copie[cnt].nr_operations * sizeof(int));
						for (int j = 0; j < copie[cnt].nr_operations; j++)
						{
							copie[cnt].operations_idxs[j] = senzor[i].operations_idxs[j];
						}
						cnt++;
					}
				}
			}
			eliberare(senzor, *nrsenzori);
			*nrsenzori = *nrsenzori - 1;
			senzor = copie;
			k--;
		}
	}
}

void analize(sensor *senzor, int i)
{
	void (*sensor_operations[8])(sensor * senzorul);
	get_operations((void **)sensor_operations);
	for (int j = 0; j < senzor[i].nr_operations; j++)
	{
		sensor_operations[senzor[i].operations_idxs[j]](senzor[i].sensor_data);
	}
}

int main(int argc, char const *argv[])
{
	sensor *senzor;
	FILE *fin,*fout;
	fin = fopen(argv[1], "rb"); /* am deschis fisierele de input si de output */
	fout= fopen("verificam.txt","w");
	int nrsenzori;
	fread(&nrsenzori, sizeof(int), 1, fin);
	senzor = malloc(nrsenzori * sizeof(sensor));
	if (senzor == NULL)
	{
		fprintf(fout,"err");
		return 1;
	}
	for (int i = 0; i < nrsenzori; i++)
	{
		int tip;
		fread(&tip, sizeof(int), 1, fin);
		if (tip == 0)
		{
			tire_sensor *dateroata;
			dateroata = malloc(sizeof(tire_sensor));
			senzor[i].sensor_type = TIRE;
			fread(&dateroata->pressure, sizeof(int), 1, fin);
			fread(&dateroata->temperature, sizeof(int), 1, fin);
			fread(&dateroata->wear_level, sizeof(int), 1, fin);
			fread(&dateroata->performace_score, sizeof(int), 1, fin);
			senzor[i].sensor_data = dateroata;
			fread(&senzor[i].nr_operations, sizeof(int), 1, fin);
			senzor[i].operations_idxs = malloc(senzor[i].nr_operations * sizeof(int));
			for (int j = 0; j < senzor[i].nr_operations; j++)
			{
				fread(&(senzor[i].operations_idxs[j]), sizeof(int), 1, fin);
			}
		}
		else
		{
			power_management_unit *datepmu;
			datepmu = malloc(sizeof(power_management_unit));
			senzor[i].sensor_type = PMU;
			fread(&datepmu->voltage, sizeof(int), 1, fin);
			fread(&datepmu->current, sizeof(int), 1, fin);
			fread(&datepmu->power_consumption, sizeof(int), 1, fin);
			fread(&datepmu->energy_regen, sizeof(int), 1, fin);
			fread(&datepmu->energy_storage, sizeof(int), 1, fin);
			senzor[i].sensor_data = datepmu;
			fread(&senzor[i].nr_operations, sizeof(int), 1, fin);
			senzor[i].operations_idxs = malloc(senzor[i].nr_operations * sizeof(int));
			for (int j = 0; j < senzor[i].nr_operations; j++)
			{
				fread(&(senzor[i].operations_idxs[j]), sizeof(int), 1, fin);
			}
		}
	}
	sensor *copie;
	copie = sortare(senzor, nrsenzori);
	eliberare(senzor, nrsenzori);
	senzor = copie;
	while (1)
	{
		char operatie[10];
		int i;
		scanf("%s", operatie);
		if (strcmp(operatie, "exit") == 0)
		{
			break;
		}
		else if (strcmp(operatie, "analyze") == 0)
		{
			scanf("%d", &i);
			analize(senzor, i);
		}
		else if (strcmp(operatie, "print") == 0)
		{
			scanf("%d", &i);
			if (i < 0 || i >= nrsenzori)
			{
				fprintf(fout,"Index not in range!\n");
				continue;
			}
			int tip;
			if (senzor[i].sensor_type == TIRE)
			{
				tip = 0;
				fprintf(fout,"Tire Sensor\n");
			}
			else
			{
				tip = 1;
				fprintf(fout,"Power Management Unit\n");
			}
			if (tip == 0)
			{
				tire_sensor *dateroata;
				dateroata = (tire_sensor *)senzor[i].sensor_data;
				fprintf(fout,"Pressure: %.2f\n", dateroata->pressure);
				fprintf(fout,"Temperature: %.2f\n", dateroata->temperature);
				fprintf(fout,"Wear Level: %d%%\n", dateroata->wear_level);
				if (dateroata->performace_score == 0)
					fprintf(fout,"Performance Score: Not Calculated\n");
				else
					fprintf(fout,"Performance Score: %d\n", dateroata->performace_score);
			}
			else
			{
				power_management_unit *datepmu;
				datepmu = (power_management_unit *)senzor[i].sensor_data;
				fprintf(fout,"Voltage: %.2f\n", datepmu->voltage);
				fprintf(fout,"Current: %.2f\n", datepmu->current);
				fprintf(fout,"Power Consumption: %.2f\n", datepmu->power_consumption);
				fprintf(fout,"Energy Regen: %d%%\n", datepmu->energy_regen);
				fprintf(fout,"Energy Storage: %d%%\n", datepmu->energy_storage);
			}
		}
		else if (strcmp(operatie, "clear") == 0)
			clear(senzor, &nrsenzori);
	}
	eliberare(senzor, nrsenzori);
	senzor = NULL;
	fclose(fin);
	return 0;
}
