#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <iterator>
#include <fstream>

using namespace std;

#define INF 999999

typedef struct
{
    int** matriz;
    int numVertices;
    int numArestas;
} Grafo;

//Cria matriz nxn
Grafo* criaMatriz(int numVertices)
{
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
    grafo->numVertices = numVertices;

    // Aloca memória para a matriz de adjacências
    grafo->matriz = (int**)malloc(numVertices * sizeof(int*));

    for (int i = 0; i < numVertices; i++)
    {
        grafo->matriz[i] = (int*)malloc(numVertices * sizeof(int));
    }

    // Inicializa a matriz de adjacências
    for (int i = 0; i < numVertices; i++)
    {
        for (int j = 0; j < numVertices; j++)
        {
            grafo->matriz[i][j] = 0;
        }
    }

return grafo;
}

//Implementa o algoritmo de Floyd-Warshall e Atualiza a matriz de adjacências
Grafo* criaMatrizWarshall(Grafo *grafo)
{
    int i, j, k;

    for (k = 0; k < grafo->numVertices; k++)
    {
        for (i = 0; i < grafo->numVertices; i++)
        {
            for (j = 0; j < grafo->numVertices; j++)
            {
                if (grafo->matriz[i][j] >= 0 && grafo->matriz[i][k] >= 0 && grafo->matriz[k][j] >= 0
                    && grafo->matriz[i][j] > (grafo->matriz[i][k] + grafo->matriz[k][j])
                    && (grafo->matriz[k][j] != INF
                    && grafo->matriz[i][k] != INF))
                {
                    //cout << "\n " << grafo->matriz[i][j] << " " << k << " " << i << " " << j;
                    grafo->matriz[i][j] = grafo->matriz[i][k] + grafo->matriz[k][j];
                    //cout << "\n " << grafo->matriz[i][j];
                }
                // AAAA
            }
        }
    }

    return grafo;
}



void adicionaPesos(Grafo* grafo, int u, int v, int p, int dir)
{
    if(dir == 0)
    {
        if(p < grafo->matriz[u][v])
        {
            grafo->matriz[u][v] = p;
            grafo->matriz[v][u] = p;
        }
        else if(grafo->matriz[u][v] < 0)
        {
            grafo->matriz[v][u] = p;
        }
    }
    else if(dir == 1)
    {
        if(p < grafo->matriz[u][v])
        {
            grafo->matriz[u][v] = p;
        }
    }
    else
    {
        cout << "\n\nERROPESOS\n\n";
    }

}

void instanciaInfinito(Grafo* grafo)
{
    for(int i = 0; i < grafo->numVertices; i++)
    {
        for(int j = 0; j < grafo->numVertices; j++)
        {
            if(grafo->matriz[i][j] == 0 && i != j)
            {
                grafo->matriz[i][j] = INF;
            }
        }
    }
}

void adicionaArestaIncidencias(Grafo* grafo, int u, int v, int linhaIncidencias, int dir)
{
    // Adiciona uma aresta na matriz de incidencias

    if(dir == 0)
    {
        grafo->matriz[linhaIncidencias][u] = 1;
        grafo->matriz[linhaIncidencias][v] = 1;
    }
    else if(dir == 1)
    {
        grafo->matriz[linhaIncidencias][u] = -1;
        grafo->matriz[linhaIncidencias][v] = 1;
    }
    else
    {
        cout << "\n\nDados invalidos\n\n";
    }

    linhaIncidencias++;
}





void liberaMatriz(Grafo* grafo)
{
    // Libera a memória alocada para a matriz de adjacências
    for (int i = 0; i < grafo->numVertices; i++)
    {
        free(grafo->matriz[i]);
    }
    free(grafo->matriz);
    free(grafo);
}

//Fiz uma função diferente para liberar memoria da matriz incidencias
void liberaMatrizInc(Grafo* grafo)
{
    for (int i = 0; i < grafo->numArestas; i++)
    {
        free(grafo->matriz[i]);
    }
    free(grafo->matriz);
    free(grafo);
}




void procuraLin(Grafo* grafo, int lin, int* linArray)
{
    for(int i = 0; i < grafo->numVertices; i++)
    {
        linArray[i] = grafo->matriz[lin][i];
    }
}

int procuraLinUnico(Grafo* grafo, int lin)
{
    for(int i = 0; i < grafo->numVertices; i++)
    {
        if(grafo->matriz[lin][i] != 0)
        {
            return grafo->matriz[lin][i];
        }
    }

    return 0;
}

void procuraCol(Grafo* grafo, int col, int* colArray)
{
    for(int i = 0; i < grafo->numArestas; i++)
    {
        colArray[i] = grafo->matriz[i][col];
    }
}

int procuraColUnico(Grafo* grafo, int col)
{
    for(int i = 0; i < grafo->numVertices; i++)
    {
        if(grafo->matriz[i][col] != 0)
        {
            return grafo->matriz[i][col];
        }
    }

    return 0;
}

void copiaMatrizVertices(Grafo* grafo, Grafo* grafo2)
{
    for(int i = 0; i < grafo->numVertices; i++)
    {
        for(int j = 0; j < grafo->numVertices; j++)
        {
            grafo->matriz[i][j] = grafo2->matriz[i][j];
        }
    }
}


int tamanhoMatriz(Grafo *grafo)
{
    return grafo->numArestas;
}

int ordemMatriz(Grafo *grafo)
{
    return grafo->numVertices;
}


int somaLinha(Grafo* grafo, int linha)
{
    int aux = 0;
    for(int i = 0; i < grafo->numVertices; i++)
    {
        if(grafo->matriz[linha][i] != INF)
            aux += grafo->matriz[linha][i];
    }

    return aux;
}

