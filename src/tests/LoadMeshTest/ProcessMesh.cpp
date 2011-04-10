#include "ProcessMesh.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vcg/complex/trimesh/allocate.h>
#include <vcg/complex/trimesh/point_sampling.h>
#include <vcg/complex/trimesh/update/bounding.h>
#include <vcg/space/normal_extrapolation.h>
#include <wrap/io_trimesh/import.h>


using namespace std;

class BaseSampler
{
	public:
	BaseSampler(MyMesh* _m){m=_m; uvSpaceFlag = false; qualitySampling=false; };
	MyMesh *m;

	int texSamplingWidth;
	int texSamplingHeight;
	bool uvSpaceFlag;
	bool qualitySampling;

	void AddVert(const MyMesh::VertexType &p)
	{
		Allocator<MyMesh>::AddVertices(*m,1);
		m->vert.back().ImportData(p);
	}

	void AddFace(const MyMesh::FaceType &f, MyMesh::CoordType p)
	{
		Allocator<MyMesh>::AddVertices(*m,1);
		m->vert.back().P() = f.P(0)*p[0] + f.P(1)*p[1] +f.P(2)*p[2];
		m->vert.back().N() = f.V(0)->N()*p[0] + f.V(1)->N()*p[1] + f.V(2)->N()*p[2];

		if (qualitySampling)
      m->vert.back().Q() = f.V(0)->Q()*p[0] + f.V(1)->Q()*p[1] + f.V(2)->Q()*p[2];
	}
  /*      void AddTextureSample(const MyMesh::FaceType &f, const MyMesh::CoordType &p, const Point2i &tp, float edgeDist)
	{
                if (edgeDist != .0) return;

		tri::Allocator<MyMesh>::AddVertices(*m,1);

		if(uvSpaceFlag) m->vert.back().P() = Point3f(float(tp[0]),float(tp[1]),0);
							 else m->vert.back().P() = f.P(0)*p[0] + f.P(1)*p[1] +f.P(2)*p[2];

		m->vert.back().N() = f.V(0)->N()*p[0] + f.V(1)->N()*p[1] +f.V(2)->N()*p[2];
		if(tex)
		{
			//QRgb val;
                        // Computing normalized texels position
                        int xpos = (int)(tex->width()  * (float(tp[0])/texSamplingWidth)) % tex->width();
                        int ypos = (int)(tex->height() * (1.0- float(tp[1])/texSamplingHeight)) % tex->height();

                        if (xpos < 0) xpos += tex->width();
                        if (ypos < 0) ypos += tex->height();

			val = tex->pixel(xpos,ypos);
			m->vert.back().C().SetRGB(qRed(val),qGreen(val),qBlue(val));
		}

	}*/
}; // end class BaseSampler

ProcessMesh::ProcessMesh(){
}
ProcessMesh::~ProcessMesh(){
}

