#include "SerializedNode.h"

SerializedNode::SerializedNode(string tagId)
{
    this->tagId = tagId;
}

SerializedNode::~SerializedNode()
{
    //dtor
}

void SerializedNode::addAttribute(string attrId, string attrVal) {
    attributes.push_back(pair<string, string>(attrId, attrVal));
}

void SerializedNode::addAttribute(string attrId, int attrVal) {
    std::stringstream sstr;
    sstr.str("");
    sstr << attrVal;
    attributes.push_back(pair<string, string>(attrId, sstr.str()));
}

void SerializedNode::addAttribute(string attrId, float attrVal) {
    std::stringstream sstr;
    sstr.str("");
    sstr << attrVal;
    attributes.push_back(pair<string, string>(attrId, sstr.str()));
}

void SerializedNode::addAttribute(string attrId, bool attrVal) {
    if(attrVal) {
        attributes.push_back(pair<string, string>(attrId, "true"));
    }
    else {
        attributes.push_back(pair<string, string>(attrId, "false"));
    }
}

void SerializedNode::addAttribute(string attrId, ofxVec2f attrVal) {
    std::stringstream sstr;
    sstr.str("");
    sstr << attrVal.x << " " << attrVal.y;
    attributes.push_back(pair<string, string>(attrId, sstr.str()));
}

void SerializedNode::addAttribute(string attrId, ofxVec3f attrVal) {
    std::stringstream sstr;
    sstr.str("");
    sstr << attrVal.x << " " << attrVal.y << " " << attrVal.z;
    attributes.push_back(pair<string, string>(attrId, sstr.str()));
}

void SerializedNode::addAttribute(string attrId, ofxVec4f attrVal) {
    std::stringstream sstr;
    sstr.str("");
    sstr << attrVal.x << " " << attrVal.y << " " << attrVal.z << " " << attrVal.w;
    attributes.push_back(pair<string, string>(attrId, sstr.str()));
}

void SerializedNode::addChildNode(SerializedNode* child) {
    childNodes.push_back(child);
}

string SerializedNode::getTagId() {
    return tagId;
}

vector<pair<string, string> > SerializedNode::getAttributes() {
    return attributes;
}

vector<SerializedNode*> SerializedNode::getChildNodes() {
    return childNodes;
}