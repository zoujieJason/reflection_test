#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <sstream>
    
#include "target_data.pb.h"

using keyType = std::pair<google::protobuf::FieldDescriptor::CppType, std::string>; 

void parse_key(const google::protobuf::Message &message, std::queue<keyType> &Q, std::string &key)
{
    if(Q.empty())
    {
        return; 
    }

    const google::protobuf::Descriptor* descriptor = message.GetDescriptor();
    const google::protobuf::Reflection* reflection = message.GetReflection();

    const auto token = Q.front();
    Q.pop();
    for(size_t i = 0; i < descriptor->field_count(); ++i)
    {
        const google::protobuf::FieldDescriptor* field = descriptor->field(i);
        if(reflection->HasField(message, field))
        {
            const auto field_cpp_type = field->cpp_type();
            const auto field_name = field->name();
            if(field_cpp_type != token.first || field_name != token.second)
            {
                continue;
            }

            switch (field_cpp_type)
            {
#define CAST_FIELD_TYPE(proto_type, field_type, cpp_type)\
            case google::protobuf::FieldDescriptor::CPPTYPE_##proto_type:\
            {\
                key = std::to_string(reflection->Get##field_type(message, field));\
                break;\
            }

            CAST_FIELD_TYPE(INT32, Int32, int);
            CAST_FIELD_TYPE(FLOAT, Float, float);
            CAST_FIELD_TYPE(BOOL, Bool, bool);
#undef CAST_FIELD_TYPE
            case google::protobuf::FieldDescriptor::CPPTYPE_MESSAGE:
                parse_key(reflection->GetMessage(message, field), Q, key);
            default:
                break;
            }
        }
    }
}

void parse_key(const google::protobuf::Message &message, char * arg, std::string &key)
{
    std::istringstream ISS(arg); 
    std::string token;
    std::queue<keyType> Q;
    while(std::getline(ISS, token, '.'))
    {
        std::istringstream iss(token); 
        std::string type, key; 
        iss >> type >> key;
        Q.push(std::make_pair(google::protobuf::FieldDescriptor::CppType(std::stoi(type)), key));
    }
    parse_key(message, Q, key);
}

int main(int argc, char **argv)
{
    TargetData target_data; 
    {
        target_data.set_version("1.0");
        target_data.set_major(1);
        target_data.set_minor(0);
        target_data.mutable_embedding_data()->set_float_data(3.14f);
        target_data.mutable_embedding_data()->set_bool_data(false);
    }

    for(int i = 1; i < argc; ++i)
    {
        std::string key; 
        parse_key(target_data, argv[i], key);
        std::cout << "key: " << key << std::endl;
    }
    return 1; 
}