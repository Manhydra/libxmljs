// Copyright 2009, Squish Tech, LLC.
#include "./xml_parser.h"
#include "./xml_sax_parser.h"
#include "./xml_document.h"

namespace libxmljs {

v8::Handle<v8::Value>
ParseXmlString(const v8::Arguments& args) {
  v8::HandleScope scope;

  if (!args[0]->IsString())
    return v8::ThrowException(v8::Exception::Error(
      v8::String::New("Must supply parseString with a string")));

  v8::String::Utf8Value str(args[0]->ToString());
  xmlResetLastError();
  xmlDoc *doc = xmlReadMemory(*str, str.length(), NULL, NULL, 0);
  if (doc == NULL) {
    xmlFreeDoc(doc);
    return v8::Null();
  }

  return LIBXMLJS_GET_MAYBE_BUILD(XmlDocument, xmlDoc, doc);
}

v8::Handle<v8::Value>
ParseXmlFile(const v8::Arguments& args) {
  v8::HandleScope scope;

  if (!args[0]->IsString())
    return v8::ThrowException(v8::Exception::Error(
      v8::String::New("Must supply parseFile with a filename")));

  v8::String::Utf8Value str(args[0]->ToString());
  xmlResetLastError();
  xmlDoc *doc = xmlReadFile(*str, NULL, 0);
  if (doc == NULL) {
    xmlFreeDoc(doc);
    return v8::Null();
  }

  return LIBXMLJS_GET_MAYBE_BUILD(XmlDocument, xmlDoc, doc);
}

void
XmlParser::Initialize(v8::Handle<v8::Object> target) {
  v8::HandleScope scope;

  LIBXMLJS_SET_METHOD(target,
                      "parseXmlString",
                      ParseXmlString);

  LIBXMLJS_SET_METHOD(target,
                      "parseXmlFile",
                      ParseXmlFile);

  XmlSaxParser::Initialize(target);
}
}  // namespace libxmljs