def centralizar_obj(nome_arquivo):
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
            x = float(partes[1]) - centroid[0]
            y = float(partes[2]) - centroid[1]
            z = float(partes[3]) - centroid[2]
            linhas_centralizadas.append(f"v {x} {y} {z}\n")
        else:
            linhas_centralizadas.append(linha)
    
    # Salvar o arquivo centralizado
    nome_arquivo_centralizado = nome_arquivo.replace('.obj', '_centralizado.obj')
    with open(nome_arquivo_centralizado, 'w') as f:
        f.writelines(linhas_centralizadas)
    
    print(f"Arquivo centralizado salvo como {nome_arquivo_centralizado}")

# Exemplo de uso
centralizar_obj("C:/Users/marco/Documents/dev/trabalho_final_FCG/data/bunny.obj")
