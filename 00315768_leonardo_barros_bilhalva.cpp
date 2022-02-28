//+------------------------------------------------------------------+
//|                                                   Laboratório 03 |
//|              Alunos: Leonardo Barros Bilhalva  e Santiago Gonzaga|
//|                     Disciplina: Classificação e Pesquisa de Dados|
//+------------------------------------------------------------------+
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int tamanhoMaximo(vector<string> &data)       //Acha o tamanho da maior string no string de vetores
{
  int lenMax = 0;
  for(int q = data.size()-1; q>=0; q--)       //Percorre todas as palavras possíveis
  {
  if(data[q].size() > lenMax)                // Se a palavra atual for maior do que a última maior palavra registrada
    lenMax = data[q].size();                 // ela é a nova maior palavra
  }
  return lenMax;                            //retorna o tamanho da maior palavra
}

void countSort(vector<string> &data, int i)
{
int counts[256] = { 0 };                    // São 256 possibilidades para um unsigned char, ou seja, 256 "ESCANINHOS" possíveis -- Inicializa todos contadores com 0.   

for(int q = data.size()-1; q>=0; q--)       //Percorre todas as palavras possíveis para pegar cada digito i delas
{
  string b = data[q];
  for(int a = 0; a<=256; a++)              //Percorre todos os escaninhos possíveis para iniciar a comparação escaninho - letra
  {
    if(b.size() < i)                       //Se a palavra atual não tiver o digito i(ser de tamanho menor do que i), encontramos um '\0'
    {
      counts[0]++;
      break;                              //Se "resolveu" a letra, pode pular para a próxima palavra
    }
    if(b[i] == (char)a)                   //Incrementa o escaninho do valor encontrado
    {
    counts[a]++;
    break;
    }
  }
}
     
int total = 0;
for(int a = 0; a<=256; a++)              //Percorre todos os escaninhos para fazer a fase de acumulação(somar o atual a todos da posteriores)
  {
    counts [a] += total;
    total = counts[a];
  }
  
vector<string> buffer(data.size());      // aloca um buffer auxiliar para facilitar as movimentações

int d;                                  // Variável para facilitar o entendimento da operação com o buffer
  for(int q = data.size()-1; q>=0; q--) //Percorre todas as palavras possíveis para pegar cada digito i delas
{
  string b = data[q];                 
  for(int a = 0; a<=256; a++)           //Percorre todos os escaninhos possíveis para iniciar a comparação escaninho - letra
  {
    if(b.size() < i)                    //Se a palavra atual não tiver o digito i(ser de tamanho menor do que i), colocamos ela na posição 0 possível
    {      
      counts[0]--;
      d = counts[0];
      buffer[d] = move(b);
      break;
    }
    if(b[i] == (char)a)                 //Se a o digito i da palavra atual for igual ao escaninho atual, colocamos a palavra na sua posição correta
    {               
      counts[a]--;
      d = counts[a];
      buffer[d] = move(b);
      break;
    }
  }
}
  data = move(buffer);                   // devolve o buffer auxiliar em data para o fim do processo
}

void RadixSort(vector<string> &data)
{
  int len = tamanhoMaximo(data);      // Utiliza tamanhoMaximo para retornar o tamanho da maior string do vetor de strings
  for (int i = len; i--;) {           // Começa com o tamanho(maior valor)(MSD) e vai diminuindo para seguir
    countSort(data, i);

    /*int a=0;                        // Desnecessário para o código -> Aqui deixei uma opção para printar o vetor de strings a cada loop do countSort
    for (int i = 24; i>0 ;i--){
    cout << data[i] << " ";
    if(data[i] == "\0" )
    a++;}    
    cout << a << endl;*/
  }
}

//---------------------------------------------------------------------------------------------------------------------------------

