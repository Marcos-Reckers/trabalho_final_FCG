import numpy as np

def ler_obj(filepath):
    with open(filepath, 'r') as file:
        linhas = file.readlines()
    vertices = []
    faces = []
    for linha in linhas:
        if linha.startswith('v '):
            vertices.append(list(map(float, linha.strip().split()[1:])))
        elif linha.startswith('f '):
            faces.append(linha.strip().split()[1:])
    return np.array(vertices), faces

def salvar_obj(filepath, vertices, faces):
    with open(filepath, 'w') as file:
        for vertice in vertices:
            file.write(f"v {' '.join(map(str, vertice))}\n")
        for face in faces:
            file.write(f"f {' '.join(face)}\n")

def rotacionar(vertices, angulo, eixo):
    angulo = np.radians(angulo)
    if eixo == 'x':
        matriz_rotacao = np.array([
            [1, 0, 0],
            [0, np.cos(angulo), -np.sin(angulo)],
            [0, np.sin(angulo), np.cos(angulo)]
        ])
    elif eixo == 'y':
        matriz_rotacao = np.array([
            [np.cos(angulo), 0, np.sin(angulo)],
            [0, 1, 0],
            [np.sin(angulo), 0, np.cos(angulo)]
        ])
    elif eixo == 'z':
        matriz_rotacao = np.array([
            [np.cos(angulo), -np.sin(angulo), 0],
            [np.sin(angulo), np.cos(angulo), 0],
            [0, 0, 1]
        ])
    else:
        raise ValueError("Eixo deve ser 'x', 'y' ou 'z'")
    return np.dot(vertices, matriz_rotacao.T)

def main():
    input_filepath = 'C:/Users/marco/Documents/dev/trabalho_final_FCG/data/plane.obj'
    output_filepath = 'C:/Users/marco/Documents/dev/trabalho_final_FCG/data/plane_rotate.obj'
    angulo = 90  # ângulo de rotação em graus
    eixo = 'z'  # eixo de rotação ('x', 'y' ou 'z')

    vertices, faces = ler_obj(input_filepath)
    vertices_rotacionados = rotacionar(vertices, angulo, eixo)
    salvar_obj(output_filepath, vertices_rotacionados, faces)

if __name__ == "__main__":
    main()

