## Relatório Ninja Survival
**Alunos**: Guilherme d'Ávila Pinheiro, Marcos Luiz Kurth Reckers.

## Requisitos Técnicos
 A aplicação possibilita interação em tempo real via o mouse e teclado para mover o jogador e atacar inimigos.

## Implementações Obrigatórias

1. **Objetos Virtuais**
   * Modelo de jogador, inimigos, pizza (bônus) e Projétil (Kunai).
   O modelo do player tem complexidade maior que `cow.obj`.

2. **Transformações Geométricas**
   * O jogador faz a movimentação do modelo player com o teclado e rotaciona ele com o mouse.

3. **Câmeras Virtuais**
     * **Câmera look-at**:
     Cutscene inicial.
     * **Câmera livre**:
     Durante o jogo a câmera acompanha o player e também é movimentada com o teclado e mouse.

4. **Instâncias de Objetos**
   * Os objetos de bônus, projétil e inimigos tem múltiplas instâncias.

5. **Testes de Interseção**
   * Teste de intersecção **cubo-cubo**: usada para colisão player-inimigo, inimigo-inimigo.
   * Teste de intersecção **cubo-plano**: usado para colisão entre o player e as paredes e o chão.
   * Teste de intersecção **ponto-esfera**: usado para colisão entre o player e a pizza (bônus).
   Implementados em collisions.cpp

6. **Iluminação**
     * **Difusa (Lambert)**: Usado na maioria dos objetos, como player, inimigo e projétil.

     * **Blinn-Phong**: Usado na pizza (bônus).

     * **Gouraud**: Está faltando na implementação.

     * **Phong** : Todos os objetos usam.

7. **Mapeamento de Texturas**
   * Todos os objetos virtuais tem texturas sem deformidade e existem múltiplas texturas diferentes: a da parede, chão, player, inimigo e kunai.

8. **Curvas de Bézier**
   * A câmera segue uma  curva de Bézier cúbica suave no ínicio do jogo, na cutscene.

9. **Animação de Movimento**
    * Todas as movimentações, de jogador, inimigo e kunai, utilizam delta_time e portanto não são alteradas pela framerate.