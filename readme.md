## Relatório Ninja Survival

**Alunos**: Guilherme d'Ávila Pinheiro, Marcos Luiz Kurth Reckers.

## Contribuições dos Membros

- De forma geral ambos os integrantes participaram de forma ativa em todas as partes do desenvolvimento, atuando de forma complementar em todas as etapas.

## Uso de Ferramentas de IA

A dupla fez uso do ChatGPT para auxiliar na implementação de algumas funcionalidades específicas, como a detecção de colisões e a configuração inicial do projeto. A ferramenta foi útil para esclarecer dúvidas pontuais e fornecer exemplos de código, mas em alguns casos, as soluções sugeridas precisaram ser adaptadas para se adequarem ao contexto específico do projeto.

### Análise Crítica

A ferramenta foi útil principalmente para:

- Fornecer exemplos de código para funcionalidades específicas.
- Ajudar na depuração de erros de compilação.

No entanto, a ferramenta não foi tão eficaz em:

- Compreender o contexto completo do projeto.
- Fornecer soluções otimizadas para problemas mais complexos.

## Implementações Obrigatórias

1. **Objetos Virtuais**

   - Modelo de jogador, inimigos, pizza (bônus) e Projétil (Kunai).
     O modelo do player tem complexidade maior que `cow.obj`.
2. **Transformações Geométricas**

   - O jogador faz a movimentação do modelo player com o teclado e rotaciona ele com o mouse.
3. **Câmeras Virtuais**

   - **Câmera look-at**: Cutscene inicial.
   - **Câmera livre**: Durante o jogo a câmera acompanha o player e também é movimentada com o teclado e mouse.
4. **Instâncias de Objetos**

   - Os objetos de bônus, projétil e inimigos tem múltiplas instâncias.
5. **Testes de Interseção**

   - Teste de intersecção **cubo-cubo**: usada para colisão player-inimigo, inimigo-inimigo.
   - Teste de intersecção **cubo-plano**: usado para colisão entre o player e as paredes e o chão.
   - Teste de intersecção **ponto-esfera**: usado para colisão entre o player e a pizza (bônus).
     Implementados em collisions.cpp
6. **Iluminação**

   - **Difusa (Lambert)**: Usado na maioria dos objetos, como player, inimigo e projétil.
   - **Blinn-Phong**: Usado na pizza (bônus).
   - **Phong**: Todos os objetos usam.
7. **Mapeamento de Texturas**

   - Todos os objetos virtuais tem texturas sem deformidade e existem múltiplas texturas diferentes: a da parede, chão, player, inimigo e kunai.
8. **Curvas de Bézier**

   - A câmera segue uma curva de Bézier cúbica suave no ínicio do jogo, na cutscene.
9. **Animação de Movimento**

   - Todas as movimentações, de jogador, inimigo e kunai, utilizam delta_time e portanto não são alteradas pela framerate.

## Manual de Utilização

- Utilize as teclas W, A, S, D para mover o jogador.
- Use o mouse para rotacionar a câmera.
- Pressione o botão esquerdo do mause  para atacar os inimigos.

## Passos para Compilação e Execução

1. Instale ou configure o compilador (ex.: MinGW para C/C++).
2. Certifique-se de ter o CMake instalado.
3. Navegue até o diretório do projeto.
4. Utilizando o VScode, baixe as extensões de C/C++ e CMAKE
5. Utilizando o comando <CTRL+SHIFT+P> abra a paleta de coamndos e digite: "CMake: Build"
6. Assim deve ser criado uma pasta build na raiz do projeto com um executável do jogo.
