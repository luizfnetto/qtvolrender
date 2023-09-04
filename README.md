# qtvolrender

## MultiPass Volume Render

A simple demo of a Multipass Volume Rendering following the classical paper [1].

The intent is a personal refresh of my OpenGL and SciVis skills, and to build some experience with the QT framework.

At the moment there is just a simple rendering of a given volume dataset.

The following roadmap is planned:
- [x] Create a MVP with the volume rendering running 
- [X] Create a volume data class
- [X] Add camera
- [ ] Build UI to control rendering params
- [ ] Allow UI to change the loaded dataset
- [ ] Add support to some transfer functions

### Current output (04/09/2023)
![foot](https://github.com/luizfnetto/qtvolrender/assets/7663523/53dfae46-f145-48af-beb0-8a1a1fbf9b14)


### References

[1] J. Kruger and R. Westermann, "Acceleration techniques for GPU-based volume rendering," IEEE Visualization, 2003. VIS 2003., Seattle, WA, USA, 2003, pp. 287-292, doi: 10.1109/VISUAL.2003.1250384.
