#ifndef __MeshDefinition_h__
#define __MeshDefinition_h__

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

#include <vcg/simplex/vertex/base.h>
#include <vcg/simplex/vertex/component.h>
#include <vcg/simplex/face/base.h>
#include <vcg/simplex/face/component.h>

#include <vcg/complex/trimesh/base.h>


class MyVertex;
class MyFace;

class MyUsedTypes: public vcg::UsedTypes< vcg::Use<MyVertex>::AsVertexType,vcg::Use<MyFace>::AsFaceType>{};


class MyVertex : public vcg::Vertex<MyUsedTypes, vcg::vertex::Coord3d, vcg::vertex::Normal3f> {};
class MyFace : public vcg::Face<MyUsedTypes, vcg::face::VertexRef> {};
class MyMesh : public vcg::tri::TriMesh< std::vector<MyVertex>, std::vector<MyFace> > {};


#endif
