from slices import IndexTracker, plt, np
import struct
import itk,vtk

"rb"
with open("../RMHEA109S") as f:
    rectype = np.dtype(np.ubyte)
    data = np.fromfile(f,dtype=rectype)

im = np.array(data)
im = np.reshape(data,(109,256,256))

im_itk = itk.GetImageFromArray(np.ascontiguousarray(im))
cerebro = itk.ConnectedThresholdImageFilter(im_itk,Lower=65,Upper=90,Seed=[155,100,89],ReplaceValue=1)
#craneo =itk.ConnectedThresholdImageFilter(im_itk,Lower=96,Upper=255,Seed=[201,60,36],ReplaceValue=1)

#saved = itk.GetArrayFromImage(cerebro).astype(np.ubyte).ravel()
#saved.tofile("cerebro")

'''
fig, ax = plt.subplots()
tracker = IndexTracker(ax, cerebro)
fig.canvas.mpl_connect('scroll_event', tracker.on_scroll)
plt.show()
'''
#%%
im_vtk = itk.vtk_image_from_image(cerebro)
iso = vtk.vtkFlyingEdges3D()
iso.SetInputData(im_vtk)
iso.ComputeGradientsOn()
iso.ComputeScalarsOn()#off
iso.InterpolateAttributesOn()
iso.SetValue(0, 1)#81 10
#
window = vtk.vtkWindowedSincPolyDataFilter()
window.SetInputConnection(iso.GetOutputPort())
window.SetNumberOfIterations(25)
window.SetPassBand(0.0001)
window.NormalizeCoordinatesOn()
window.FeatureEdgeSmoothingOn()
window.SetFeatureAngle(360)
window.SetEdgeAngle(360)
window.BoundarySmoothingOn()
window.NonManifoldSmoothingOn()
window.Update()
#
normal = vtk.vtkPolyDataNormals()
normal.SetInputConnection(window.GetOutputPort())
normal.SetFeatureAngle(360)
normal.ComputeCellNormalsOn()
normal.SplittingOn()
normal.ConsistencyOn()
normal.AutoOrientNormalsOn()
#
strip =vtk.vtkStripper()
strip.SetInputConnection(normal.GetOutputPort())
strip.Update()


#%%

from vtk.numpy_interface import dataset_adapter as dsa
from mpl_toolkits.mplot3d import axes3d
import matplotlib.pyplot as plt

strips = strip.GetOutput().GetStrips()
points = dsa.WrapDataObject(strip.GetOutput()).Points
points = np.array(points)
#%%
triangles = []
for i in range(len(points)-2):
    p1 = points[i]
    p2 = points[i+1]
    p3 = points[i+2]
    v1,v2 = p1-p2,p3-p2
    o = np.cross(v1,v2)@[1,1,1]
    if o != 0:
        pnts = [p1,p2,p3]
        for p in pnts:
            for i in p:
                triangles.append(i)

#%%
p = points[::100]
ax = plt.figure().add_subplot(projection='3d')
#ax.plot_trisurf(p[:,0], p[:,1], p[:,2], linewidth=0.2, antialiased=True)
ax.scatter(p[:,0], p[:,1], p[:,2], linewidth=0.2, antialiased=True)
#%%


iso_mapper = vtk.vtkPolyDataMapper()
iso_mapper.SetInputConnection(strip.GetOutputPort())
iso_mapper.ScalarVisibilityOff()
#
colors = vtk.vtkNamedColors()
colors.SetColor('SkinColor', [255, 192, 137, 255])#255 220 178
colors.SetColor('BkgColor',[0,0,0,255])
iso_actor = vtk.vtkActor()
iso_actor.SetMapper(iso_mapper)
iso_actor.GetProperty().SetColor(colors.GetColor3d('SkinColor'))
#
outline = vtk.vtkOutlineFilter()
outline.SetInputData(im_vtk)
#
outline_mapper = vtk.vtkPolyDataMapper()
outline_mapper.SetInputConnection(outline.GetOutputPort())
outline_actor = vtk.vtkActor()
outline_actor.SetMapper(outline_mapper)
#
outline_actor = vtk.vtkActor()
outline_actor.SetMapper(outline_mapper)
#
ren = vtk.vtkRenderer()
ren_win = vtk.vtkRenderWindow()
ren_win.AddRenderer(ren)
iren = vtk.vtkRenderWindowInteractor()
iren.SetRenderWindow(ren_win)
ren.AddActor(outline_actor)
ren.AddActor(iso_actor)
ren.SetBackground(colors.GetColor3d('BkgColor'))#SlateGray

ren.GetActiveCamera().SetFocalPoint(0, 0, 1)
ren.GetActiveCamera().SetPosition(0, 0, 0)
ren.GetActiveCamera().SetViewUp(1, 1, 0)
ren.ResetCamera()
ren.GetActiveCamera().Dolly(1.5)
ren.ResetCameraClippingRange()
'''
filter = vtk.vtkRenderLargeImage()
filter.SetMagnification(1)
filter.SetInput(ren)
png = vtk.vtkPNGWriter()
png.SetFileName("logo.png")
png.SetInputConnection(filter.GetOutputPort())
png.Write()
'''
ren_win.SetSize(1000, 800)
ren_win.SetWindowName('ULS Fetal')

ren_win.Render()
iren.Start()



