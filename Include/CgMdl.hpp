#ifndef CG_MDL__HPP
#define CG_MDL__HPP

/*
* _________________________________________________
* |                MDL File Format                |
* |-----------------------------------------------|
* |    Type         |   Description               |
* |-----------------|-----------------------------|
* |    Header       |   Header 'MDL'              |
* |-----------------|-----------------------------|
* |    Block        |   Block 1                   |
* |-----------------|-----------------------------|
* |    Block        |   .....                     |
* |-----------------|-----------------------------|
* |    Block        |   Block N                   |
* |-----------------|-----------------------------|
* |    UInt32       |   End of File 'EOF'         |
* |_________________|_____________________________|
*
* Header
* _________________________________________________
* |                MDL Header Format              |
* |-----------------------------------------------|
* |    Type         |  Description                |
* |-----------------|-----------------------------|
* |    Uint32       |  Signature 'MDL'            |
* |-----------------|-----------------------------|
* |    Uint32       |  Version                    |
* |-----------------|-----------------------------|
* |    Uint32[6]    |  Reserved                   |
* |_________________|_____________________________|
* 
* _________________________________________________
* |                MDL String Format              |
* |-----------------------------------------------|
* |    Type         |  Description                |
* |-----------------|-----------------------------|
* |    UInt32       |  String Signature 'STR'     |
* |-----------------|-----------------------------|
* |    UInt8        |  Length                     |
* |-----------------|-----------------------------|
* |    char[]       |  Data                       |
* |_________________|_____________________________|
* * Note: The string is null terminated, and the size includes the terminator.
*
* _________________________________________________
* |                MDL Array Format               |
* |-----------------------------------------------|
* |    Type         |   Description               |
* |-----------------|-----------------------------|
* |    UInt64       |   Array Signature 'ARRAY'   |
* |-----------------|-----------------------------|
* |    UInt8        |   Type                      |
* |-----------------|-----------------------------|
* |    UInt16       |   Length                    |
* |-----------------|-----------------------------|
* |               Data                            |
* |-----------------|-----------------------------|
* |    UInt32       |   End of data 'END'         |
* |_________________|_____________________________|
*
* _________________________________________________
* |                MDL Matrix4F                   |
* |-----------------------------------------------|
* |    Type         |   Description               |
* |-----------------|-----------------------------|
* |    UInt8        |   Signature 'MX'            |
* |-----------------|-----------------------------|
* |    Float[16]    |   Data                      |
* |-----------------|-----------------------------|
* |    UInt32       |   End of data 'END'         |
* |_________________|_____________________________|
*
* _________________________________________________
* |           MDL Node Data Block Format          |
* |-----------------------------------------------|
* |    Type         |   Description               |
* |-----------------|-----------------------------|
* |    UInt64       |   Block Signature 'BLOCK'   |
* |-----------------|-----------------------------|
* |    MDL_Array    |   Nodes                     |
* |-----------------|-----------------------------|
* |    MDL_Array    |   Bones                     |
* |-----------------|-----------------------------|
* |    UInt32       |   End of data 'END'         |
* |_________________|_____________________________|
*
* _________________________________________________
* |           MDL Material Data Block Format      |
* |-----------------------------------------------|
* |    Type         |   Description               |
* |-----------------|-----------------------------|
* |    UInt64       |   Block Signature 'BLOCK'   |
* |-----------------|-----------------------------|
* |    MDL_String   |   Texture                   |
* |-----------------|-----------------------------|
* |    UInt8        |   End of data 'END'         |
* |_________________|_____________________________|
*
* _________________________________________________
* |           MDL Mesh Data Block Format          |
* |-----------------------------------------------|
* |    Type         |   Description               |
* |-----------------|-----------------------------|
* |    UInt64       |   Block Signature 'BLOCK'   |
* |-----------------|-----------------------------|
* |    MDL_Array    |   Vertices                  |
* |-----------------|-----------------------------|
* |    MDL_Array    |   Mesh Data                 |
* |-----------------|-----------------------------|
* |    UInt32       |   End of data 'END'         |
* |_________________|_____________________________|
*
* _________________________________________________
* |                MDL Node Format                |
* |-----------------------------------------------|
* |    Type         |   Description               |
* |-----------------|-----------------------------|
* |    UInt32       |   Node Signature 'NODE'     |
* |-----------------|-----------------------------|
* |    MDL_String   |   Name                      |
* |-----------------|-----------------------------|
* |    MDL_String   |   Parent                    |
* |-----------------|-----------------------------|
* |    MDL_Matrix4F |   Transform                 |
* |-----------------|-----------------------------|
* |    UInt32       |   End of data 'END'         |
* |_________________|_____________________________|
*
* _________________________________________________
* |                MDL Bone Format                |
* |-----------------------------------------------|
* |    Type         |   Description               |
* |-----------------|-----------------------------|
* |    UInt32       |   Node Signature 'BONE'     |
* |-----------------|-----------------------------|
* |    MDL_String   |   Name                      |
* |-----------------|-----------------------------|
* |    MDL_Matrix4F |   Offset matrix             |
* |-----------------|-----------------------------|
* |    UInt32       |   End of data 'END'         |
* |_________________|_____________________________|
*
* _________________________________________________
* |                MDL Vertex Format              |
* |-----------------------------------------------|
* |    Type         |  Description                |
* |-----------------|-----------------------------|
* |    UInt16       |  Vertex Signature 'VX'      |
* |-----------------|-----------------------------|
* |    float[3]     |  Position                   |
* |-----------------|-----------------------------|
* |    float[3]     |  Normal                     |
* |-----------------|-----------------------------|
* |    float[2]     |  UV                         |
* |-----------------|-----------------------------|
* |    Uint8        |  Node index                 |
* |-----------------|-----------------------------|
* |    Uint8        |  Bone count                 |
* |-----------------|-----------------------------|
* |    Uint8[4]     |  Bone indices               |
* |-----------------|-----------------------------|
* |    float[4]     |  Bone weights               |
* |_________________|_____________________________|
*
* _________________________________________________
* |                MDL Mesh Format                |
* |-----------------------------------------------|
* |    Type         |   Description               |
* |-----------------|-----------------------------|
* |    UInt32       |   Mesh Signature 'MESH'     |
* |-----------------|-----------------------------|
* |    MDL_String   |   Name                      |
* |-----------------|-----------------------------|
* |    MDL_Array    |   Indices                   |
* |-----------------|-----------------------------|
* |    UInt32       |   End of data 'END'         |
* |_________________|_____________________________|
*
*/

