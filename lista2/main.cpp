/* 
 * File:   main.cpp
 * Author: seunome
 */

#include <list>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

using namespace std;

class MeuArquivo {
public:
    struct Cabecalho { int quantidade=0; int disponivel=0; } cabecalho;
    struct Registro { int quantidade; int disponivel; char * palavra; } registro;
    typedef struct Removido{int tamanho; int pos;} Removido;
    // construtor: abre arquivo. Essa aplicacao deveria ler o arquivo se existente ou criar um novo.
    // Entretando recriaremos o arquivo a cada execucao ("w+").
    MeuArquivo() {
        fd = fopen("dados.dat","w+");
    }

    // Destrutor: fecha arquivo
    ~MeuArquivo() {
        fclose(fd);
    }

    // Insere uma nova palavra, consulta se há espaco disponível ou se deve inserir no final
    void inserePalavra(char *palavra) {
        this->substituiBarraNporBarraZero(palavra); // funcao auxiliar substitui terminador por \0
        // Adicionando nova palavra
        int tam = strlen(palavra);
        int substituir = this->procurarRegistroDisponivel(tam);
        if(substituir >=0){ // Caso exista um espaco no meio dos registro que caiba a palavra apenas o preencha e atualize o cabecalho
            fseek(fd, substituir, SEEK_SET);
            this->atualizarCabecalho(true, 0);
        }else{ // Caso contrario, faca a insercao no final e atualize o campo disponivel do cabecalho
            fseek(fd, cabecalho.disponivel, SEEK_SET);
            fwrite(&tam, sizeof(int), 1, fd);
            this->atualizarCabecalho(true, tam+sizeof(int));
        }
        fwrite(palavra, sizeof(char), tam, fd);
        fseek(fd, 0, SEEK_SET);
    }

    // Marca registro como removido, atualiza lista de disponíveis, incluindo o cabecalho
    void removePalavra(int offset) {
        char *found = new char[50]; 
        int next_size, pos = 0 , i = 0;
        while (!feof(fd)) {
            fread(&next_size, 1, sizeof(int), fd);
            pos +=4;
            fread(found, next_size, sizeof(char), fd);
            if(++i == offset){
                // Se encontrado esvazia a string e a adiona o * como substituto
                memset(found, 0, next_size*sizeof(char));
                found[0] = '*';
                found[next_size-1] = '\0';
                fseek(fd, pos, SEEK_SET);
                fwrite(found, sizeof(char), next_size, fd);
                //Atualiza cabecalho indicando uma remocao e alocacao não alterada
                atualizarCabecalho(false, 0);
                // Adiciona um novo registo do tipo removido na lista de removidos
                Removido d;
                d.pos = pos;
                d.tamanho = next_size;
                removidos.push_front(d);
            }
            pos += next_size;
            memset(found, 0, 50);
        }
        fseek(fd, 0, SEEK_SET);
    }

    // BuscaPalavra: retorno é o offset para o registro
    // Nao deve considerar registro removido
    int buscaPalavra(char *palavra) {
        this->substituiBarraNporBarraZero(palavra); // funcao auxiliar substitui terminador por \0
        
        char *found = new char[50]; 
        int next_size;
        int i = 0;
        while (!feof(fd)) {
            fread(&next_size, 1, sizeof(int), fd);
            fread(found, next_size, sizeof(char), fd);
            if(strcmp(palavra, found) == 0){
                fseek(fd, 0, SEEK_SET);
                return ++i;
            }
             memset(found, 0, sizeof(char)*50); 
             i++;
        }
        fseek(fd, 0, SEEK_SET);
        // retornar -1 caso nao encontrar
        return -1;
    }

private:
    // descritor do arquivo é privado, apenas métodos da classe podem acessa-lo
    FILE *fd;
    list<Removido> removidos;
    // funcao auxiliar substitui terminador por \0
    void substituiBarraNporBarraZero(char *str) {
        int tam = strlen(str); 
        for (int i = 0; i < tam; i++) 
            if (str[i] == '\n') str[i] = '\0';
    }

    // Funcao auxiliar que busca por espacos de palavras removidas que caibam uma nova palavra de tamanho igual ou inferior a ela
    int procurarRegistroDisponivel(int str_len){
        list <Removido> :: iterator it;
        for(it = removidos.begin(); it != removidos.end(); ++it){
            if(it->tamanho >= str_len){
                removidos.erase(it);
                return it->pos;
            }
        }
        return -1;
    }

    // Funcao que mantem o cabecalho atualizado
    void atualizarCabecalho(bool add, int bytes_added){
        cabecalho.disponivel += bytes_added;
        if(add) 
            cabecalho.quantidade++;
        else 
            cabecalho.quantidade--;
    }
};

int main(int argc, char** argv) {
    // abrindo arquivo dicionario.txt
    FILE *f = fopen("dicionario.txt","rt");

    // se não abriu
    if (f == NULL) {
        printf("Erro ao abrir arquivo.\n\n");
        return 0;
    }

    char *palavra = new char[50];

    // criando arquivo de dados
    MeuArquivo *arquivo = new MeuArquivo();
    while (!feof(f)) {
        fgets(palavra,50,f);
        arquivo->inserePalavra(palavra);
        memset(palavra, 0, sizeof(char)*50);
    }

    // fechar arquivo dicionario.txt
    fclose(f);

    printf("Arquivo criado.\n\n");

    char opcao;
    do {
        printf("\n\n1-Insere\n2-Remove\n3-Busca\n4-Sair\nOpcao:");
        opcao = getchar();
        if (opcao == '1') {
            printf("Palavra: ");
            scanf("%s",palavra);
            arquivo->inserePalavra(palavra);
        }
        else if (opcao == '2') {
            printf("Palavra: ");
            scanf("%s",palavra);
            int offset = arquivo->buscaPalavra(palavra);
            if (offset >= 0) {
                arquivo->removePalavra(offset);
                printf("Removido.\n\n");
            }
        }
        else if (opcao == '3') {
            printf("Palavra: ");
            scanf("%s",palavra);
            int offset = arquivo->buscaPalavra(palavra);
            if (offset >= 0)
                printf("Encontrou %s na posição %d\n\n",palavra,offset);
            else
                printf("Não encontrou %s\n\n",palavra);
        }
        if (opcao != '4') opcao = getchar();
    } while (opcao != '4');

    printf("\n\nAte mais!\n\n");

    return (EXIT_SUCCESS);
}
