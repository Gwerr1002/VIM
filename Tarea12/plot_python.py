from slices import IndexTracker, plt, np
import struct
import itk,vtk


with open("../RMHEA109S") as f:
    rectype = np.dtype(np.ubyte)
    data = np.fromfile(f,dtype=rectype)

im = np.array(data)
im = np.reshape(data,(109,256,256))
#%%
im_itk = itk.GetImageFromArray(np.ascontiguousarray(im.astype(float)))

#%%
import SimpleITK as sitk

def downsamplePatient(im, resize_factor):

    original_CT = im
    dimension = original_CT.GetDimension()
    reference_physical_size = np.zeros(original_CT.GetDimension())
    reference_physical_size[:] = [(sz-1)*spc if sz*spc>mx  else mx for sz,spc,mx in zip(original_CT.GetSize(), original_CT.GetSpacing(), reference_physical_size)]
    
    reference_origin = original_CT.GetOrigin()
    reference_direction = original_CT.GetDirection()

    reference_size = [round(sz/resize_factor) for sz in original_CT.GetSize()] 
    reference_spacing = [ phys_sz/(sz-1) for sz,phys_sz in zip(reference_size, reference_physical_size) ]

    reference_image = sitk.Image(reference_size, original_CT.GetPixelIDValue())
    reference_image.SetOrigin(reference_origin)
    reference_image.SetSpacing(reference_spacing)
    reference_image.SetDirection(reference_direction)

    reference_center = np.array(reference_image.TransformContinuousIndexToPhysicalPoint(np.array(reference_image.GetSize())/2.0))
    
    transform = sitk.AffineTransform(dimension)
    transform.SetMatrix(original_CT.GetDirection())

    transform.SetTranslation(np.array(original_CT.GetOrigin()) - reference_origin)
  
    centering_transform = sitk.TranslationTransform(dimension)
    img_center = np.array(original_CT.TransformContinuousIndexToPhysicalPoint(np.array(original_CT.GetSize())/2.0))
    centering_transform.SetOffset(np.array(transform.GetInverse().TransformPoint(img_center) - reference_center))
    centered_transform = sitk.CompositeTransform([transform,centering_transform])
    #centered_transform.AddTransform(centering_transform)

    # sitk.Show(sitk.Resample(original_CT, reference_image, centered_transform, sitk.sitkLinear, 0.0))
    
    return sitk.Resample(original_CT, reference_image, centered_transform, sitk.sitkBSpline, 0.0)

cer = itk.GetArrayFromImage(im_itk)
cer_sitk = sitk.GetImageFromArray(cer)
res = downsamplePatient(cer_sitk, .5)
o = sitk.GetArrayFromImage(res)
o = itk.GetImageFromArray(o)
#%%
#cerebro = itk.ConnectedThresholdImageFilter(im_itk,Lower=65,Upper=90,Seed=[155,100,89],ReplaceValue=1)
cerebroS = itk.ConnectedThresholdImageFilter(o,Lower=68,Upper=85,Seed=[284,156,132],ReplaceValue=1)
#sm = itk.CurvatureFlowImageFilter(im_itk,NumberOfIterations = 2)
#gris =itk.ConnectedThresholdImageFilter(sm,Lower=55,Upper=68,Seed=[157,77,55],ReplaceValue=1)
#[113,73,70]
'''
#%%
saved = itk.GetArrayFromImage(cerebro).astype(np.ubyte).ravel()
saved.tofile("mgris")
'''
#%%

fig, ax = plt.subplots()
tracker = IndexTracker(ax, cerebroS)
fig.canvas.mpl_connect('scroll_event', tracker.on_scroll)
plt.show()


#%%

import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d.art3d import Poly3DCollection

from skimage import measure
from skimage.draw import ellipsoid

saved = itk.GetArrayFromImage(o)
# Use marching cubes to obtain the surface mesh of these ellipsoids
verts, faces, normals, values = measure.marching_cubes(saved, 0)
#%%
'''
fig = plt.figure(figsize=(10, 10))
ax = fig.add_subplot(111, projection='3d')

# Fancy indexing: `verts[faces]` to generate a collection of triangles
mesh = Poly3DCollection(verts[faces])
mesh.set_edgecolor('k')
ax.add_collection3d(mesh)
ax.set_xlim(0, 100)  # a = 6 (times two for 2nd ellipsoid)
ax.set_ylim(0, 100)  # b = 10
ax.set_zlim(0, 300)  # c = 16
'''

#%%
p =  verts[faces]
strips = p.reshape(-1).astype(np.float32)
#%%
strips.tofile("strips2")

#%%

im_vtk = itk.vtk_image_from_image(cerebro)
iso = vtk.vtkFlyingEdges3D()
#iso = vtk.vtkMarchingCubes()
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

ren_win.SetSize(1000, 800)
ren_win.SetWindowName('ULS Fetal')

ren_win.Render()
iren.Start()
