import osmnx as ox

mosmm = (55 + (38.444/60), 37 + (31.804/60) )

g = ox.graph_from_point( mosmm, 5000, network_type = 'all', simplify=False, retain_all=True, truncate_by_edge=True)
ox.save_graphml(g, filepath='mosmm.gml')
ox.save_graph_geopackage(g, filepath='mosmm.gpkp')
