# myQualityFoam
Application used in my Engineering Thesis "Application for evaluation of geometric model discretization quality".

Application is meant to be used inside OpenFOAM enviroment.

Created 01.2021.

## Table of contents
- [OpenFOAM](#openfoam)
- [Theoretical background](#theoretical-background)
- [Setup](#setup)
- [Running](#running)
- [Example of use](#example-of-use)

## OpenFOAM
OpenFOAM is an open-source C++ toolbox for CFD (Computational Fluid Dynamics). It is used in development of customized numerical solvers, but comes with a great deal of built in utilities. OpenFOAM consists of over 100 libraries with various classes and data types, which were used in this appliaction (e.g. scalar is a floating-point number)

## Theoretical background
Navier-Stokes equations can described any fluid known to this date. Partial differential equations cannot be solved directly. In order to obtain solution one must discretize solution and domain (space in which equations are meant to be solved). Computational mesh is created in which a set of complex equations is transformed to algebraic set of equations. By a mesh we understand a set of connected wth each other.

<p align="center">
  <img src="https://user-images.githubusercontent.com/83305684/119635332-de68d380-be13-11eb-8c91-2ee58e2a1050.png" />
</p>
<p align="center">
  <em>Different types of cells</em>
</p>

It does not come without a price. By discretization a large error can be created. One of the biggest impacts on solution correctness is so called mesh quality. Discretization is conducted with assumption of orthogonal mesh - a line connecting neighbour cells is parallel to normal vector of the common face.

<p align="center">
  <img src="https://user-images.githubusercontent.com/83305684/119634853-6c908a00-be13-11eb-9e25-5a9d9b57026a.png" />
<p align="center">
  <em>Orthogoanl mesh</em>
</p>

In reality we rarely have to deal with such ideal meshes. Usually cells are somehow distorted. It can be safely assumed that the more a cell is distorted the bigger numerical we can anticipate. 

<p align="center">
  <img src="https://user-images.githubusercontent.com/83305684/119636502-00af2100-be15-11eb-8d09-bf1274730d97.png" />
<p align="center">
  <em>Non-orthogoanl mesh</em>
</p>

To assess mesh quality we can use different metrics. The problem is that there is no one universal metric - each one is focused on different type of cell distortion. In order to be sure of the mesh quality an engineer needs to check multiple metric which values may not be consistent with each other. 

Two of mentioned metric are:
* Aspect Ratio

  Can be defined as stretching of the cell and is calculated by a ratio of longest to shortest edge in a cell.
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

***The aim of the thesis was to create an application to asses mesh quality using one metric, which would be the combination of conventional ones***

Dozens of numerical simulations were run. Impact of different quality metric was studied. Finally using Design of Experiments a model of quality metric was built.

  <p align="center">
  <img src="https://user-images.githubusercontent.com/83305684/119640357-d2334500-be18-11eb-8a24-933f2a77ae82.png" />
  <p align="center">
  <em>Quality metric function</em>
  </p>

Inputs parameters are Skewness and Aspect Ratio discussed above. Quality metric function outputs values from 0 to 1, where 1 is perfect value.

## Setup
Requires Linux or WSL if you're using Windows.
Install OpenFOAM software from: https://www.openfoam.com/ .
Clone repository to somewhere in your OpenFOAM directory. 
Check if $FOAM_USER_APPBIN is setup on your machine, should be created automatically while installing OpenFOAM, if not create it.
Compile application from /myQualityFoam using:
```
$ wmake
```

## Running
Enter case directory.
You need to create the mesh before running application.
Type:
```
myQualityFoam
```

## Example of use
This example used deafult OpenFOAM tutorial case:
> tutorials/mesh/blockMesh/pipe

First mesh needs to be created. In this example we'll use:
```
$ blockMesh
```
After the mesh is created, the application can be ran. 

Type:
```
$ myQualityFoam
```

First we will see mesh statistics.

<p align="center">
<img src="https://user-images.githubusercontent.com/83305684/119682787-74682280-be43-11eb-8ca6-1084ac5ed78f.png" width="600"/>
<p align="center">
<em>Mesh statistics</em>
</p>

Then mesh quality for component metrics as well as combined metric. The decision whether mesh quality is good enough depends on number of factors and should be made with consideration to individual example. 

<p align="center">
<img src="https://user-images.githubusercontent.com/83305684/119683720-2c95cb00-be44-11eb-80d7-9e4a1b6b0a9f.png" width="600"/>
<p align="center">
<em>Mesh quality</em>
</p>

At last the calculation time is displayed.

<p align="center">
<img src="https://user-images.githubusercontent.com/83305684/119684071-7da5bf00-be44-11eb-932d-65ec9f19dee1.png" width="600"/>
<p align="center">
<em>Calculation time</em>
</p>

One can use Paraview software to visalize mesh quality.
I strongly recomend adding Paraview to $PATH.
First we need to create dummy file for easier startup. Just type:
```
nano foam.foam
```
Then save empty file. Now, having enviromental variable setup properly we can start Paraview:
```
paraview foam.foam &
```
Now we can visualize mesh quality.

<p align="center">
<img src="https://user-images.githubusercontent.com/83305684/119685449-a9757480-be45-11eb-9438-34ef04e5e099.png" width="600"/>
<p align="center">
<em>Combined Quality metric</em>
</p>