int main()
{  
    //---------------------------------------------------------frankestein
    cout << "Frankestein comecou!" << endl;
    ifstream leitura_entrada_frankestein;       //Inicia o Arquivo de leitura
    ofstream escrita_frankestein_ordenado;           //inicia o Stats de saída

    string linha_frankestein;                   //Strings para leitura do arquivo
    string word_frankestein;                    
    vector<string> words_frankestein;           //Vetor para alocação do arquivo
    unsigned int i_frankestein = 0;                      //Contador para vetor de palavras
    int word_count_frankestein = 0;             //Contador para quantidade de palavras

    leitura_entrada_frankestein.open("frankenstein.txt");    //Abre arquivos
    escrita_frankestein_ordenado.open("frankestein_ordenado.txt");

    getline(leitura_entrada_frankestein, linha_frankestein);        //pega a linha

    istringstream ss_frankestein(linha_frankestein);                //  \/---- Função para "quebrar" a linha recebida em getlin
    bool tem_caracteres_diferentes_de_letras_frank = false;
    while (ss_frankestein>>word_frankestein)
    { 
      tem_caracteres_diferentes_de_letras_frank = false;  
      for(unsigned int c = 0; c < word_frankestein.size(); c++)
      { 
        if(isalpha(word_frankestein[c]) == 0)                     //isalpha retorna verdadeiro se faz parte do alfabeto. Aqui eu confiro se a letra não faz parte do alfabeto.
        {
          tem_caracteres_diferentes_de_letras_frank = true;
        }        
      }      
      if(word_frankestein.size() > 3 && tem_caracteres_diferentes_de_letras_frank == false)                        // Só registra palavras com tamanho maior que 3 e somente com letras
      words_frankestein.push_back(word_frankestein);         // Aloca as palavras no vector de strings words
    }                                                               //  /\---

    /*while( i_frankestein < words_frankestein.size())                //While desnecessário para o código -> Ele mostra o que na prompt quais palavras foram alocadas
        {
            cout << words_frankestein[i_frankestein] << " ";
            i++;
        }*/

    RadixSort(words_frankestein);                        //Função para ordenar o vetor

    i_frankestein=0;// reseta o índice do vetor de strings
    while( i_frankestein < words_frankestein.size())
        {
          word_count_frankestein=1;                   //Toda palavra achada começa com contagem = 1
          while(words_frankestein[i_frankestein] == words_frankestein [i_frankestein+1])  //While para contar palavras repetidas
            {
             i_frankestein++;
             word_count_frankestein++;
            }      
          escrita_frankestein_ordenado << words_frankestein[i_frankestein] << " ";   // Escreve a palavra no arquivo ordenado
          escrita_frankestein_ordenado << word_count_frankestein << endl;            // Escreve a contagem dela e da uma nova linha para a proxima palavra
          i_frankestein++;                                                      // Pula para a proxima palavra
        }

    leitura_entrada_frankestein.close();                // Fecha arquivos
    escrita_frankestein_ordenado.close();
    cout << "Frankestein terminou com sucesso!" << endl;
    
    //---------------------------------------------------------war and peace

    cout << "War and peace comecou!" << endl;
    ifstream leitura_entrada_war_and_peace;       //Inicia o Arquivo de leitura
    ofstream escrita_war_and_peace_ordenado;           //inicia o Stats de saída

    string linha_war_and_peace;                   //Strings para leitura do arquivo
    string word_war_and_peace;                    
    vector<string> words_war_and_peace;           //Vetor para alocação do arquivo
    unsigned int i_war_and_peace = 0;                      //Contador para vetor de palavras
    int word_count_war_and_peace = 0;             //Contador para quantidade de palavras

    leitura_entrada_war_and_peace.open("war_and_peace.txt");    //Abre arquivos
    escrita_war_and_peace_ordenado.open("war_and_peace_ordenado.txt");

    getline(leitura_entrada_war_and_peace, linha_war_and_peace);        //pega a linha

    istringstream ss_war_and_peace(linha_war_and_peace);                //  \/---- Função para "quebrar" a linha recebida em getline
    bool tem_caracteres_diferentes_de_letras_war = false;
    while (ss_war_and_peace>>word_war_and_peace)
    {        
      tem_caracteres_diferentes_de_letras_war = false;
      for(unsigned int c = 0; c < word_war_and_peace.size(); c++)
      { 
        if(isalpha(word_war_and_peace[c]) == 0)                     //isalpha retorna verdadeiro se faz parte do alfabeto. Aqui eu confiro se a letra não faz parte do alfabeto.
        {
          tem_caracteres_diferentes_de_letras_war = true;
        }        
      }      
      if(word_war_and_peace.size() > 3 && tem_caracteres_diferentes_de_letras_war == false)               // Só registra palavras com tamanho maior que 3 e somente com letras
      words_war_and_peace.push_back(word_war_and_peace);         // Aloca as palavras no vector de strings words

    }                                                                   //  /\---

    /*while( i_war_and_peace < words_war_and_peace.size())              //While desnecessário para o código -> Ele mostra o que na prompt quais palavras foram alocadas
        {
            cout << words_war_and_peace[i_war_and_peace] << " ";
            i++;
        }*/

    RadixSort(words_war_and_peace);                                     //Função para ordenar o vetor

    i_war_and_peace=0;// reseta o índice do vetor de strings
    while( i_war_and_peace < words_war_and_peace.size())
        {
          word_count_war_and_peace=1;                   //Toda palavra achada começa com contagem = 1
          while(words_war_and_peace[i_war_and_peace] == words_war_and_peace [i_war_and_peace+1])  //While para contar palavras repetidas
            {
             i_war_and_peace++;
             word_count_war_and_peace++;
            }      
          escrita_war_and_peace_ordenado << words_war_and_peace[i_war_and_peace] << " ";   // Escreve a palavra no arquivo ordenado
          escrita_war_and_peace_ordenado << word_count_war_and_peace << endl;              // Escreve a contagem dela e da uma nova linha para a proxima palavra
          i_war_and_peace++;                                                          // Pula para a proxima palavra
        }

    leitura_entrada_war_and_peace.close();                // Fecha arquivos
    escrita_war_and_peace_ordenado.close();
    cout << "War and peace terminou com sucesso!";

    return 0;
}