int somaColuna(Grafo* grafo, int coluna)
{
    int aux = 0;
    for(int i = 0; i < grafo->numVertices; i++)
    {
        if(grafo->matriz[i][coluna] != INF)
            aux += grafo->matriz[i][coluna];
    }

    return aux;
}



int maxLinha(Grafo* grafo, int linha)
{
    int aux = 0;
    for(int i = 0; i < grafo->numVertices; i++)
    {
        if(grafo->matriz[linha][i] > aux && grafo->matriz[linha][i] != INF)
        {
            aux = grafo->matriz[linha][i];
        }
    }

    if(aux != INF)
        return aux;
    else
        return 0;
}

int maxColuna(Grafo* grafo, int coluna)
{
    int aux = 0;
    for(int i = 0; i < grafo->numVertices; i++)
    {
        if(grafo->matriz[i][coluna] > aux && grafo->matriz[i][coluna] != INF)
        {
            aux = grafo->matriz[i][coluna];
        }
    }

    if(aux != INF)
        return aux;
    else
        return 0;
}

int minLinha(Grafo* grafo, int linha)
{
    int aux = procuraLinUnico(grafo, linha);

    for(int i = 0; i < grafo->numVertices; i++)
    {
        if(grafo->matriz[linha][i] < aux && linha != i)
        {
            aux = grafo->matriz[linha][i];
        }
    }

    return aux;
}

int minColuna(Grafo* grafo, int coluna)
{
    int aux = procuraColUnico(grafo, coluna);
    bool pegouNum = false;

    for(int i = 0; i < grafo->numVertices; i++)
    {
        if(grafo->matriz[i][coluna] < aux && coluna != i)
        {
            aux = grafo->matriz[i][coluna];
            pegouNum = true;
        }
    }


    return aux;
}

void VertVertGrafoParaCSV(Grafo* grafo, string fileName)
{
    std::ofstream file;
    fileName += ".csv";
    file.open(fileName);

    for(int i = 0; i < grafo->numVertices; i++)
    {
        for(int j = 0; j < grafo->numVertices; j++)
        {
            if(j == grafo->numVertices - 1)
            {
                file << grafo->matriz[i][j];
                file << "; " << "; " << maxLinha(grafo, i);
                file << "; " << minLinha(grafo, i);
                file << "; " << somaLinha(grafo, i);
                file << "\n";
            }
            else
            {
                file << grafo->matriz[i][j];
                file << "; ";
            }
        }
    }

    file.close();
}

void VertAresGrafoParaCSV(Grafo* grafo, string fileName)
{
    std::ofstream file;
    fileName += ".csv";
    file.open(fileName);

    for(int i = 0; i < grafo->numArestas; i++)
    {
        for(int j = 0; j < grafo->numVertices; j++)
        {
            if(j == grafo->numVertices - 1)
            {
                file << grafo->matriz[i][j];
                file << "; " << "; " << maxColuna(grafo, i);
                file << "; " << minColuna(grafo, i);
                file << "; " << somaColuna(grafo, i);
                file << "\n";
            }
            else
            {
                file << grafo->matriz[i][j];
                file << "; ";
            }
        }
    }

    file.close();
}

int main()
{
    char filename[100]; // nome do arquivo
    FILE* file;

    printf("\nDigite o nome do arquivo: ");
    scanf("%s", filename);

    //Abre o arquivo para leitura
    file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    int numVertices, numArestas;
    fscanf(file, "%d %d", &numVertices, &numArestas);



    Grafo* grafoPesos = criaMatriz(numVertices);

    Grafo* grafoFloydWarshall = criaMatriz(numVertices);

    instanciaInfinito(grafoPesos);

    for (int i = 0; i < numArestas; i++)
    {
        /* Arquivo exemplo:
            0  1  1  0
            u  v  p  dir
        */
        int dir, u, v, p;
        fscanf(file, "%d %d %d %d", &u, &v, &p, &dir);


        adicionaPesos(grafoPesos, u, v, p, dir);

    }


    fclose(file);



    copiaMatrizVertices(grafoFloydWarshall, grafoPesos);
    criaMatrizWarshall(grafoFloydWarshall);

    cout << "\n\nValores Linha e Coluna:";
    for(int i = 0; i < numVertices; i++)
    {
        cout << "\nMaior valor da linha " << i << " : " <<
        maxLinha(grafoFloydWarshall, i);
    }
    cout << "\n";

    for(int i = 0; i < numVertices; i++)
    {
        cout << "\nMaior valor da coluna " << i << " : " <<
        maxColuna(grafoFloydWarshall, i);
    }
    cout << "\n";

    for(int i = 0; i < numVertices; i++)
    {
        cout << "\nMenor valor da linha " << i << " : " <<
        minLinha(grafoFloydWarshall, i);
    }
    cout << "\n";

    for(int i = 0; i < numVertices; i++)
    {
        cout << "\nMenor valor da coluna " << i << " : " <<
        minColuna(grafoFloydWarshall, i);
    }
    cout << "\n";

    int vertIdeal = 0;
    int vertSoma = INF;
    for(int i = 0; i < numVertices; i++)
    {
        int valAux = somaLinha(grafoFloydWarshall, i);

        cout << "\nSoma dos valores da linha " << i << " : " << valAux;
        if(valAux < vertSoma)
        {
            vertIdeal = i;
            vertSoma = valAux;
        }
    }
    cout << "\n";

    for(int i = 0; i < numVertices; i++)
    {
        cout << "\nSoma dos valores da coluna " << i << " : " <<
        somaColuna(grafoFloydWarshall, i);
    }

    cout << "\n";


    cout << "A posicao ideal para o posto de saude e o vertice: " << vertIdeal << "\n";

    VertVertGrafoParaCSV(grafoFloydWarshall, "FloydWarshall");


    return 0;
}
