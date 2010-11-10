#include "Quad2D.h"
#include "ofGraphics.h"
#include "ofMain.h"

static const float quadTextCoords[] = {0,0, 1,0, 1,1, 0,1};

//Radio de los circulos
static const float radius = 5.0f;

Quad2D::Quad2D(string id) {
    selected = false;
    enabled = false;

    this->id = id;

    float centerX = 200.0f;
    float centerY = 200.0f;
    float quadWidth = 100.0f;
    float quadHeight = 100.0f;

    quadPoints[0] = centerX - quadWidth;quadPoints[1] = centerY - quadHeight;
    quadPoints[2] = centerX + quadWidth;quadPoints[3] = centerY - quadHeight;
    quadPoints[4] = centerX + quadWidth;quadPoints[5] = centerY + quadHeight;
    quadPoints[6] = centerX - quadWidth;quadPoints[7] = centerY + quadHeight;

    this->material = new Material();
}

Quad2D::Quad2D(string id, float x1,float y1,float x2,float y2,float x3, float y3, float x4, float y4) {
    selected = false;
    enabled = false;

    this->id = id;

    quadPoints[0] = x1;quadPoints[1] = y1;
    quadPoints[2] = x2;quadPoints[3] = y2;
    quadPoints[4] = x3;quadPoints[5] = y3;
    quadPoints[6] = x4;quadPoints[7] = y4;

    this->material = new Material();
}

Quad2D::~Quad2D() {
    //dtor
}

string Quad2D::getId() {
    return id;
}

void Quad2D::setEnabled(bool enabled) {
    this->enabled = enabled;
}

bool Quad2D::isEnabled() {
    return this->enabled;
}

void Quad2D::setMaterial(Material *mat) {
    this->material = mat;
}

Material* Quad2D::getMaterial() {
    return this->material;
}

void Quad2D::setPoint(int i, float x, float y) {
    if(i >= 0 && i <= 3)
    {
        quadPoints[i * 2] = x;
        quadPoints[1 + (i * 2)] = y;
    }
}

void Quad2D::getPoint(int i, float &x, float &y) {
    if(i >= 0 && i <= 3)
    {
        x = quadPoints[i * 2];
        y = quadPoints[1 + (i * 2)];
    }
}

int Quad2D::getControlPointAt(int x, int y) {
    int result = -1;
    if(!this->selected)
        return result;

    for(int i = 0; i < 4; i++)
    {
        float xc = quadPoints[i * 2];
        float yc = quadPoints[(i * 2) + 1];

        if(ofDistSquared(xc, yc, x, y) <= pow(radius, 2))
        {
            return i;
        }
    }
    return result;
}

void Quad2D::setSelected(bool selected) {
    this->selected = selected;
}

void Quad2D::draw() {
    if(!enabled) {
        return;
    }

    if(this->material != NULL){
        this->material->Enable();
    }
    else {
        glColor3f(0.7, 0.8, 0.9);
    }

    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glTexCoordPointer(2, GL_FLOAT, 0, &quadTextCoords);

    glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, &quadPoints[0]);

	glDrawArrays(GL_QUADS, 0, 4);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

    if(this->material != NULL){
        this->material->Disable();
    }

    #ifdef CONSOLE
    //Modo consola, dibuja solo alrededor.

    if(selected) {
        glColor4f(1.0f, 0.3f, 0.3f, 1.0f);
    }
    else {
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    }
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < 8; i += 2) {
        glVertex2f(quadPoints[i], quadPoints[i+1]);
    }
    glEnd();

    if(selected) {
        ofCircle(quadPoints[0], quadPoints[1], radius);
        ofCircle(quadPoints[2], quadPoints[3], radius);
        ofCircle(quadPoints[4], quadPoints[5], radius);
        ofCircle(quadPoints[6], quadPoints[7], radius);
    }

	#endif
}

void Quad2D::set(int aParam, float value) {
}

float Quad2D::get(int aParam) {
    return 0;
}
