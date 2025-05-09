#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Função para calcular o MDC (Algoritmo de Euclides)
long long int gcd(long long int a, long long int b) {
    long long int temp;
    // Assegurando que a seja sempre maior que b inicialmente
    if (a < b) {
        temp = a;
        a = b;
        b = temp;
    }
    
    printf("Calculando MDC(%lld, %lld) usando o Algoritmo de Euclides:\n", a, b);
    
    while (b != 0) {
        printf("  MDC(%lld, %lld): %lld = %lld * %lld + %lld\n", 
               a, b, a, a/b, b, a%b);
        temp = b;
        b = a % b;
        a = temp;
    }
    
    printf("  O MDC é %lld\n", a);
    return a;
}

// Função para verificar se um número é primo
bool is_prime(long long int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    
    printf("Verificando se %lld é primo:\n", n);
    printf("  Testando divisibilidade por números da forma 6k±1 até √%lld\n", n);
    
    for (long long int i = 5; i * i <= n; i += 6) {
        if (n % i == 0) {
            printf("  %lld é divisível por %lld, portanto não é primo\n", n, i);
            return false;
        }
        if (n % (i + 2) == 0) {
            printf("  %lld é divisível por %lld, portanto não é primo\n", n, i+2);
            return false;
        }
    }
    
    printf("  %lld é primo pois não é divisível por nenhum número até sua raiz quadrada\n", n);
    return true;
}

// Função para calcular o inverso modular usando o algoritmo estendido de Euclides
long long int mod_inverse(long long int a, long long int m) {
    long long int m0 = m, t, q;
    long long int x0 = 0, x1 = 1;
    
    printf("\n=== CÁLCULO DO INVERSO MODULAR DE %lld EM Z%lld ===\n", a, m);
    printf("Utilizando o algoritmo estendido de Euclides:\n");
    
    if (m == 1) {
        printf("O inverso é 1 porque estamos em Z1\n");
        return 0;
    }
    
    // Verificar se a e m são coprimos
    if (gcd(a, m) != 1) {
        printf("O inverso não existe porque %lld e %lld não são coprimos (MDC = %lld != 1)\n", 
               a, m, gcd(a, m));
        return -1;
    }
    
    printf("Aplicando o algoritmo estendido de Euclides para encontrar x e y tais que: %lld·x + %lld·y = 1\n", a, m);
    printf("Inicializando: x0 = 0, x1 = 1\n");
    
    int step = 1;
    printf("\nIterações:\n");
    
    // As variáveis originais para exibição
    long long int a_orig = a;
    long long int m_orig = m;
    
    while (a > 1) {
        // q é o quociente
        q = a / m;
        t = m;
        
        // m é o resto agora, processo igual ao Euclides
        m = a % m;
        a = t;
        
        // Atualizamos x
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
        
        printf("Passo %d:\n", step);
        printf("  Quociente q = %lld\n", q);
        printf("  a = %lld, m = %lld\n", a, m);
        printf("  x0 = %lld, x1 = %lld\n", x0, x1);
        step++;
    }
    
    printf("\nConclusão:\n");
    printf("  O inverso x1 = %lld\n", x1);
    
    // Garantimos que x1 seja positivo
    if (x1 < 0) {
        printf("  Como x1 é negativo (%lld), adicionamos m0 (%lld) para torná-lo positivo\n", x1, m0);
        x1 += m0;
        printf("  Novo valor de x1 = %lld\n", x1);
    }
    
    printf("Verificação: (%lld · %lld) mod %lld = %lld\n", a_orig, x1, m0, (a_orig * x1) % m0);
    printf("Inverso de %lld em Z%lld = %lld\n", a_orig, m0, x1);
    return x1;
}

