#pragma once
#include <map>

#include <v8.h>
#include <uv.h>
#include <node.h>
#include <node_object_wrap.h>
#include <string>
#include <memory>

#include "H5Cpp.h"

namespace NodeHDF5 {

    using namespace v8;
    using namespace node;
    
enum HLType {
    HL_TYPE_UNKNOWN = -1,      /* Unknown object type                      */
    HL_TYPE_LITE = 0,             /* Lite dataset interface                        */
    HL_TYPE_IMAGE = 1,           /* Image                      */
    HL_TYPE_TABLE = 2,    /* Table   */
    HL_TYPE_PACKET_TABLE = 3,             /* Packets       */
    HL_TYPE_DIMENSION_SCALES = 4,             /*        */
    HL_TYPE_OPTIMIZED_FUNCTIONS = 5,             /*        */
    HL_TYPE_EXTENSIONS = 6             /*        */
};

    class File : public ObjectWrap {
    protected:
			std::map<unsigned long, unsigned long> toAccessMap;
            hid_t plist_id, gcpl, dtpl_id, dapl_id, dcpl_id;
			void InitMap()
			{
				toAccessMap = std::map<unsigned long, unsigned long> { { 0, H5F_ACC_RDONLY }, { 1, H5F_ACC_RDWR }, { 2, H5F_ACC_TRUNC }, { 3, H5F_ACC_EXCL }, { 4, H5F_ACC_DEBUG }, { 5, H5F_ACC_CREAT } };
			}

        public:
            static void Initialize (Handle<Object> target);
            H5::H5File* FileObject();
            hid_t getGcpl(){return gcpl;};
        
        private:
            H5::H5File* m_file;
            File(const char* path);
            File(const char* path, unsigned long access);
            ~File();
            static Persistent<FunctionTemplate> Constructor;
            static void New (const v8::FunctionCallbackInfo<Value>& args);
            static void CreateGroup (const v8::FunctionCallbackInfo<Value>& args);
            static void OpenGroup (const v8::FunctionCallbackInfo<Value>& args);
            static void Refresh (const v8::FunctionCallbackInfo<Value>& args);
            static void Flush (const v8::FunctionCallbackInfo<Value>& args);
            static void Close (const v8::FunctionCallbackInfo<Value>& args);
            static void GetNumAttrs (const v8::FunctionCallbackInfo<Value>& args);
            static void GetMemberNamesByCreationOrder (const v8::FunctionCallbackInfo<Value>& args);
            static void GetChildType (const v8::FunctionCallbackInfo<Value>& args);
        
    };
    
    class Group : public ObjectWrap {
        
        private:
            std::string name;
            H5::Group m_group;
            std::shared_ptr<H5::PropList> gcpl;
            static Persistent<FunctionTemplate> Constructor;
            static void New (const v8::FunctionCallbackInfo<Value>& args);
            
        public:
            Group(H5::Group group);
            static void Initialize ();
            static Local<Object> Instantiate (Local<Object> file);
            static Local<Object> Instantiate (const char* path, Local<Object> file, unsigned long creationOrder = 0);
            static void Create (const v8::FunctionCallbackInfo<Value>& args);
            static void Open (const v8::FunctionCallbackInfo<Value>& args);
            static void OpenGroup (const v8::FunctionCallbackInfo<Value>& args);
            static void Refresh (const v8::FunctionCallbackInfo<Value>& args);
            static void Flush (const v8::FunctionCallbackInfo<Value>& args);
            static void Close (const v8::FunctionCallbackInfo<Value>& args);
            static void GetNumAttrs (const v8::FunctionCallbackInfo<Value>& args);
            static void GetAttributeNames (const v8::FunctionCallbackInfo<Value>& args);
            static void ReadAttribute (const v8::FunctionCallbackInfo<Value>& args);
            static void GetNumObjs (const v8::FunctionCallbackInfo<Value>& args);
            static void GetMemberNames (const v8::FunctionCallbackInfo<Value>& args);
            static void GetMemberNamesByCreationOrder (const v8::FunctionCallbackInfo<Value>& args);
            static void GetChildType (const v8::FunctionCallbackInfo<Value>& args);
            static void getDatasetType (const v8::FunctionCallbackInfo<Value>& args);
            
    };

};