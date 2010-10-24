#include "Quad2D.h"
#include "ofGraphics.h"

static const float quadTextCoords[] = {0,0, 1,0, 1,1, 0,1};
static const float radius = 5.0f;

Quad2D::Quad2D(float x1,float y1,float x2,float y2,float x3, float y3, float x4, float y4)
{
    quadPoints[0] = x1;
    quadPoints[1] = y1;
    quadPoints[2] = x2;
    quadPoints[3] = y2;
    quadPoints[4] = x3;
    quadPoints[5] = y3;
    quadPoints[6] = x4;
    quadPoints[7] = y4;
}

Quad2D::~Quad2D()
{
    //dtor
}

void Quad2D::setPoint(int i, float x, float y)
{
    if(i >= 0 && i <= 3)
    {
        quadPoints[i * 2] = x;
        quadPoints[1 + (i * 2)] = y;
    }
}

void Quad2D::getPoint(int i, float &x, float &y)
{
    if(i >= 0 && i <= 3)
    {
        x = quadPoints[i * 2];
        y = quadPoints[1 + (i * 2)];
    }
}

int Quad2D::getControlPointAt(int x, int y)
{
    int result = -1;
    for(int i = 0; i < 4; i++)
    {
        float xc = quadPoints[i * 2];
        float yc = quadPoints[(i * 2) + 1];

        if ((((xc - x) * (xc - x)) + ((yc - y) * (yc - y))) <= (radius * radius))
        {
            return i;
        }
    }
    return result;
}

void Quad2D::draw()
{
    #ifndef CONSOLE

    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glTexCoordPointer(2, GL_FLOAT, 0, &quadTextCoords);

    glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, &quadPoints[0]);

	glDrawArrays(GL_QUADS, 0, 4);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	#else
    //Modo consola, dibuja solo alrededor.

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < 8; i += 2) {
        glVertex2f(quadPoints[i], quadPoints[i+1]);
    }
    glEnd();
    glColor3f(1.0f, 0.0f, 0.0f);
    ofCircle(quadPoints[0], quadPoints[1], radius);
    ofCircle(quadPoints[2], quadPoints[3], radius);
    ofCircle(quadPoints[4], quadPoints[5], radius);
    ofCircle(quadPoints[6], quadPoints[7], radius);

	#endif
}

void Quad2D::set(int aParam, float value)
{
}

float Quad2D::get(int aParam)
{
    return 0;
}
