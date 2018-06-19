//
//  TestTable.cpp
//
//  Created by Eiji Adachi Medeiros Barbosa 
//

#include "TestTable.h"
#include "HashTable.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

extern HashEntry<std::string, std::string> *ENTRY_DELETED;

bool testar_Criar()
{
    cout << "INÍCIO: Teste Criar" << endl;
    
    bool resultado = true;
    
    int tamanhoDesejado = 7;
    
    HashTable *tabela = new HashTable(tamanhoDesejado);
    
    if( tabela == NULL )
    {
        cout << "\t*ERRO - Teste Criar: Tabela retornada é nula." << endl;
        resultado = false;
    }
    else if( tabela->getSize() != tamanhoDesejado )
    {
        cout << "\t*ERRO - Teste Criar: Tabela deveria ter tamanho igual a " << tamanhoDesejado << ", mas foi criada com tamanho igual a " << tabela->getSize() << endl;
        resultado = false;
    }
    else if( tabela->getQuantity() != 0 )
    {
        cout << "\t*ERRO - Teste Criar: Tabela deveria ter quantidade de elementos igual a 0, mas foi criada com quantidade igual a " << tabela->getQuantity() << endl;
        resultado = false;
    }
    
    delete tabela;
    
    cout << "FIM: Teste Criar" << endl;
    
    return resultado;
}

bool testar_Buscar_CasoNormal()
{
    HashTable* tabela = new HashTable(13);
    
    string chavesStr[5] = {"chave", "echav", "vecha", "avech", "havec"};
    string conteudosStr[5] = {"C1", "C2", "C3", "C4", "C5"};
    
    for( int i = 0; i < 5; i++)
    {
        tabela->put( conteudosStr[i], chavesStr[i] );
    }
    
    
    string valor = "Conteudo";
    string chave = "acehv";
    
    tabela->put(chave, valor);
    
    
    string retornado = tabela->get(chave);
    
    bool resultado = true;
    
    if( retornado != valor )
    {
        cout << "\t*ERRO - Teste Buscar - Caso Normal: Buscou por chave '" << chave << "', mas não retornou valor esperado. Retornou: " << retornado << ". Esperado era:" << valor << "'." << endl;
        
        resultado = false;
    }
    
    string naoAchou = tabela->get("NAO EXISTE");
    
    if( naoAchou != "" )
    {
        cout << "\t*ERRO - Teste Buscar - Caso Normal: Buscou por chave que não existe mas não retornou string vazia." << endl;
        
        resultado = false;
    }
    
    delete tabela;
    
    return resultado;
}

bool testar_Buscar_ComRemocoes()
{
    HashTable* tabela = new HashTable(17);
    
    string chavesStr[5] = {"chave", "echav", "vecha", "avech", "havec"};
    string conteudosStr[5] = {"C1", "C2", "C3", "C4", "C5"};
    
    for( int i = 0; i < 5; i++)
    {
        string it = conteudosStr[i];
        string ch = chavesStr[i];
        
        tabela->put(ch, it);
        
        if(i%2==1)
        {
            tabela->remove(ch);
        }
    }
    
    string valor = "Conteudo";
    string chave = "acehv";
    
    tabela->put(chave, valor);
    
    string retornado = tabela->get(chave);
    
    bool resultado = true;
    
    if( retornado != valor )
    {
        cout << "\t*ERRO - Teste Buscar - Com remoções: Após algumas remoções, busca por uma chave que existe na tabela retornou outro valor. Valor retornado: '" << retornado << "'. Valor esperado:" << valor << endl;
        resultado = false;
    }
    
    delete tabela;
    
    return resultado;
}

bool testar_Buscar()
{
    cout << "\nINÍCIO: Testes Buscar" << endl;
    
    bool resultado = true;
    
    cout << "\tTeste Buscar - Caso Normal" << endl;
    resultado = testar_Buscar_CasoNormal();
    
    if(resultado)
    {
        cout << "\tTeste Buscar - Com Remoções" << endl;
        resultado = testar_Buscar_ComRemocoes();
    }
    
    cout << "FIM: Testes Buscar" << endl;
    
    return resultado;
}

