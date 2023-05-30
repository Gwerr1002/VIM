from slices import IndexTracker, plt, np
import struct
import itk

"rb"
with open("../RMHEA109S") as f:
    rectype = np.dtype(np.ubyte)
    data = np.fromfile(f,dtype=rectype)

im = np.array(data)
im = np.reshape(data,(109,256,256))

im_itk = itk.GetImageFromArray(np.ascontiguousarray(im))
cerebro = itk.ConnectedThresholdImageFilter(im_itk,Lower=65,Upper=90,Seed=[155,100,89],ReplaceValue=1)
#craneo =itk.ConnectedThresholdImageFilter(im_itk,Lower=96,Upper=255,Seed=[201,60,36],ReplaceValue=1)
#dientes=itk.ConnectedThresholdImageFilter(im_itk,Lower=30,Upper=60,Seed=[93,167,42],ReplaceValue=1)

fig, ax = plt.subplots()
tracker = IndexTracker(ax, cerebro)
fig.canvas.mpl_connect('scroll_event', tracker.on_scroll)
plt.show()

"""
  sigmoidFilterBilateral(volumen,255,0,60,200,0.1,10);
  segmentar(segment,volumen,250,255);
"""
#materia blanca: 30 - 60
#hueso 50-255
