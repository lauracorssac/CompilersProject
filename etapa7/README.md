# Etapa 7

## Otimizações Implementadas

### 1. Código após return 

Quando há comandos após um comando de return em uma função, esses são ignorados. Isso foi implementado impedindo com que os comandos fossem introduzidos na AST, então a diferença de tamanho no código final otimizado já pode ser percebida no código intermediário. Funções que possuem um comando de if com else, ambos com algum retorno em seus blocos, ou blocos de while ou for contendo retorno em seus blocos têm todo seu código que procede o comando if-else ignorado. Entretanto, se há um if sem else ou um if com else, mas algum desses blocos sem um retorno, o resto do corpo da função, que procede o comando de if ou if-else, conforme o caso, permanece. A otimização também é feita dentro dos blocos desses comandos if, if-else, while e for. Dessa forma, quando há, por exemplo, apenas dois comandos dentro de um while, sendo o primeiro deles um retorno, ignoramos o segundo.

Os arquivos de entrada que usamos para testar o programa contêm em sua primeira linha um comentário com a saída esperada e estão localizados na pasta `teste`. Nos seguintes, a diferença no tamanho de código pode ser observada por conta dessa implementação.

- return1.txt
- return2.txt
- return3.txt
- return4.txt
- returnWhile.txt
- returnFor.txt
- returnForIf.txt
- returnForIfElse.txt

### 2. Funções não chamadas

Quando há alguma função não chamada, todo o código intermediário referente ao seu corpo não é traduzido a assembly.

Os casos de teste que ilustram essa otimização estão também na pasta `teste` . Tais são eles:

- function1.txt
- function2.txt