bool testar_Inserir_CasoNormal()
{
    int tamanho = 17;
    HashTable* tabela = new HashTable(tamanho);
    
    bool inseriu = true;
    
    for(int i = 0; i < tamanho/2 && inseriu; i++)
    {
        string chaveStr = "chave-" + to_string(i);
        string valor = "conteudo-" + to_string(i);
        
        int tamanhoAntes = tabela->getSize();
        int qtdElementoAntes = tabela->getQuantity();
        
        inseriu = tabela->put(chaveStr, valor);
        
        int tamanhoDepois = tabela->getSize();
        int qtdElementoDepois = tabela->getQuantity();
        
        if( tamanhoAntes != tamanhoDepois )
        {
            cout << "\t*ERRO - Teste Inserir_CasoNormal: Tamanho foi modificado incorretamente. Tamanho só pode ser modificado quando ocorre redimensionamento." << endl;
            inseriu = false;
            break;
        }
        if( qtdElementoAntes != qtdElementoDepois-1 )
        {
            cout << "\t*ERRO - Teste Inserir_CasoNormal: Quantidade de elementos não foi incrementada corretamente." << endl;
            inseriu = false;
            break;
        }
    }
    
    delete tabela;
    
    return inseriu;
}

bool testar_Inserir_Atualizar()
{
    HashTable* tabela = new HashTable(7);
    
    string chave = "chave";
    string valor1 = "ConteudoInicial";
    string valor2 = "ConteudoAtualizado";
    
    tabela->put( chave, valor1 );
    
    tabela->put( chave, valor2 );
    
    bool resultado = true;
    
    if( tabela->getQuantity() == 1 )
    {
        for(int i = 0; i < tabela->getSize(); i++)
        {
            HashEntry<string, string> *entry = tabela->data[i];
            
            // A única entrada != null é a que foi atualizada com valor2
            // Se tiver alguém com value() != valor2, então está errado
            if( entry != nullptr && entry->getValue() != valor2)
            {
                cout << "\t*ERRO - Teste Inserir_Atualizar: Ao inserir dois itens com mesma chave, o valor do segundo deve sobrescrever valor do primeiro. Neste teste, dois elementos com mesma chave foram inseridos na tabela. O esperado era que o conteúdo do item na tabela fosse igual a '" << valor2 << "', mas valor encontrado foi igual a '" << entry->getValue() << "'." << endl;
                resultado = false;
                break;
            }
        }
    }
    else
    {
        cout << "\t*ERRO - Teste Inserir_Atualizar: Ao inserir dois itens com mesma chave, o valor do segundo deve sobrescrever valor do primeiro. Neste teste, dois elementos com mesma chave foram inseridos na tabela; o esperado era uma tabela com 1 item, mas a tabela ficou com " << tabela->getQuantity() << " itens." << endl;
        
        resultado = false;
    }
    
    delete tabela;
    
    return resultado;
}

bool testar_Inserir_Colisao()
{
    HashTable* tabela = new HashTable(17);
    string c1 = "abba";
    string i1 = "conteudo1";
    
    tabela->put(c1, i1);
    
    string c2 = "bbaa";
    string i2 = "conteudo2";
    
    tabela->put(c2,i2);
    
    bool achou1 = false, achou2 = false;
    for(int x = 0; x < tabela->getSize(); x++)
    {
        HashEntry<string, string> *entry = tabela->data[x];
        
        if( entry != nullptr && entry->getKey() == c1 )
        {
            achou1 = true;
        }
        
        if( entry != nullptr && entry->getKey() == c2 )
        {
            achou2 = true;
        }
    }
    
    bool resultado = true;
    if( (achou1 && !achou2)||(!achou1 && achou2) )
    {
        cout << "\t*ERRO - Teste Inserir_Colisao: Duas chaves que colidem foram inseridas, mas apenas uma foi encontrada na tabela. Provavelmente uma sobrescreveu a outra. Rever tratamento de colisão." << endl;
        resultado = false;
    }
    
    delete tabela;
    
    return resultado;
}

bool testar_Inserir()
{
    cout << "\nINÍCIO: Testes Inserir" << endl;
    
    bool resultado = true;
    
    cout << "\tTeste Inserir - Caso Normal" << endl;
    resultado = testar_Inserir_CasoNormal();
    
    if(resultado)
    {
        cout << "\tTeste Inserir - Colisão" << endl;
        resultado = testar_Inserir_Colisao();
    }
    if(resultado)
    {
        cout << "\tTeste Inserir - Caso Atualizar" << endl;
        resultado = testar_Inserir_Atualizar();
    }
    
    cout << "FIM: Testes Inserir" << endl;
    
    return resultado;
}

