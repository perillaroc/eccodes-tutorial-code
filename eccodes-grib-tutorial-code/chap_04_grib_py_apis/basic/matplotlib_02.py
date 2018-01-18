import numpy as np
import matplotlib
# or use
# echo "backend: TkAgg" >> ~/.matplotlib/matplotlibrc
matplotlib.use("TkAgg")


from mpl_toolkits.basemap import Basemap
import matplotlib.pyplot as plt
# make sure the value of resolution is a lowercase L,
#  for 'low', not a numeral 1
map = Basemap(projection='ortho', lat_0=50, lon_0=-100,
              resolution='l', area_thresh=1000.0)
map.drawcoastlines()
map.drawcountries()
map.fillcontinents(color='coral')
map.drawmapboundary()
map.drawmeridians(np.arange(0, 360, 30))
map.drawparallels(np.arange(-90, 90, 30))

plt.show()
