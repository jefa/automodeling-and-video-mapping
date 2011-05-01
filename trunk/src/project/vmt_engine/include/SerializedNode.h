#ifndef SERIALIZEDNODE_H
#define SERIALIZEDNODE_H

#include "ofxVectorMath.h"

#include <vector>
#include <string>
using namespace std;

class SerializedNode
{
    public:
        SerializedNode(string tagId);
        virtual ~SerializedNode();

        string getTagId();
        vector<pair<string, string> > getAttributes();
        vector<SerializedNode*> getChildNodes();

        void addAttribute(string attrId, string attrVal);
        void addAttribute(string attrId, int attrVal);
        void addAttribute(string attrId, float attrVal);
        void addAttribute(string attrId, bool attrVal);
        void addAttribute(string attrId, ofxVec2f attrVal);
        void addAttribute(string attrId, ofxVec3f attrVal);
        void addAttribute(string attrId, ofxVec4f attrVal);

        void addChildNode(SerializedNode* child);

    protected:
    private:
        string tagId;
        vector<pair<string, string> > attributes;
        vector<SerializedNode*> childNodes;
};

#endif // SERIALIZEDNODE_H