#include <stdint.h>

enum
{
	MDL_SIG    = 0x00000000004C444D, // 'MDL'
	MDL_EOF    = 0x0000000000464F45, // 'EOF'
	MDL_ARRAY  = 0x0000005941525241, // 'ARRAY'
	MDL_BLOCK  = 0x0000004B434F4C42, // 'BLOCK'
	MDL_VERTEX = 0x0000000000005856, // 'VX'
	MDL_STRING = 0x0000000000525453, // 'STR'
	MDL_MATRIX = 0x000000000000584D, // 'MX'
	MDL_BONE   = 0x00000000454E4F42, // 'BONE'
	MDL_NODE   = 0x0000000045444F4E, // 'NODE'
	MDL_END    = 0x0000000000444E45  // 'END'
};

enum MDL_BLOCK_TYPE
{
	MDL_INVALID_BLOCK  = 0x00000000, // INVALID
	MDL_NODE_BLOCK     = 0x45444F4E, // 'NODE'
	MDL_MATERIAL_BLOCK = 0x004C544D, // 'MTL'
	MDL_MESH_BLOCK     = 0x4853454D  // 'MESH'
};

struct MDL_HEADER
{
	uint32_t signature;
	uint32_t version;
	uint32_t reserved[6];
};

struct MDL_BLOCK
{
	uint64_t signature;
	uint8_t  type;
	uint16_t reserved;
};

struct MDL_ARRAY
{
	uint64_t signature;
	uint8_t  type;
	uint32_t length;
};

struct MDL_VERTEX
{
	uint8_t signature;
	float   position[3];
	float   normal[3];
	float   uv[2];
	uint8_t node_index;
	uint8_t bone_count;
	uint8_t bone_indices[4];
	float   bone_weights[4];
};

struct MDL_STRING
{
	uint32_t signature;
	uint8_t  length;
	char     data[];
};

struct MDL_MATRIX
{
	uint8_t signature;
};

#endif // CG_MDL__HPP