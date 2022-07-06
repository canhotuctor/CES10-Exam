Nome do grupo: Only Survivors
Nome dos integrantes:   
		Felipe José Batista Farias
		Mario Célio da Silva Bezerra
		Leonardo Peres Dias

Instruções para rodar e jogar:

O nome do RPG: "Only Survivors"

História do RPG:

Após uma terrível praga não explicável arrasar a vida na terra, pequenos grupos de seres humanos passaram a viver totalmente isolados por milhares de anos.
40 mil anos depois, os grupos sobrevientes observaram que algumas pessoas nascidas na vila apresentavam características estranhas às convencionais e, com medo delas causarem mal à vila, começaram a expulsá-las. 
Assim começa a saga dos "Only Survivors", que se aliam e guerrilham por sua sobrevivência nessa imensidão do mundo devastado, apenas por serem diferentes.

Intrunções rodar e jogar:

Rode: g++ -std=c++17 -Wall -Wextra -Werror -pedantic main.cpp defs.cpp -o main

Copie o código em um compilado e rode o programa.

Jogar: ./main [filename1] [filename2] ...

-----

Após rodar o jogo, será aberta uma tela inicial. Se arquivos válidos foram colocados na linha de comando para execução, será dada uma opção de se carregar um desses arquivos. Entretanto, sendo ou não carregado um arquivo na linha de comando, também será dada a opção de começar um novo jogo, meio de inicialização(descrita abaixo) pelo qual será perguntado o número de guerreiros em cada time, bem como com quais guerreiros quer jogar.

Descrição da inicialização:

- Escolha se irá batalhar com 1, 2 ou até 5 personagens através do input de comando:
1 para (1x1), 2 para (2x2)...

- Após o comando, escolha os personagens que serão aliados e estarão sobre seu comando.
Através do input 1 para guerreiro, 2 para para mago, 3 para ladino, 4 para curandeiro, 5 para arqueiro, 6 para bardo.
A ordem dos persogens depende da ordem de escolha do números, sendo os 1º, 2º e nº números de input suas posições respectivamente...
Para (1x1), exemplo de input: 5
Para (2x2), exemplo de input: 1 4
Para (5x5), exemplo de input: 1 3 6 4 2

Com a escolha dos personagens aliados, o computador escolherá seus oponentes de maneira aleatória e começará a batalha.

Lógica geral:

A batalha segue um sistema sem turnos, baseado no Active-Time Battle system do jogo Final Fantasy 3
A cada rodada, o jogador com o menor 'temporizador' é escolhido, e sua contagem é subtraída de todos os jogadores presentes no jogo;
Ele então, realiza sua ação, a qual, dependendo da dificuldade soma diferentes contagens para seu contador(ex: uma ação difícil como um ataque especial, ou poderoso, fazem com que o jogador tenha de esperar um grande tempo para jogar de novo)

Caso seja o turno do jogador, serão apresentadas de 5 a 6 opções de ação para sua escolha:

1 para realizar o ataque padrão
2 para realizar a ação especial inerente a cada personagem
3 para realizar o ataque poderoso, que dá o triplo do dano padrão, mas demora mais pra carregar
4 para realizar a cura básica, à qual apenas alguns personagens tem acesso
9 para salvar o jogo e sair
0 para sair do jogo sem salvar

Caso seja o turno do inimigo(computador), ele tomará suas ações com base num sistema de probabilidades baseadas nas suas próprias condições e nas do personagem do usuário com menor vida.

Seguindo esse sistema, você lutará até todos os inimigos serem derrotados ou todos os seus aliados serem mortos.

Boa sorte!
