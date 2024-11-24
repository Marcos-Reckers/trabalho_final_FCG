# Requisitos para o Trabalho de Computação Gráfica (FCG)

## Tecnologias e Código

* **Linguagem de programação** : Livre escolha.
* **Recomendação** : Uso de C++ com OpenGL.
  * Facilita reutilização do código das aulas práticas.
  * Melhora a criação de aplicações de alta performance com interação em tempo real.
* **Limite de código pronto** :
* **Máximo permitido** : 15% do código total.
* **Identificação obrigatória** :
  * Comentários com a palavra "FONTE" em maiúsculo.
  * Informar a origem de cada trecho de código reutilizado.
* **roibido** :
  * Uso de mais de 15% de código pronto.
  * Plágio de outros trabalhos (atuais ou anteriores).
* **Código desenvolvido em aula** : Reutilização permitida.
* **Bibliotecas de cálculo de transformações e câmera** : Proibidas.
* Exemplos de funções proibidas:
  * `gluLookAt()`, `gluOrtho2D()`, `glm::rotate()`, `glm::perspective()`, etc.

---

## Requisitos Técnicos

### **Interatividade**

* A aplicação deve possibilitar interação em  **tempo real** .
* Interação deve ocorrer via:
  * **Mouse**
  * **Teclado**
* Aplicações com jogabilidade comprometida devido à lentidão serão penalizadas.

### **Lógica e Objetivo**

* A aplicação deve possuir lógica de controle  **não-trivial** .
  * **Exemplo válido** : Jogos com lógica complexa.
  * **Exemplo inválido** : Aplicações que apenas carregam e exibem modelos 3D.

### **Transformações Geométricas**

* Utilização de matrizes:
  * **Model matrix** (Transformações geométricas dos objetos).
  * **Projection matrix** (Projeções).
  * **View matrix** (Sistema de coordenadas da câmera).

---

## Implementações Obrigatórias

1. **Objetos Virtuais**
   * Representados por **malhas poligonais complexas** (malhas de triângulos).
   * **Requisitos mínimos** :
   * Modelo geométrico com complexidade igual ou maior que `cow.obj`.
   * Uso de bibliotecas para carregar OBJ permitido (e.g., `tinyobjloader`).
   * **Variedade** de modelos geométricos é um diferencial.
2. **Transformações Geométricas**
   * Controladas pelo usuário via  **teclado e/ou mouse** .
3. **Câmeras Virtuais**
   * Implementação mínima:
     * **Câmera look-at**
     * **Câmera livre**
4. **Instâncias de Objetos**
   * No mínimo um objeto deve ser copiado com  **duas ou mais instâncias** .
   * Apenas as matrizes de modelagem devem ser alteradas.
5. **Testes de Interseção**
   * Implementação mínima de **três tipos** de teste de interseção:
     * Exemplo: cubo-cubo, cubo-plano, ponto-esfera.
   * **Propósito claro** dentro da lógica da aplicação (e.g., evitar colisões em um jogo de corrida).
   * Testes devem estar implementados em `collisions.cpp`.
6. **Iluminação**
   * Modelos de iluminação obrigatórios:
     * **Difusa (Lambert)**
     * **Blinn-Phong**
   * Modelos de interpolação obrigatórios:
     * **Gouraud** : Avaliado por vértice, interpolado por pixel.
     * **Phong** : Normais interpoladas, iluminação avaliada por pixel.
7. **Mapeamento de Texturas**
   * Todos os objetos virtuais devem usar  **texturas** .
   * **Requisitos mínimos** :
   * Uso de no mínimo **três imagens distintas** como texturas.
   * Texturas "esticadas" de forma não natural serão penalizadas.
8. **Curvas de Bézier**
   * No mínimo um objeto deve seguir uma  **curva de Bézier cúbica** .
   * O movimento deve ser **suave** e  **curvo** .
9. **Animação de Movimento**
   * Movimentações devem ser baseadas no  **tempo** :
     * Mesma velocidade independente do hardware.

---

## Avaliação

* **Apresentação**
  * Qualidade da apresentação conta na nota final.
  * Presença obrigatória nas apresentações dos colegas.
* **Pontuação individual**
  * Cada integrante será avaliado de forma independente.
* **Plágio**
  * Qualquer tipo de plágio acarretará  **nota zero** .
