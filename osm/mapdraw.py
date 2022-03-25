import osmnx as ox

# (55.635, 37.526)

mosmm = (55 + (38.444/60), 37 + (31.804/60) )

g = ox.graph_from_point( mosmm, 25, network_type = 'all', simplify=False, retain_all=True, truncate_by_edge=True)
fig,_ = ox.plot_graph(g, show=False, dpi=2400)
fig.tight_layout(pad=0)
fig.savefig("osm.png")
