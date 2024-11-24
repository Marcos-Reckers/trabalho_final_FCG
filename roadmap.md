# Roadmap para Desenvolvimento do Jogo

## Etapa 1: Configuração Inicial e Câmera Livre

### Objetivo

Criar uma tela inicial com uma câmera livre que pode ser movimentada usando **WASD** e controlada com o mouse.

### Tarefas

1. Configurar o projeto base:
   * Estruturar diretórios: `src/`, `shaders/`, `assets/`.
   * Inicializar o ambiente OpenGL.
   * Criar um loop principal para:
     * Processar entradas do teclado e mouse.
     * Atualizar a lógica do jogo.
     * Renderizar a cena.
2. Implementar uma câmera livre:
   * Controle de movimento com  **WASD** .
   * Rotação utilizando o mouse.
3. Exibir um plano básico ou fundo para visualização inicial.

---

## Etapa 2: Ambiente e Personagem Principal

### Objetivo

Criar o ambiente e adicionar o modelo do personagem principal.

### Tarefas

1. Criar a  **box do ambiente** :
   * Implementar um modelo básico que representa o chão e paredes do ambiente.
   * Adicionar texturas ao ambiente.
2. Adicionar o  **personagem principal** :
   * Carregar um modelo 3D (OBJ) para o jogador.
   * Posicionar o modelo no centro do ambiente.
3. Permitir movimentação do personagem com:
   * **Teclado** : Movimento básico.
   * **Mouse** : Rotação do personagem ou câmera em relação à posição do cursor.

---

## Etapa 3: Inimigos e IA Básica

### Objetivo

Adicionar inimigos ao jogo e fazer com que eles sigam o personagem principal.

### Tarefas

1. Carregar o modelo 3D para os inimigos.
2. Implementar a lógica de geração de inimigos:
   * Spawn em posições aleatórias ao redor do ambiente.
   * Limitar a quantidade inicial de inimigos para testes.
3. Criar a IA de movimentação:
   * Fazer os inimigos seguirem o personagem principal utilizando vetores de direção.
4. Adicionar variação no movimento (opcional):
   * Permitir velocidades diferentes para os inimigos.
   * Testar interações entre múltiplos inimigos.

---

## Etapa 4: Colisões

### Objetivo

Implementar testes de colisão entre o jogador, inimigos e o ambiente.

### Tarefas

1. Implementar colisão básica para o jogador:
   * Impedir que o personagem principal atravesse as paredes do ambiente.
2. Implementar colisão entre o jogador e os inimigos:
   * Reduzir a vida do jogador ao entrar em contato com um inimigo.
3. Implementar colisão entre inimigos:
   * Evitar sobreposição direta (opcional para refinamento).
4. Criar arquivo separado (`collisions.cpp`) para organizar os testes:
   * **Cubo-cubo** : Exemplo para colisão entre inimigos e paredes.
   * **Cubo-plano** : Exemplo para colisão do jogador com o chão.
   * **Ponto-esfera** : Exemplo para disparos atingindo inimigos.

---

## Etapa 5: Disparos

### Objetivo

Adicionar disparos ao jogador, permitindo atacar e eliminar inimigos.

### Tarefas

1. Implementar projéteis:
   * Criar um modelo simples para os projéteis (ex.: esferas ou cubos).
   * Ativar disparos ao pressionar uma tecla (ex.:  **barra de espaço** ).
   * Limitar o tempo de vida ou distância dos projéteis.
2. Implementar lógica de ataque:
   * Detectar colisões entre projéteis e inimigos.
   * Remover projéteis ao colidir ou sair dos limites do ambiente.
   * Reduzir a vida dos inimigos ao serem atingidos.
3. Adicionar animações ou efeitos visuais para os disparos (opcional).

---

## Etapa 6: HUD e Refinamento

### Objetivo

Criar um HUD básico para exibir informações de vida, pontuação e outros dados relevantes.

### Tarefas

1. Criar um HUD minimalista:
   * Exibir a vida do jogador.
   * Exibir a quantidade de inimigos derrotados (pontuação).
2. Adicionar lógica de vitória/derrota:
   * Derrota: Vida do jogador chega a zero.
   * Vitória: Derrotar todos os inimigos (opcional para níveis básicos).
3. Refinar a jogabilidade:
   * Ajustar a velocidade e comportamento dos inimigos.
   * Balancear a dificuldade do jogo.

---

## Roadmap Resumido

1. **Câmera Livre** :

* Movimentação com WASD.
* Rotação com o mouse.

1. **Ambiente e Personagem** :

* Criar a box do ambiente.
* Adicionar e movimentar o personagem principal.

1. **Inimigos e IA** :

* Adicionar inimigos e fazê-los seguirem o jogador.

1. **Colisões** :

* Implementar colisões jogador-ambiente, jogador-inimigo, inimigo-inimigo.

1. **Disparos** :

* Criar projéteis e implementar ataques.

1. **HUD** :

* Exibir informações de vida e pontuação.
* Refinar lógica de vitória/derrota.

Com esse plano, o desenvolvimento é organizado em etapas claras, facilitando testes e entregas parciais.
