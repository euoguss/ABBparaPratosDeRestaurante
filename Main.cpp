#include <iostream>
#include <string>

using namespace std;

struct Prato {
    int codPrato;
    string nome;
    double preco;
    Prato* esquerda;
    Prato* direita;

    Prato(int codPrato, string nome, double preco) {
        this->codPrato = codPrato;
        this->nome = nome;
        this->preco = preco;
        esquerda = direita = nullptr;
    }
};

class CardapioBST {
private:
    Prato* raiz;

    Prato* inserir(Prato* raiz, int codPrato, string nome, double preco) {
        if (raiz == nullptr) {
            return new Prato(codPrato, nome, preco);
        }

        if (codPrato < raiz->codPrato) {
            raiz->esquerda = inserir(raiz->esquerda, codPrato, nome, preco);
        } else if (codPrato > raiz->codPrato) {
            raiz->direita = inserir(raiz->direita, codPrato, nome, preco);
        }

        return raiz;
    }

    Prato* buscar(Prato* raiz, int codPrato) {
        if (raiz == nullptr || raiz->codPrato == codPrato) {
            return raiz;
        }

        return (codPrato < raiz->codPrato) ? buscar(raiz->esquerda, codPrato) : buscar(raiz->direita, codPrato);
    }

    Prato* remover(Prato* raiz, int codPrato) {
        if (raiz == nullptr) return raiz;

        if (codPrato < raiz->codPrato) {
            raiz->esquerda = remover(raiz->esquerda, codPrato);
        } else if (codPrato > raiz->codPrato) {
            raiz->direita = remover(raiz->direita, codPrato);
        } else {
            if (raiz->esquerda == nullptr) {
                Prato* temp = raiz->direita;
                delete raiz;
                return temp;
            } else if (raiz->direita == nullptr) {
                Prato* temp = raiz->esquerda;
                delete raiz;
                return temp;
            }

            Prato* temp = minValor(raiz->direita);
            raiz->codPrato = temp->codPrato;
            raiz->nome = temp->nome;
            raiz->preco = temp->preco;
            raiz->direita = remover(raiz->direita, temp->codPrato);
        }

        return raiz;
    }

    Prato* minValor(Prato* raiz) {
        while (raiz->esquerda != nullptr) { // Correção do loop
            raiz = raiz->esquerda;
        }
        return raiz;
    }

    void ordenar(Prato* raiz) {
        if (raiz != nullptr) {
            ordenar(raiz->esquerda);
            cout << "Código do Prato: " << raiz->codPrato 
                 << " | Nome: " << raiz->nome 
                 << " | Preço: R$ " << raiz->preco << endl;
            ordenar(raiz->direita);
        }
    }

public:
    CardapioBST() {
        raiz = nullptr;
    }

    void adicionarPrato(int codPrato, string nome, double preco) {
        raiz = inserir(raiz, codPrato, nome, preco);
    }

    bool buscarPrato(int codPrato) {
        return buscar(raiz, codPrato) != nullptr;
    }

    void removerPrato(int codPrato) {
        raiz = remover(raiz, codPrato);
    }

    void exibirCardapio() {
        ordenar(raiz);
    }
};

int main() {
    CardapioBST cardapio;

    cardapio.adicionarPrato(101, "Pizza Margherita", 25.90);
    cardapio.adicionarPrato(102, "Hambúrguer Artesanal", 18.50);
    cardapio.adicionarPrato(103, "Salada Caesar", 15.00);
    cardapio.adicionarPrato(104, "Lasanha Bolonhesa", 30.00);

    cout << "Cardápio do Restaurante:\n";
    cardapio.exibirCardapio();

    cout << "\n Buscar prato (Código 102):\n";
    cout << (cardapio.buscarPrato(102) ? "Prato encontrado!" : "Prato não encontrado!") << endl;

    cout << "\n Removendo prato (Código 103)...\n";
    cardapio.removerPrato(103);

    cout << "\n Cardápio atualizado:\n";
    cardapio.exibirCardapio();

    return 0;
}