// Função para calcular a função totiente de Euler (phi)
long long int euler_phi(long long int n) {
    long long int result = n;  // Inicializa o resultado como n
    long long int original_n = n;
    
    printf("\n=== CÁLCULO DA FUNÇÃO TOTIENTE DE EULER φ(%lld) ===\n", n);
    printf("Utilizando a fórmula: φ(n) = n · ∏(p|n) (1 - 1/p), onde p são os fatores primos de n\n");
    printf("Inicializando φ(%lld) = %lld\n", n, result);
    printf("Buscando os fatores primos de %lld:\n", n);
    
    // Conta e remove todos os fatores 2
    if (n % 2 == 0) {
        printf("Fator primo encontrado: 2\n");
        printf("Aplicando a fórmula: φ(%lld) = %lld · (1 - 1/2) = %lld · (1/2) = %lld\n", 
               original_n, result, result, result/2);
        result -= result / 2;  // Aplica a fórmula φ(n) = n * (1 - 1/p)
        printf("φ(%lld) atualizado = %lld\n", original_n, result);
        
        printf("Removendo todos os fatores 2 de %lld:\n", n);
        while (n % 2 == 0) {
            n /= 2;
            printf("  n = %lld\n", n);
        }
    }
    
    // n deve ser ímpar neste ponto
    // Agora procuramos por todos os números ímpares restantes
    for (long long int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            printf("Fator primo encontrado: %lld\n", i);
            printf("Aplicando a fórmula: φ(%lld) = %lld · (1 - 1/%lld) = %lld · (%lld/%lld) = %lld\n", 
                   original_n, result, i, result, i-1, i, result - result/i);
            result -= result / i;  // Aplica a fórmula φ(n) = n * (1 - 1/p)
            printf("φ(%lld) atualizado = %lld\n", original_n, result);
            
            printf("Removendo todos os fatores %lld de %lld:\n", i, n);
            while (n % i == 0) {
                n /= i;
                printf("  n = %lld\n", n);
            }
        }
    }
    
    // Se n > 1, então n é um número primo
    if (n > 1) {
        printf("Fator primo encontrado: %lld\n", n);
        printf("Aplicando a fórmula: φ(%lld) = %lld · (1 - 1/%lld) = %lld · (%lld/%lld) = %lld\n", 
               original_n, result, n, result, n-1, n, result - result/n);
        result -= result / n;  // Aplica a fórmula φ(n) = n * (1 - 1/p)
        printf("φ(%lld) atualizado = %lld\n", original_n, result);
    }
    
    printf("\nResultado final: φ(%lld) = %lld\n", original_n, result);
    return result;
}

// Função para calcular a exponenciação modular (a^x mod n1) com explicação detalhada
long long int modular_exponentiation(long long int a, long long int x, long long int n1) {
    long long int result = 1;
    long long int original_a = a;
    long long int original_x = x;
    
    printf("\n=== CÁLCULO DE EXPONENCIAÇÃO MODULAR ===\n");
    printf("Vamos calcular %lld^%lld mod %lld\n\n", a, x, n1);
    
    printf("Passos iniciais:\n");
    printf("- Começamos com resultado = 1\n");
    
    a = a % n1;
    printf("- Reduzimos a base pelo módulo: %lld mod %lld = %lld\n\n", original_a, n1, a);
    
    if (x == 0) {
        printf("O expoente é 0, então o resultado é 1.\n");
        return 1;
    }
    
    if (x < 0) {
        printf("AVISO: O expoente é negativo (%lld). Para calcular corretamente, precisaríamos do inverso modular de %lld em Z%lld.\n", x, a, n1);
        printf("No entanto, este programa está configurado para trabalhar com expoentes positivos. Por favor, insira um expoente positivo.\n");
        return -1;
    }
    
    printf("Método da exponenciação binária (rápida):\n");
    printf("Representação binária de %lld: ", x);
    
    // Mostrar o expoente em binário
    long long int temp_x = x;
    long long int bin_pow = 1;
    while (bin_pow <= temp_x) bin_pow *= 2;
    bin_pow /= 2;
    
    while (bin_pow > 0) {
        if (temp_x >= bin_pow) {
            printf("1");
            temp_x -= bin_pow;
        } else {
            printf("0");
        }
        bin_pow /= 2;
    }
    printf("\n\n");
    
    int step = 1;
    
    while (x > 0) {
        printf("Passo %d:\n", step);
        printf("  - Expoente atual (x) = %lld\n", x);
        
        if (x % 2 == 1) {
            long long int old_result = result;
            result = (result * a) % n1;
            printf("  - Expoente é ímpar, multiplicamos o resultado pela base: (%lld * %lld) mod %lld = %lld\n", 
                   old_result, a, n1, result);
        } else {
            printf("  - Expoente é par, não multiplicamos o resultado nesta etapa\n");
        }
        
        x = x >> 1; // Equivalente a dividir por 2
        printf("  - Dividimos o expoente por 2: x = %lld\n", x);
        
        if (x > 0) {
            long long int old_a = a;
            a = (a * a) % n1;
            printf("  - Elevamos a base ao quadrado: (%lld * %lld) mod %lld = %lld\n\n", 
                  old_a, old_a, n1, a);
        }
        
        step++;
    }
    
    printf("\nResultado final: %lld^%lld mod %lld = %lld\n", original_a, original_x, n1, result);
    return result;
}

