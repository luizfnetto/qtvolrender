# qtvolrender

## MultiPass Volume Render

A simple demo of a Multipass Volume Rendering following the classical paper [1].

The intent is a personal refresh of my OpenGL and SciVis skills, and to build some experience with the QT framework.

At the moment there is just a simple rendering of a given volume dataset.

The following roadmap is planned:
- [x] Create a MVP with 
- [ ] Create a volume data class
- [ ] Add camera
- [ ] Build UI to control vol. rendering params.
- [ ] Add support to some transfer functions

### Current output (30/08/2023)
![image](https://github.com/luizfnetto/qtvolrender/assets/7663523/8994046b-32ae-43e7-841f-68f96e4c0c85)

### References

[1] J. Kruger and R. Westermann, "Acceleration techniques for GPU-based volume rendering," IEEE Visualization, 2003. VIS 2003., Seattle, WA, USA, 2003, pp. 287-292, doi: 10.1109/VISUAL.2003.1250384.
