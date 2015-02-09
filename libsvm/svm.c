#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define Malloc(type,n) (type *)malloc((n)*sizeof(type))

/*
       float* readDatabase(); // ler a base de dados e carrega para a memoria primaria
       float* normalize(float* dataBase)

        /* genetic algorithm 

       float* selectFeature(float* dataBaseNormalized, ); //seleciona da base de dados o conjunto de caracteristicas 
       float* discreteCossineTransform(float* selectedData);
       float supportVectorMachine(float* transformedBase, float C, float gamma)
       
       /* suppot vector machine
       

*/
void read(const char *filename);


static char *line = NULL;
static int max_line_len;

static char* readline(FILE *input)
{
	int len;
	
	if(fgets(line,max_line_len,input) == NULL)
		return NULL;

	while(strrchr(line,'\n') == NULL)
	{
		max_line_len *= 2;
		line = (char *) realloc(line,max_line_len);
		len = (int) strlen(line);
		if(fgets(line+len,max_line_len-len,input) == NULL)
			break;
	}
	return line;
}

int main()
{

        // determine filenames
	char *input_file_name = "svmguide4.t";
	read(input_file_name);
		

	return 0;
}

// read in a problem (in svmlight format)

void read(const char *filename)
{
	int max_index, inst_max_index, i;
	size_t  j;
	int numFeatures,numProteins;
	FILE *fp = fopen(filename,"r");
	char *endptr;
	char *idx, *val, *label;

	if(fp == NULL)
	{
		fprintf(stderr,"can't open input file %s\n",filename);
		exit(1);
	}

	numProteins = 0;
	numFeatures = 0;

	max_line_len = 1024;
	line = Malloc(char,max_line_len);
	
	while(readline(fp)!=NULL)
	{
		char *p = strtok(line," \t"); // label

		// features
		while(1)
		{
			p = strtok(NULL," \t");
			if(p == NULL || *p == '\n') // check '\n' as ' ' may be after the last feature
				break;
			++numFeatures;
		}
		++numFeatures;//numero de caracteristicas
		++numProteins;//numero de instancias
	}
	rewind(fp);
	
	printf("quantidade de Caracteristicas: %d \n",numFeatures);
	
        printf("quantidade de Proteinas: %d \n",numProteins);
	

	
        float *data  = (float*)malloc((numProteins*numFeatures) * sizeof(float));   
	
	for(i=0;i<numProteins;i++)
	{

		readline(fp);
		label = strtok(line," \t\n");
		data[i] = strtod(label,&endptr);
				     
		//printf("%.1f ",strtod(label,&endptr));

		while(1)
		{
			idx = strtok(NULL,":");
			val = strtok(NULL," \t");
                        
                   if(val == NULL)
		     break;
                        
			data[i]= strtod(val,&endptr);
		        //printf("%.1f ",strtod(val,&endptr));

		}
		
                  printf("\n");

	}

	fclose(fp);
}

//float svm(unsigned *label, float *data, unsigned width, unsigned height, float c, float gamma)
//{
      

        /* Cross validation. */
        
        /* Train. */
        
        /* Prediction. */

  //      return (accuracy);
//}