int main() {
    long long int H, G, n, a, x, n1, resultado;
    
    printf("=====================================================================\n");
    printf("=== CÁLCULO DE EXPONENCIAÇÃO MODULAR USANDO TEORIA DOS NÚMEROS ===\n");
    printf("=====================================================================\n\n");
    
    printf("Este programa calcula a^x mod n1 de forma eficiente usando:\n");
    printf("- Pequeno Teorema de Fermat\n");
    printf("- Teorema de Euler\n");
    printf("- Exponenciação binária\n");
    printf("- Algoritmo de Euclides estendido\n\n");
    
    printf("=== DADOS DE ENTRADA ===\n");
    printf("Por favor, insira os valores para os cálculos:\n\n");
    
    // Validando entradas para H, G e n
    do {
        printf("Digite três números inteiros positivos H, G e n (separados por espaço): ");
        if (scanf("%lld %lld %lld", &H, &G, &n) != 3 || H <= 0 || G <= 0 || n <= 0) {
            printf("Erro: Entre apenas com números inteiros positivos!\n");
            // Limpar o buffer de entrada
            while (getchar() != '\n');
        } else {
            break;
        }
    } while (1);
    
    // Validando entrada para x
    do {
        printf("Digite o expoente x (inteiro positivo): ");
        if (scanf("%lld", &x) != 1 || x < 0) { // Permitindo x = 0
            printf("Erro: Entre apenas com um número inteiro não-negativo!\n");
            // Limpar o buffer de entrada
            while (getchar() != '\n');
        } else {
            break;
        }
    } while (1);
    
    // Validando entrada para n1
    do {
        printf("Digite o módulo n1 (inteiro positivo): ");
        if (scanf("%lld", &n1) != 1 || n1 <= 0) {
            printf("Erro: Entre apenas com um número inteiro positivo!\n");
            // Limpar o buffer de entrada
            while (getchar() != '\n');
        } else {
            break;
        }
    } while (1);
    
    printf("\n=== ETAPA 1: VERIFICAÇÃO DE PRIMALIDADE ENTRE G E n ===\n");
    printf("Precisamos verificar se G e n são primos entre si (coprimos).\n");
    printf("Dois números são coprimos se seu MDC (máximo divisor comum) é 1.\n\n");
    
    long long int mdc_G_n = gcd(G, n);
    
    if (mdc_G_n != 1) {
        printf("\nCONCLUSÃO DA ETAPA 1:\n");
        printf("G (%lld) e n (%lld) não são primos entre si (MDC = %lld).\n", G, n, mdc_G_n);
        printf("Não é possível continuar, pois G não tem inverso em Zn.\n");
        printf("Justificativa: Para a divisão H/G ser possível em Zn, G deve ter um inverso em Zn.\n");
        printf("                G tem inverso em Zn se e somente se MDC(G,n) = 1.\n");
        return 0;
    } else {
        printf("\nCONCLUSÃO DA ETAPA 1:\n");
        printf("G (%lld) e n (%lld) são primos entre si (MDC = 1).\n", G, n);
        printf("É possível continuar com o cálculo porque G tem inverso em Zn.\n");
    }
    
    printf("\n=== ETAPA 2: CALCULANDO O INVERSO DE G EM Zn ===\n");
    printf("Para realizar a divisão H/G em Zn, precisamos encontrar o inverso multiplicativo de G em Zn.\n");
    printf("Isto é, encontrar G^(-1) tal que G * G^(-1) ≡ 1 (mod n).\n\n");
    
    long long int G_inv = mod_inverse(G, n);
    
    if (G_inv == -1) {
        printf("\nCONCLUSÃO DA ETAPA 2:\n");
        printf("Não foi possível calcular o inverso de G em Zn. O programa será encerrado.\n");
        return 0;
    } else {
        printf("\nCONCLUSÃO DA ETAPA 2:\n");
        printf("O inverso de G (%lld) em Z%lld é %lld.\n", G, n, G_inv);
        printf("Verificação: (%lld * %lld) mod %lld = %lld\n", G, G_inv, n, (G * G_inv) % n);
    }
    
    printf("\n=== ETAPA 3: CÁLCULO DA BASE 'a' DIVIDINDO H POR G EM Zn ===\n");
    printf("Em aritmética modular, a divisão H/G é equivalente à multiplicação H * G^(-1).\n");
    printf("Portanto, calculamos a = (H * G^(-1)) mod n\n\n");
    
    // a = (H * G_inv) % n
    a = (H * G_inv) % n;
    if (a < 0) a += n;  // Garantir que a seja positivo
    
    printf("Cálculo: a = (H * G^(-1)) mod n\n");
    printf("a = (%lld * %lld) mod %lld\n", H, G_inv, n);
    printf("a = %lld mod %lld\n", H * G_inv, n);
    printf("a = %lld\n", a);
    
    printf("\n=== ETAPA 4: VERIFICANDO SE a E n1 SÃO COPRIMOS ===\n");
    printf("Verificamos se a base 'a' (%lld) e o módulo n1 (%lld) são coprimos.\n", a, n1);
    printf("Isso afeta a aplicação do Teorema de Euler na próxima etapa.\n\n");
    
    long long int mdc_a_n1 = gcd(a, n1);
    
    if (mdc_a_n1 != 1) {
        printf("\nCONCLUSÃO DA ETAPA 4:\n");
        printf("a (%lld) e n1 (%lld) não são coprimos (MDC = %lld != 1).\n", a, n1, mdc_a_n1);
        printf("AVISO: Isso limita a aplicação do Teorema de Euler.\n");
        printf("       Prosseguiremos com o cálculo, mas os resultados podem não ser válidos\n");
        printf("       para todos os expoentes.\n");
    } else {
        printf("\nCONCLUSÃO DA ETAPA 4:\n");
        printf("a (%lld) e n1 (%lld) são coprimos (MDC = 1).\n", a, n1);
        printf("Isso é ideal para a aplicação do Teorema de Euler ou Pequeno Teorema de Fermat.\n");
    }
    
    printf("\n=== ETAPA 5: VERIFICANDO SE n1 É PRIMO ===\n");
    printf("Esta verificação determina qual teorema usar: Pequeno Teorema de Fermat ou Teorema de Euler.\n\n");
    
    bool n1_is_prime = is_prime(n1);
    
    long long int x1;
    
    if (n1_is_prime) {
        printf("\nCONCLUSÃO DA ETAPA 5:\n");
        printf("n1 (%lld) é um número primo.\n", n1);
        printf("Portanto, utilizaremos o Pequeno Teorema de Fermat.\n");
        
        printf("\n=== ETAPA 6: APLICANDO O PEQUENO TEOREMA DE FERMAT ===\n");
        printf("O Pequeno Teorema de Fermat afirma que:\n");
        printf("Se p é primo e 'a' não é divisível por p, então a^(p-1) ≡ 1 (mod p)\n");
        printf("Isso nos permite simplificar o cálculo de potências grandes.\n\n");
        
        x1 = n1 - 1;
        printf("Como n1 é primo, calculamos x1 = n1 - 1 = %lld - 1 = %lld\n", n1, x1);
        printf("Pelo Pequeno Teorema de Fermat: a^%lld ≡ 1 (mod %lld)\n", x1, n1);
    } else {
        printf("\nCONCLUSÃO DA ETAPA 5:\n");
        printf("n1 (%lld) não é um número primo.\n", n1);
        printf("Portanto, utilizaremos o Teorema de Euler.\n");
        
        printf("\n=== ETAPA 7: APLICANDO O TEOREMA DE EULER ===\n");
        printf("O Teorema de Euler afirma que:\n");
        printf("Se a e n são coprimos, então a^φ(n) ≡ 1 (mod n)\n");
        printf("onde φ(n) é a função totiente de Euler, que conta quantos inteiros\n");
        printf("entre 1 e n são coprimos com n.\n\n");
        
        x1 = euler_phi(n1);
        printf("Pelo Teorema de Euler: a^%lld ≡ 1 (mod %lld)\n", x1, n1);
    }
    
    printf("\n=== ETAPA 8: DECOMPOSIÇÃO DO EXPOENTE x PELO TEOREMA DA DIVISÃO ===\n");
    printf("Pelo algoritmo da divisão, podemos escrever x = x1 * q + r, onde 0 ≤ r < x1\n");
    printf("Isso nos permite simplificar o cálculo de a^x mod n1\n\n");
    
    long long int q = x / x1;
    long long int r = x % x1;
    
    printf("Dividindo x por x1: %lld ÷ %lld\n", x, x1);
    printf("Quociente q = %lld\n", q);
    printf("Resto r = %lld\n", r);
    printf("Verificação: x = x1 * q + r\n");
    printf("%lld = %lld * %lld + %lld = %lld + %lld = %lld ✓\n", x, x1, q, r, x1*q, r, x1*q+r);
    
    printf("\n=== ETAPA 9: REESCREVENDO A EXPRESSÃO a^x mod n1 ===\n");
    printf("Com base na decomposição do expoente, podemos reescrever:\n");
    printf("a^x mod n1 = a^(x1*q+r) mod n1\n");
    printf("            = (a^(x1*q) * a^r) mod n1\n");
    printf("            = ((a^x1)^q * a^r) mod n1\n\n");
    
    printf("Pelo teorema aplicado (");
    if (n1_is_prime) {
        printf("Pequeno Teorema de Fermat");
    } else {
        printf("Teorema de Euler");
    }
    printf("), sabemos que:\n");
    printf("a^x1 ≡ 1 (mod n1) se a e n1 são coprimos\n\n");
    
    if (mdc_a_n1 != 1) {
        printf("AVISO: Como a e n1 não são coprimos (MDC = %lld), essa simplificação pode não se aplicar\n", mdc_a_n1);
        printf("       diretamente. Prosseguiremos calculando os valores explicitamente.\n\n");
    }
    
    printf("\n=== ETAPA 10: CALCULANDO VALORES INTERMEDIÁRIOS ===\n");
    printf("Vamos calcular os valores intermediários sequencialmente.\n");
    
    printf("Calculando a^x1 mod n1:\n");
    long long int x2 = modular_exponentiation(a, x1, n1);
    
    if (x2 == 1 && mdc_a_n1 == 1) {
        printf("\nObservação: a^x1 mod n1 = 1, confirmando o ");
        if (n1_is_prime) {
            printf("Pequeno Teorema de Fermat.\n");
        } else {
            printf("Teorema de Euler.\n");
        }
    } else if (x2 != 1 && mdc_a_n1 == 1) {
        printf("\nAVISO: Esperávamos a^x1 mod n1 = 1 pelo ");
        if (n1_is_prime) {
            printf("Pequeno Teorema de Fermat, mas obtivemos %lld.\n", x2);
        } else {
            printf("Teorema de Euler, mas obtivemos %lld.\n", x2);
        }
        printf("       Isso indica algum problema no cálculo ou nos parâmetros.\n");
    }
    
    printf("\nCalculando x2^q mod n1:\n");
    long long int x2_q = modular_exponentiation(x2, q, n1);
    
    printf("\nCalculando a^r mod n1:\n");
    long long int a_r = modular_exponentiation(a, r, n1);
    
    printf("\n=== ETAPA 11: COMBINANDO OS RESULTADOS FINAIS ===\n");
    printf("Agora vamos combinar os resultados intermediários para obter a^x mod n1.\n\n");
    
    resultado = (x2_q * a_r) % n1;
    if (resultado < 0) resultado += n1;  // Garantir que o resultado seja positivo
    
    printf("Combinação final: ((x2^q) * (a^r)) mod n1\n");
    printf("                 = ((%lld^%lld) * (%lld^%lld)) mod %lld\n", a, x1, a, r, n1);
    printf("                 = ((%lld^%lld) * %lld) mod %lld\n", x2, q, a_r, n1);
    printf("                 = (%lld * %lld) mod %lld\n", x2_q, a_r, n1);
    printf("                 = %lld mod %lld\n", x2_q * a_r, n1);
    printf("                 = %lld\n", resultado);
    
    // Verificação direta para comparação
    printf("\n=== VERIFICAÇÃO DO RESULTADO ===\n");
    printf("Vamos calcular a^x mod n1 diretamente para verificar:\n");
    long long int verificacao = modular_exponentiation(a, x, n1);
    
    printf("\n=== RESUMO FINAL ===\n");
    printf("Valores de entrada:\n");
    printf("- H = %lld, G = %lld, n = %lld\n", H, G, n);
    printf("- Base calculada a = %lld\n", a);
    printf("- Expoente x = %lld\n", x);
    printf("- Módulo n1 = %lld\n", n1);
    printf("\nResultados dos cálculos intermediários:\n");
    printf("- x1 (expoente base) = %lld\n", x1);
    printf("- q (quociente de x/x1) = %lld\n", q);
    printf("- r (resto de x/x1) = %lld\n", r);
    printf("- a^x1 mod n1 = %lld\n", x2);
    printf("- (a^x1)^q mod n1 = %lld\n", x2_q);
    printf("- a^r mod n1 = %lld\n", a_r);
    printf("\nResultado final usando o método otimizado:\n");
    printf("a^x mod n1 = %lld\n", resultado);
    printf("\nResultado da verificação direta:\n");
    printf("a^x mod n1 = %lld\n", verificacao);
    
    if (resultado == verificacao) {
        printf("\nO resultado obtido está correto! ✓\n");
    } else {
        printf("\nAVISO: Os resultados não coincidem. Verifique os cálculos.\n");
    }
    
    return 0;
}