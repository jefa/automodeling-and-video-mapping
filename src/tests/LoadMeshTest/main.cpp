
#include "ProcessMesh.h"
#include "MeshDefinition.h"
#include <iostream>
#include <stdio.h>
#include <string>



using namespace std;


int main()
{
  MyMesh m;
  ProcessMesh p;
  string filename;
  filename = "greek_helmet2.obj";
  // load a mesh from a .obj file
  p.LoadMesh((&m) ,filename);
  //p.LoadMesh2((&m) ,filename);



  //if (m.bbox.IsNull() ){  cout << "dato bounding box de la maya esta vacio  ";}


  // proccess the mesh to Subsampling  with a top fixed number of samples
  p.PoissonDiskSampling((&m));
  // compute the normals of the vertices of a mesh
  p.ComputeNormalsForPointSet((&m));
  //use point and normal to build a surface using the Poisson Surface rconstruction approach.
  p.SurfaceReconstructionPoisson((&m));
  // write the result mesh in the file
  p.WriteMesh((&m));

  return 0;
}
