from slices import IndexTracker, plt, np
import struct

"rb"
with open("../RMHEA109S") as f:
    rectype = np.dtype(np.ubyte)
    data = np.fromfile(f,dtype=rectype)

im = np.array(data)
im = np.reshape(data,(109,256,256))

fig, ax = plt.subplots()
tracker = IndexTracker(ax, im)
fig.canvas.mpl_connect('scroll_event', tracker.on_scroll)
plt.show()

"""
  sigmoidFilterBilateral(volumen,255,0,60,200,0.1,10);
  segmentar(segment,volumen,250,255);
"""
#materia blanca: 30 - 60
#hueso 50-255
