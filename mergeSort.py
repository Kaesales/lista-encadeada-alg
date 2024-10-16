def mergesort(lista, inicio = 0, fim=None):
    if fim is None:
        fim = len(lista)
    if(fim - inicio > 1): #isso aqui significa que enquanto a sublista tiver mais que 2 elementos, ocorrerá uma divisão
        meio = (inicio + fim)//2
        mergesort(lista, inicio, meio)
        mergesort(lista, meio, fim)
        merge(lista, inicio, meio, fim)



def merge(lista, inicio, meio, fim): #serve para mesclar as sublistas
    left = lista[inicio:meio]
    right = lista[meio:fim]
    topo_left,topo_right = 0, 0
    for k in range(inicio, fim):
        if topo_left >= len(left): 
            lista[k] = right[topo_right]
            topo_right = topo_right + 1 

        elif topo_right >= len(right):
            lista[k] = left[topo_left]
            topo_left = topo_left + 1

        elif left[topo_left] < right[topo_right]:
            lista[k] = left[topo_left]
            topo_left = topo_left + 1
        else:
            lista[k] = right[topo_right]
            topo_right = topo_right + 1 



#para criar sublistas precisaremos guardar as posições de inicio, meio e fim da lista
#O Merge Sort é um algoritmo baseado na ideia de dividir para conquistar. Ele divide recursivamente a lista ao meio até que as sublistas tenham apenas um elemento. 
#O cálculo de fim - inicio (ou right - left no código em inglês) ajuda a entender quantos elementos existem em uma sublista, e é fundamental para determinar o momento em que o caso base do algoritmo é atingido.

lista = [84,72,71,59,85,75,28,63,45,40]
print(lista)

mergesort(lista)
print(lista)