bool testar_Remover_CasoNormal()
{
    HashTable* tabela = new HashTable(17);
    
    string c1 = "abba";
    string i1 = "conteudo1";
    
    string c2 = "cdefg";
    string i2 = "conteudo2";
    
    string c3 = "baee";
    string i3 = "conteudo3";
    
    tabela->put(c1, i1);
    tabela->put(c2, i2);
    tabela->put(c3, i3);
    
    int qtdAntes = tabela->getQuantity();
    
    tabela->remove( c2 );
    
    bool resultado = true;
    
    int qtdDepois = tabela->getQuantity();
    
    if( qtdAntes - 1 != qtdDepois )
    {
        cout << "\t*ERRO - Teste Remover_CasoNormal: Não decrementou corretamente a quantidade de itens durante a remoção." << endl;
        resultado = false;
    }
    
    bool achou = false;
    for(int x = 0; x < tabela->getSize(); x++)
    {
        HashEntry<string, string>* c = tabela->data[x];
        
        if( c == nullptr ) continue;
        if( c == ENTRY_DELETED ) continue;
        if( c->getKey() == c2 )
        {
            achou = true;
            break;
        }
    }
    
    if(achou)
    {
        cout << "\t*ERRO - Teste Remover_CasoNormal: Remoção não foi feita corretamente, pois o item passado como parâmetro ainda foi encontrado na tabela." << endl;
        resultado = false;
    }
    
    delete tabela;
    
    return resultado;
}

bool testar_Remover_Sucessivas()
{
    int tamanho = 17;
    
    HashTable* tabela = new HashTable(tamanho);
    
    bool removeu = false;
    
    int qtdInserido = tabela->getSize()/2;
    int qtdRemovido = qtdInserido - 1 - tabela->getSize()/4;
    
    string base1 = "chave-";
    string base2 = "cheva-";
    string base3 = "hceva-";
    
    // Inicialização da tabela
    for(int i = 0; i < qtdInserido; i++)
    {
        string chave;
        
        if( i%3==0 )
        {
            chave = base1 + to_string(i);
        }
        else if( i%3==1 )
        {
            chave = base2 + to_string(i-1);
        }
        else
        {
            chave = base3 + to_string(i-2);
        }
        
        tabela->put(chave, "Conteudo" + to_string(i));
    }
    
    
    // Série de remoções com sucesso
    for(int i = 0; i < qtdRemovido; i++)
    {
        string chave;
        
        if( i%3==0 )
        {
            chave = base1 + to_string(i);
        }
        else if( i%3==1 )
        {
            chave = base2 + to_string(i-1);
        }
        else
        {
            chave = base3 + to_string(i-2);
        }
        
        int qtdAntes = tabela->getQuantity();
        
        removeu = tabela->remove(chave);
        
        
        if(!removeu)
        {
            cout << "\t*ERRO - Teste Remover_Sucessivas: Não removeu corretamente item com chave igual a : " << chave << "." << endl;
            removeu = false;
            break;
        }
        
        int qtdDepois = tabela->getQuantity();
        
        if( qtdAntes - 1 != qtdDepois )
        {
            cout << "\t*ERRO - Teste Remover_Sucessivas: Não decrementou corretamente a quantidade de itens durante a remoção." << endl;
            removeu = false;
            break;
        }
    }
    
    delete tabela;
    
    return removeu;
}

bool testar_Remover_Colisao()
{
    HashTable* tabela = new HashTable(17);
    string c1 = "abba";
    string i1 = "conteudo1";
    
    string c2 = "bbaa";
    string i2 = "conteudo2";
    
    string c3 = "baba";
    string i3 = "conteudo3";
    
    tabela->put(c1, i1);
    tabela->put(c2, i2);
    tabela->put(c3, i3);
    
    tabela->remove(c2);
    
    bool achou1 = false, achou3 = false;
    for(int x = 0; x < tabela->getSize(); x++)
    {
        HashEntry<string, string>* c = tabela->data[x];
        
        if( c != nullptr && c != ENTRY_DELETED && c->getKey() == c1  )
        {
            achou1 = true;
        }
        
        if( c != nullptr && c != ENTRY_DELETED && c->getKey() == c3  )
        {
            achou3 = true;
        }
    }
    
    bool resultado = true;
    if( (achou1 && !achou3)||(!achou1 && achou3) )
    {
        cout << "\t*ERRO - Teste Remover_Colisao: Três chaves que colidem foram inseridas e uma foi removida, mas foi removida a chave errada. Rever tratamento de colisão." << endl;
        resultado = false;
    }
    
    delete tabela;
    
    return resultado;
}

