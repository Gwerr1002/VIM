# -*- coding: utf-8 -*-
"""
Created on Tue Feb 14 12:57:18 2023

@author: gerard
"""

import numpy as np
import matplotlib.pyplot as plt


class IndexTracker:
    def __init__(self, ax, X):
        self.index = int(X.shape[0]/2)
        self.X = X
        self.ax = ax
        #self.im = ax.imshow(self.X[:,self.index,:],cmap='gray')#saggital
        self.im = ax.imshow(self.X[self.index,::],cmap='gray',interpolation = None)
        #self.im = ax.imshow(self.X[::,self.index],cmap='gray',interpolation = None)
        self.update()

    def on_scroll(self, event):
        #print(event.button, event.step)
        increment = 1 if event.button == 'up' else -1
        max_index = self.X.shape[-1] - 1
        self.index = np.clip(self.index + increment, 0, max_index)
        self.update()

    def update(self):
        #self.im.set_data(self.X[:,self.index,:])
        self.im.set_data(self.X[self.index,::])
        #self.im.set_data(self.X[::,self.index])
        self.ax.set_title(
            f'Use scroll wheel to navigate\nindex {self.index}')
        self.im.axes.figure.canvas.draw()

if __name__ == "__main__":
    from itk import imread
    fig, ax = plt.subplots()
    vol = imread("C:/Users/gerard/Desktop/Proyecto Terminal/ProyectoT/Etapa1/I0000034.nrrd")
    # create an IndexTracker and make sure it lives during the whole
    # lifetime of the figure by assigning it to a variable
    tracker = IndexTracker(ax, vol)
    fig.canvas.mpl_connect('scroll_event', tracker.on_scroll)
    plt.show()
