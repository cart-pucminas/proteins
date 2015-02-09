#include <iostream>
#include "libxl.h"
#include<string.h>
#include<string>
#include <sstream>
#include <stdio.h>
#include <fstream>      // std::ifstream
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <locale.h>
#include <langinfo.h>
#include <stdint.h>
#include <errno.h>
#include <fcntl.h>
#include <dirent.h>
#include <cstdlib>


using namespace std;

//funcoes
int listaArquivos(string);


int main() 
{

    string classes [6] ={"Hidrolases","Isomerases","Liases","Ligases","Oxidoredutases","Transferases"}; 
      for(int i = 0; i < 1; i++)
      {     
            cout<<"-------"+classes[i]+"-------"<<endl;
            listaArquivos ("/home/larissa/Desktop/BaseCsv/"+classes[i]+"/");
      }
            return 0;

}

int listaArquivos (string nomeDir) {
    DIR *dir = 0;
    struct dirent *entrada = 0;
    unsigned char isDir = 0x4;
    unsigned char isFile = 0x8;
 
    dir = opendir (nomeDir.c_str());
 
    if (dir == 0) {
        std::cerr << "Nao foi possivel abrir diretorio." << std::endl;
        exit (1);
    }
 
    //Iterar sobre o diretorio
    while (entrada = readdir (dir))
    {
        if (entrada->d_type == isFile)
        {
            std::cout << entrada->d_name << std::endl;
        }
        char dir [nomeDir.size()];
        strcpy(dir, nomeDir.c_str());
        
        const char* nome = entrada->d_name;
        char* path = strcat(dir,nome); 

                
        ifstream file;
        file.open (path, ifstream::in); 
        string value;

        char * pch;
        
        //Leitura do arquivo
        while ( file.good() )
        {
             getline ( file, value); 
             char split [value.size()];
             strcpy(split, value.c_str());
             pch = strtok (split,";");
                  while (pch != NULL)
                  {
                    printf ("%s\n",pch);
                    pch = strtok (NULL, ";");
                  }
           // cout << string( value, 0, value.length())<<endl; 
             break;
        }
            
            
    }
    closedir (dir);
     
    return 0;
}