void ProcessMesh::LoadMesh2(MyMesh *m, string filename) {

vcg::tri::io::Importer<MyMesh>::Open((*m),"greek_helmet.obj",0);


 // io::Importer::Open(m,filename,0);

  cout << "number of vertices " <<  (*m).vert.size()  << '\n';

  cout << "number of faces " << (*m).face.size()<< '\n';


}
void ProcessMesh::LoadMesh(MyMesh *m, string filename) {

int cantEnter = 0;
int countV;
int countVN;
int countF;
float coord1,coord2,coord3;
bool isTheEnd=false;

ifstream file;
char inputx,inputx2;

int vIndex1 = 0, vIndex2 = 0, vIndex3 = 0;
//int tIndex1 = 0, tIndex2 = 0, tIndex3 = 0;
int nIndex1 = 0, nIndex2 = 0, nIndex3 = 0;


 (*m).Clear();
MyMesh::VertexPointer ivp[1];
MyMesh::VertexPointer ivp2[3];
MyMesh::VertexIterator vi;
MyMesh::FaceIterator fi;

 countV = 0;
 countVN = 0;
 countF = 0;


  file.open(filename.data());
  if(file.fail() == true)

  cout<<  "File could not be opened";
  else//
  {//cout<< "OK";
     while(! isTheEnd )
	{

     coord1 = 0.0;
     coord2 = 0.0;
     coord3 = 0.0;
     isTheEnd = true;

     file.get(inputx);

     if (inputx == 'v'){
         //  vertices
         file.get(inputx);
         // vertices coord
         if (inputx == ' '){
             countV ++;
             file >> coord1 >> coord2 >> coord3;
             //allocate space for a new vertice
             Allocator<MyMesh>::AddVertices((*m),1);

             vi=(*m).vert.begin();
             ivp[0]=&*vi;(*vi).P()= MyMesh::CoordType ( coord1, coord2, coord3); ++vi;

             file.get(inputx);
             isTheEnd = false;
            }
         else {
             // normals
             if (inputx == 'n'){
             countVN ++;
             file >> coord1 >> coord2 >> coord3;
                 //cout <<"coord1" <<coord1;
                 //cout <<"coord2" <<coord2;
                 //cout <<"coord3" <<coord3 <<'\n';

                 file.get(inputx);
                 isTheEnd = false;
         }

         }
     }
    else {
        if (inputx == 'f'){
            //faces   format:  f v/vt/vn v/vt/vn v/vt/vn v/vt/vn we use without texture:  f v//vn v//vn v//vn v//vn


            file.get(inputx);
            countF ++;

			file >> vIndex3 >> inputx2 >>  inputx2 >> nIndex3 >>  vIndex2 >>  inputx2 >> inputx2 >> nIndex2 >>  vIndex1 >>inputx2 >>  inputx2 >> nIndex1;
            //cout<< "Index3 " <<vIndex3<<" " << tIndex3 << " " << nIndex3 << '\n';
            //cout<< "Index2 " <<vIndex2<<" " << tIndex2 << " " << nIndex2 << '\n';
            //cout<< "Index1 " <<vIndex1<<" " << tIndex1 << " " << nIndex1 << '\n';

            //allocate space for a new face
            Allocator<MyMesh>::AddFaces((*m),1);
            fi=(*m).face.begin();
            ivp2[0]=&(*m).vert[vIndex1];
            ivp2[1]=&(*m).vert[vIndex2];
            ivp2[2]=&(*m).vert[vIndex3];
            (*fi).V(0)=ivp2[0];  (*fi).V(1)=ivp2[1]; (*fi).V(2)=ivp2[2];fi++;

            // Start reading the beginning of the next line.
            file.get(inputx);
            isTheEnd = false;

        }
        else {
           if (inputx  == '#'){
                while(inputx != '\n')
                {
                    file.get(inputx);
                    //cout<< inputx;
                }

                //cout<< inputx;
                isTheEnd = false;

            }
           /* else{
                if (inputx  == ' '  ){
                    file.get(inputx);
                    while(inputx != '\n')
                    {cout<< "loop nunca sale?? ";
                        file.get(inputx);
                        cout<< inputx;
                    }
                cout<< inputx;
                isTheEnd = false;
                }*/
                else{
                    if (inputx  ==  '\n' ){
                    //cout<< inputx;
                    cantEnter ++ ;
                    file.get(inputx);
                    isTheEnd =  (cantEnter > 5);
                    //cout << cantEnter <<"   "  <<isTheEnd;
                    }
                }
            //}
        }
    }
  }

  cout << "number of vertices " <<  (*m).vert.size()  << '\n'; //countV << '\n';
 // cout << "number of normals " <<  countVN << '\n';
  cout << "number of faces " << (*m).face.size()<< '\n';

  file.close();

 }
 tri::UpdateBounding<MyMesh>::Box((*m));
}
void ProcessMesh::WriteMesh(MyMesh *m) {
}
void ProcessMesh::PoissonDiskSampling(MyMesh *m) {

            //setup parameters
            BaseSampler mps(&(*m));
/*
MyMesh::VertexIterator vi;
int i=0;
for(vi = (*m).vert.begin(); vi!=(*m).vert.end(); ++vi )
{

       if(!(*vi).IsD())
     {
    //cout<<" looop " <<i;
    i++;
               mps.AddVert((*vi));
              cout << mps.texSamplingHeight;
     }
}

  cout<<" SALGO DE loop cargo basesampler";
*/

            int sampleNum =1000;
            float radius;
            radius= tri::SurfaceSampling<MyMesh,BaseSampler>::ComputePoissonDiskRadius((*m),sampleNum);

            //cout<< "radius poissondisksampling   " << radius<< '\n';
            radius=0.246799;

            tri::SurfaceSampling<MyMesh,BaseSampler>::PoissonDiskParam pp;

            //poisson samplig need a support mesh from which it takes vertexes; we use the same input mesh
            //as support mesh, so we are sure that pointer to vertexes of input mesh are returned.
            //perform sampling: number of samples returned can be greater or smaller of the requested amount


            MyMesh *presampledMesh=&((*m));


           // cout << " adaptiveRadiusFlag "<<pp.adaptiveRadiusFlag;
           // cout << " radiusVariance "<<pp.radiusVariance;
           // cout << " preGenFlag "<<pp.preGenFlag;

            //tri::SurfaceSampling<MyMesh,BaseSampler>::PoissonDisk((*m),mps, (*presampledMesh), radius, pp);
            tri::SurfaceSampling<MyMesh,BaseSampler>::PoissonDiskPruning((*m),mps, (*presampledMesh), radius, pp);
            tri::UpdateBounding<MyMesh>::Box((*m));


            cout << "number of vertices after PoissonDiskSampling : " <<  (*m).vn  << '\n';

}
void ProcessMesh::ComputeNormalsForPointSet(MyMesh *m) {

  //Allocator<MyMesh>::CompactVertexVector((*m));
  //NormalExtrapolation<vector<MyVertex> >::ExtrapolateNormals((*m).vert.begin(), (*m).vert.end(), 16,-1,NormalExtrapolation<vector<MyVertex> >::IsCorrect);
  // cout << "number of normal after ComputeNormalsForPointSet : " <<  (*m).vn  << '\n';

}
void ProcessMesh::SurfaceReconstructionPoisson(MyMesh *m) {
}