bool testar_Remover()
{
    cout << "\nINÍCIO: Testes Remover" << endl;
    
    bool resultado = true;
    
    cout << "\tTeste Remover - Caso Normal" << endl;
    resultado = testar_Remover_CasoNormal();
    
    if(resultado)
    {
        cout << "\tTeste Remover - Sucessivas" << endl;
        resultado = testar_Remover_Sucessivas();
    }
    if(resultado)
    {
        cout << "\tTeste Remover - Colisão" << endl;
        resultado = testar_Remover_Colisao();
    }
    
    cout << "FIM: Testes Remover" << endl;
    
    return resultado;
}

bool testar_Tudo()
{
    cout << "\nINÍCIO: Testes Tudo" << endl;
    
    bool resultado = true;
    
    HashTable* tabela = new HashTable(177);
    
    string base1 = "chave-";
    string base2 = "cheva-";
    string base3 = "hceva-";
    
    for(int i = 0; i < 50; i++)
    {
        string conteudo = "conteudo" + to_string(i);

        
        string chave;
        
        if( i%3==0 )
        {
            chave = base1 + to_string(i);
        }
        else if( i%3==1 )
        {
            chave = base2 + to_string(i-1);
        }
        else
        {
            chave = base3 + to_string(i-2);
        }
        
        if( !tabela->put(chave, conteudo) )
        {
            cout << "\t*ERRO - Teste Tudo: Não inseriu item corretamente. Chave:Valor inseridos quando erro foi detectado: " << chave << ":" << conteudo << endl;
            resultado = false;
            break;
        }
        
        
        if( tabela->get(chave) != conteudo )
        {
            cout << "\t*ERRO - Teste Tudo: Não buscou item corretamente." << endl;
            resultado = false;
            break;
        }
    }
    
    if( resultado )
    {
        for(int i = 0; i < 50; i++)
        {
            string novoConteudo = "NovoConteudo" + to_string(i);
            
            string chave;
            
            if( i%3==0 )
            {
                chave = base1 + to_string(i);
            }
            else if( i%3==1 )
            {
                chave = base2 + to_string(i-1);
            }
            else
            {
                chave = base3 + to_string(i-2);
            }
            
            tabela->put(chave, novoConteudo);
            
            string retornado = tabela->get(chave);
            
            if( retornado != novoConteudo )
            {
                cout << "\t*ERRO - Teste Tudo: Não atualizou item corretamente." << endl;
                resultado = false;
                break;
            }
        }
    }
    
    if(resultado)
    {
        for(int i = 0; i < 50; i++)
        {
            string chave;
            
            if( i%3==0 )
            {
                chave = base1 + to_string(i);
            }
            else if( i%3==1 )
            {
                chave = base2 + to_string(i-1);
            }
            else
            {
                chave = base3 + to_string(i-2);
            }
            
            
            if(!tabela->remove(chave))
            {
                cout << "\t*ERRO - Teste Tudo: Não removeu item corretamente." << endl;
                
                resultado = false;
                    
                tabela->print();
                break;
            }
        }
    }
    
    cout << "FIM: Testes Tudo\n" << endl;
    
    delete tabela;
    
    return resultado;
}

