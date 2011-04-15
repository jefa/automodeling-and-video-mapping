#ifndef _PROCESSMESH
#define _PROCESSMESH

#include "MeshDefinition.h"
#include <string>
using namespace std;
using namespace vcg;
using namespace tri;
using namespace vertex;
using namespace face;


class ProcessMesh {

   public:
        ProcessMesh();
        virtual ~ProcessMesh();

        void LoadMesh(MyMesh *m, string filename,int NumberOfVertices, int NumberOfFaces);
        void LoadMesh2(MyMesh *m, string filename);
        void WriteMesh(MyMesh *m);
        void PoissonDiskSampling(MyMesh *m);
        void ComputeNormalsForPointSet(MyMesh *m);
        void SurfaceReconstructionPoisson(MyMesh *m);



   //protected:

   //private:
};

#endif // PROCESSMESH_H
