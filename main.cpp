//
//  main.cpp
//
//  Created by Eiji Adachi Medeiros Barbosa
//

#include "TestTable.h"
#include <iostream>
#include <cassert>

int main(int argc, const char * argv[]) {
    assert( testar_Criar() );
    assert( testar_Inserir() );
    assert( testar_Remover() );
    assert( testar_Buscar() );
    assert( testar_Tudo() );
    
    std::cout << "\tTodos os testes rodaram sem falhas.\n";
    
    return 0;
}

