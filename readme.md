<h1>Projeto Analisador Semântico (Compiladores)</h1>
<hr/>
<p>Objetivo: Criar um analisador semântico para permitir a produção de um pseudo-código de máquina já compilado.</p>

 <h2>Exemplo de Entrada:</h2>

```
    Digite a entrada: 5*(3+2*(4-5)+3)-1
```

<h2>Saída Correspondente:</h2>

```
    Saida:

    LDA 4
    SUB 5
    STA T1

    LDA 2
    MUL T1
    STA T2

    LDA 3
    ADA T2
    STA T3

    LDA T3
    ADA 3
    STA T4

    LDA 5
    MUL T4
    STA T5

    LDA T5
    SUB 1
    STA T6
```

<br/>
<h3>Colaboradores:</h3>
<p>
    <ul>
        <li>João Souza (<a href=http://github.com/Jvictor97>@Jvictor97</a>)</li>
        <li>Marcus More (<a href=http://github.com/MarcusMore>@MarcusMore</a>)</li>
    </ul>
</p>
