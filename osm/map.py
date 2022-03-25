import osmnx as ox

g = ox.load_graphml('mosmm.gml')
attrs = []
for n in g.nodes(data = True):
    for d in n[1].keys():
        if d not in attrs:
            attrs.append(d)
print(attrs)