bool testar_Inserir_Redimensionamento()
{
    cout << "INÍCIO: Testes Inserir-Redimensionamento" << endl;
    
    int tamanho = 117;
    
    HashTable* tabela = new HashTable(tamanho);
    
    vector<string> itensInseridos;
    vector<string> chavesInseridas;
    
    int i = 0;
    float alpha;
    do
    {
        string iStr = to_string(i);
        string chave = "chave-" + iStr;
        string valor = "valor-" + iStr;
        
        chavesInseridas.push_back(chave);
        itensInseridos.push_back(valor);
        
        tabela->put(chave, valor);

        i++;
        
        alpha = (float) (tabela->getQuantity()+1) / tabela->getSize();
    } while( alpha <= 0.5f );
    
    
    // Quando chegar aqui, está exatamente antes de fazer o redimensionamento
    int tamanhoAntes = tabela->getSize();
    
    string chaveNova = "ChaveNova";
    chavesInseridas.push_back(chaveNova);
    
    string valorNovo = "ConteudoNovo";
    itensInseridos.push_back(valorNovo);
    
    tabela->put( chaveNova, valorNovo);
    
    int tamanhoDepois = tabela->getSize();
    
    if( 1 + 2*tamanhoAntes != tamanhoDepois )
    {
        cout << "\t*ERRO - Teste Inserir_Redimensionamento: Tabela não foi redimensionada corretamente. Tamanho antes de inserir = " << tamanhoAntes << ". Tamnho depois de inserir = " << tamanhoDepois << ". Esperado após inserir era: " << 1+2*tamanhoAntes << endl;
        
        return false;
    }
    
    // Verifica se todos elementos que estavam antes do redimensionamento continuam na tabela
    for(string chave : chavesInseridas)
    {
        bool achou = false;
        for(int i = 0; i < tabela->getSize(); i++)
        {
            HashEntry<string, string>* entry = tabela->data[i];
            
            if(entry != nullptr && entry != ENTRY_DELETED && entry->getKey() == chave)
            {
                achou = true;
                break;
            }
        }
        if(!achou)
        {
            cout << "\t*ERRO - Teste Inserir_Redimensionamento: O item com chave igual a "<< chave << " estava na tabela antes do redimensionamento, mas não se encontra após." << endl;
            delete tabela;
            return false;
        }
    }
    
    // Verifica se todos elementos que estão na tabela após o redimensionamento já estavam na tabela
    for(int i = 0; i < tabela->getSize(); i++)
    {
        HashEntry<string, string>* entry = tabela->data[i];
        if(entry != nullptr && entry != ENTRY_DELETED)
        {
            bool achou = false;
            for(string chave : chavesInseridas)
            {
                if( entry->getKey() == chave )
                {
                    achou = true;
                    break;
                }
            }
            if(!achou)
            {
                cout << "\t*ERRO - Teste Inserir_Redimensionamento: Item com chave igual a "<< entry->getKey() << " está na tabela após o redimensionamento, mas não se encontrava antes." << endl;
                delete tabela;
                return false;
            }
        }
    }
    
    delete tabela;
    
    cout << "FIM: Testes Inserir-Redimensionamento\n" << endl;
    
    return true;
}

bool testar_Remover_Redimensionamento()
{
    cout << "INÍCIO: Testes Remover-Redimensionamento" << endl;
    
    bool removeu = true;
    
    int tamanho = 177;
    
    HashTable* tabela = new HashTable(tamanho);
    
    // Essas quantidades evitam que a tabela sofra um redimensionamento
    int qtdInserido = tabela->getSize()/2;
    int qtdRemovido = qtdInserido - 1 - tabela->getSize()/4;
    
    // Inicialização da tabela
    for(int i = 0; i < qtdInserido; i++)
    {
        string iStr = to_string(i);
        string chave = "chave-" + iStr;
        string valor = "valor-" + iStr;
        
        tabela->put(chave, valor);
    }
    
    for(int i = 0; i < qtdRemovido; i++)
    {
        string iStr = to_string(i);
        string chave = "chave-" + iStr;
        
        removeu = tabela->remove(chave);
        
        if(!removeu)
        {
            cout << "\t*ERRO - Teste Remover_Redimensionamento: Não removeu corretamente item com chave igual a: " << chave << endl;
            removeu = false;
            break;
        }
    }
    
    // Ao chegar aqui a Tabela está prestes a sofrer uma redução no seu tamanho, basta mais uma remoção
    // Escolhe uma chave qualquer para remover item
    string chave;
    
    for(int i = 0; i < tabela->getSize(); i++)
    {
        HashEntry<string, string>* entry = tabela->data[i];
        if(entry != nullptr && entry != ENTRY_DELETED)
        {
            chave = entry->getKey();
            break;
        }
    }
    
    int tamanhoAntes = tabela->getSize();
    
    removeu = tabela->remove(chave);
    
    int tamanhoDepois = tabela->getSize();
    
    if( 1+tamanhoAntes/2 != tamanhoDepois )
    {
        cout << "\t*ERRO - Teste Remover_Redimensionamento: Tabela não foi redimensionada corretamente. Tamanho antes de remover = " << tamanhoAntes << ". Tamanho depois de remover = " << tamanhoDepois << ". Esperado após inserir era: " << 1+tamanho/2 << endl;
        removeu = false;
    }
    
    delete tabela;
    
    cout << "FIM: Testes Remover-Redimensionamento\n" << endl;
    
    return removeu;
}
