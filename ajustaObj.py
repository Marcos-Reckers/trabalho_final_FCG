def ajusta_obj(nome_arquivo, escala):
    vertices = []
    
    # Ler o arquivo .obj
    with open(nome_arquivo, 'r') as f:
        linhas = f.readlines()
    
    # Extrair vértices
    for linha in linhas:
        if linha.startswith('v '):  # Linhas de vértices começam com "v "
            partes = linha.split()
            vertices.append([float(partes[1]), float(partes[2]), float(partes[3])])
    
    # Calcular o centroide
    centroid = [sum(coord) / len(vertices) for coord in zip(*vertices)]
    
    # Centralizar os vértices
    linhas_centralizadas = []
    for linha in linhas:
        if linha.startswith('v '):
            partes = linha.split()
            x = (float(partes[1]) - centroid[0]) * escala
            y = (float(partes[2]) - centroid[1]) * escala
            z = (float(partes[3]) - centroid[2]) * escala
            linhas_centralizadas.append(f"v {x} {y} {z}\n")
        else:
            linhas_centralizadas.append(linha)
    
    # Salvar o arquivo centralizado
    nome_arquivo_centralizado = nome_arquivo
    with open(nome_arquivo_centralizado, 'w') as f:
        f.writelines(linhas_centralizadas)
    
    print(f"Arquivo centralizado salvo como {nome_arquivo_centralizado}")

# Exemplo de uso
ajusta_obj("D:/user/Documents/UFRGS/TrabFinalFCG/trabalho_final_FCG/data/enemy.obj", 4)
