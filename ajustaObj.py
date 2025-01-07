import math

def ajusta_obj(nome_arquivo, escala):
    with open(nome_arquivo, 'r') as f:
        linhas = f.readlines()

    # Calcular o centróide do modelo
    vertices = [linha for linha in linhas if linha.startswith('v ')]
    centroid = [0.0, 0.0, 0.0]
    for vertice in vertices:
        partes = vertice.split()
        centroid[0] += float(partes[1])
        centroid[1] += float(partes[2])
        centroid[2] += float(partes[3])
    centroid = [c / len(vertices) for c in centroid]

    # Rotação de 90 graus em torno do eixo Y
    angulo = math.radians(90)
    cos_ang = math.cos(angulo)
    sin_ang = math.sin(angulo)

    linhas_centralizadas = []
    for linha in linhas:
        if linha.startswith('v '):
            partes = linha.split()
            x = (float(partes[1]) - centroid[0]) * escala
            y = (float(partes[2]) - centroid[1]) * escala
            z = (float(partes[3]) - centroid[2]) * escala

            # Aplicar rotação em torno do eixo Y
            x_rot = x * cos_ang - z * sin_ang
            z_rot = x * sin_ang + z * cos_ang

            linhas_centralizadas.append(f"v {x_rot} {y} {z_rot}\n")
        else:
            linhas_centralizadas.append(linha)

    # Salvar o arquivo centralizado
    nome_arquivo_centralizado = nome_arquivo
    with open(nome_arquivo_centralizado, 'w') as f:
        f.writelines(linhas_centralizadas)

    print(f"Arquivo centralizado salvo como {nome_arquivo_centralizado}")

# Exemplo de uso
#ajusta_obj("D:/user/Documents/UFRGS/TrabFinalFCG/trabalho_final_FCG/data/enemy.obj", 2)

if __name__ == "__main__":
    import sys
    if len(sys.argv) < 3:
        print("Uso: python ajustaObj.py <nome_arquivo> <escala>")
        sys.exit(1)

    nome_arquivo = sys.argv[1]
    escala = float(sys.argv[2])
    ajusta_obj(nome_arquivo, escala)