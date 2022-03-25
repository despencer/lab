import pyrosm

osm = pyrosm.OSM('/mnt/mobihome/maps/central-fed-district-latest.osm.pbf', bounding_box = [37 + (30.804/60), 55 + (38.443/60), 37 + (32.804/60), 55 + (38.445/60)])
net = osm.get_network(network_type='driving')
net.head(2)