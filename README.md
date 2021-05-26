# myQualityFoam
Application used in my Engineering Thesis "Application for evaluation of geometric model discretization quality".
Application is meant to be used inside of OpenFOAM enviroment.

## OpenFOAM
OpenFOAM is a open-source C++ toolbox for CFD (Computational Fluid Dynamics). It is used in development of customized numerical solvers, but comes with a great deal of built in utilities. OpenFOAM consists of over 100 libraries with various classes and data types, which were used in this appliaction (e.g. scalar is a floating point number)

## Theoretical background
Navier-Stokes equations can described any fluid known to this date. However being partial differntial equations cannot be solved directly. In order to obtain solution one must discretize solution and domain (space in which equations are meaant to be solved). Computational mesh is created in which a set of complex equations is transformed to algebraic set of equations. By a mesh we understand a set of connected wth each other.

<p align="center">
  <img src="https://user-images.githubusercontent.com/83305684/119635332-de68d380-be13-11eb-8c91-2ee58e2a1050.png" />
</p>
<p align="center">
  <em>Different types of cells</em>
</p>

It does not come without a price. By discretization a large error can be created. One of the biggest impacts on solution correctness is so called mesh quality. Discretization is conducted with assumption of orthogonal mesh - a line conecting neighbour cells is parallel to normal vector of the common face.

<p align="center">
  <img src="https://user-images.githubusercontent.com/83305684/119634853-6c908a00-be13-11eb-9e25-5a9d9b57026a.png" />
<p align="center">
  <em>Orthogoanl mesh</em>
</p>

In reality we rarly have to deal with such ideal meshes. Usually cells are somehow distorted. It can be safely assumed that the more a cell is distorted the bigger numerical we can aticipate. 

<p align="center">
  <img src="https://user-images.githubusercontent.com/83305684/119636502-00af2100-be15-11eb-8d09-bf1274730d97.png" />
<p align="center">
  <em>Non-orthogoanl mesh</em>
</p>

To assess mesh quality we can use different metrics. The problem is that there is no one universal metric - aech one is focused on different type of cell distortion. In order to be sure of the mesh quality an engineer needs to check multiple metric which values may not be consistent with each other. 

Two of mentioned metric are:
* Aspect Ratio

  Can be defined as streching of the cell and is calculated by a ratio of longest to shortest edge ina cell.
  <p align="center">
  <img src="https://user-images.githubusercontent.com/83305684/119638471-fb52d600-be16-11eb-8e11-18f1c7c853ae.png" />
  <p align="center">
  <em>Cell with high aspect ratio on the left</em>
  </p>
  
* Skewness

  Is based on a cells angle deviation from ideal one (60 degree for triangles and 90 quadrangle)
  
  <p align="center">
  <img src="https://user-images.githubusercontent.com/83305684/119639090-8d5ade80-be17-11eb-83e4-ce37f71317da.png" />
  <p align="center">
  <em>Cell with high skewness (purple)</em>
  </p>

***The aim of the thessis was to create an application to asses mesh quality using one metric, which would be the combination of conventional ones***

Dozens of numerical simulations were run. Impact of different quality metric was studied. Finally using Design of Experiments a model of quality metric was built.

  <p align="center">
  <img src="https://user-images.githubusercontent.com/83305684/119640357-d2334500-be18-11eb-8a24-933f2a77ae82.png" />
  <p align="center">
  <em>Quality metric function</em>
  </p>

Inputs parameters are discussed above Skewness and Aspect Ratio. Quality metric function outputs values from 0 to 1, where 1 is perfect value.
