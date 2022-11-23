#!/usr/bin/python3

import matplotlib.pyplot as plt

fig = plt.figure()
ax = plt.subplot(2, 1, 1)
ax.plot( [1, 2, 3, 4] , [1, 4, 9, 16] )
ax.plot( [2, 3] , [16, 3] )
# ax.change_geometry(2, 1, 1)
ax = plt.subplot(2, 1, 2)
ax.plot( [1, 2, 3, 4] , [2, 4, 6, 8] )
fig.canvas.draw()
fig.canvas.flush_events()
fig.savefig('/mnt/mobihome/temp/mpl.png')
plt.close()
