/*
 * Rayman2 Mod Loader.
 * Rayman2 structures
 */

#ifndef RAYMAN2MODLOADER_STRUCTS_H
#define RAYMAN2MODLOADER_STRUCTS_H
#include <math.h>
#pragma pack(push, 1)

struct tdstEngineObject;
struct tdstState_;
struct stVaporAnimData;
struct tdstFrame3d;
struct tdstComport_;
struct struct_entryStruct;
struct tdstGetSetParam_;
struct tdstSectInfo_;
struct struct_CollSet;
struct WP_tdstGraphNode_;

struct Vector2
{
    float x;
    float y;

    Vector2() : x(0), y(0) { }
    Vector2(float _x, float _y) : x(_x), y(_y) { }
    Vector2(const Vector2& v) : x(v.x), y(v.y) { }

    Vector2 operator + (const Vector2& v) {
        return Vector2(this->x + v.x, this->y + v.y);
    }

    Vector2 operator - (const Vector2& v) {
        return Vector2(this->x - v.x, this->y - v.y);
    }

    float& operator [] (std::size_t i) {
        return *((float*)this + i);
    }

    float length() {
        return sqrtf(this->x * this->x + this->y * this->y);
    }
};

struct Vector3
{
    float x;
    float y;
    float z;

    Vector3() : x(0), y(0), z(0) { }
    Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) { }
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) { }

    Vector3 operator + (const Vector3& v) {
        return Vector3(this->x + v.x, this->y + v.y, this->z + v.z);
    }

    Vector3 operator - (const Vector3& v) {
        return Vector3(this->x - v.x, this->y - v.y, this->z - v.z);
    }

    float& operator [] (std::size_t i) {
        return *((float*)this + i);
    }

    float length() {
        return sqrtf(this->x * this->x + this->y * this->y + this->z * this->z);
    }
};

struct Matrix {
    Sint32 transformationType;
    float x;
    float y;
    float z;
    float scaleX;
    float skewY1;
    float skewZ1;
    float skewX1;
    float scaleY;
    float skewZ2;
    float skewX2;
    float skewY2;
    float scaleZ;
    float t4_scaleX;
    float t4_skewY1;
    float t4_skewZ1;
    float t4_skewX1;
    float t4_scaleY;
    float t4_skewZ2;
    float t4_skewX2;
    float t4_skewY2;
};

struct Matrix_DYN
{
    double d_0_0;
    double d_1_0;
    double d_2_0;
    double d_3_0;
    double d_0_1;
    double d_1_1;
    double d_2_1;
    double d_3_1;
    double d_0_2;
    double d_1_2;
    double d_2_2;
    double d_3_2;
    double d_0_3;
    double d_1_3;
    double d_2_3;
    double d_3_3;
};

struct Quaternion
{
    float x;
    float y;
    float z;
    float w;
};

struct Text2D
{
    const char* text;
    float positionX;
    float positionY;
    float size;
    __byte alphaByte;
    __byte gap11;
    __byte highlight;
    __byte options; // bit 4 = highlighting color
    int dword14;
    __byte flag3;
};

struct TextureData
{
    Uint32 field0;
    Uint16 field4;
    Uint16 field6;
    void* tempBuffer;
    Uint32 fieldC;
    Uint32 field10;
    Uint32 flags;
    Uint16 height_;
    Uint16 width_;
    Uint16 height;
    Uint16 width;
    Uint32 currentScrollX;
    Uint32 currentScrollY;
    Uint32 textureScrollingEnabled;
    Uint32 alphaMask;
    Uint32 field30;
    Uint32 field34;
    Uint32 field38;
    Uint32 field3C;
    Uint32 field40;
    __byte field44;
    __byte flags__byte;
};

struct SNAFileStruct
{
    char field_0;
    char field_1;
    char field_2;
    char field_3;
};

struct SNAPointers
{
    char gap_0[4];
    int anonymous_0;
    int anonymous_1;
    int anonymous_2;
    void* anonymous_3;
    void* anonymous_4;
    void* anonymous_5;
    void* anonymous_6;
    int anonymous_7;
    void* anonymous_8;
    void* anonymous_9;
    int anonymous_10;
    int anonymous_11;
    void* anonymous_12;
    void* anonymous_13;
    void* anonymous_14;
    int anonymous_15;
    void* anonymous_16;
    int anonymous_17;
    int anonymous_18;
    int anonymous_19;
    int anonymous_20;
    int anonymous_21;
    int anonymous_22;
};

struct SoundBank
{
    int field_0;
    int id;
    int eventCount;
    int dataPart;
    int field_10;
    int field_14;
    int field_18;
    int field_1C;
    int loadState;
    int entireDataPointer;
    int field_28;
    int field_2C;
    int field_30;
    int field_34;
};

struct struct_fileHandle
{
    int readFunc;
    int noError;
    Uint32 dword8;
    __byte byteC;
    __byte fD[3];
    Uint32 dword10;
    int magic;
    int field_18;
    int field_1C;
    int field_20;
    int(__cdecl* Read)(const void*, int, int);
};

struct struct_dataPointer
{
    Uint32 dword0;
    Uint32 dword4;
    Uint32 dword8;
    __byte byteC;
    __declspec(align(4)) Uint32 dword10;
    Uint32 dword14;
    Uint32 dword18;
    Uint32 dword1C;
    Uint32 dword20;
    Uint32 dword24;
};

struct BNM_Header
{
    int field_0;
    int field_4;
    int field_8;
    int field_C;
    int field_10;
    int size1;
    int size2;
    int field_1C;
    int field_20;
    int field_24;
    int field_28;
};

struct __declspec(align(2)) BNM_FileEntry
{
    Uint32 dword0;
    Uint32 type;
    Uint32 dword8;
    int length;
    Uint32 dword10;
    Uint32 dword14;
    Uint32 dword18;
    Uint32 dword1C;
    Uint32 dword20;
    Uint32 dword24;
    int field_28;
    int field_2C;
    int field_30;
    int field_34;
    int sampleRate;
    char name[20];
    int field_50;
};

struct LEVELS0DAT_Header
{
    int field_0;
    int field_4;
    int field_8;
    int field_C;
};

struct GliTexture
{
    __byte something1_2[8];
    Uint32 something3;
    __byte something4_5[8];
    Uint32 something6;
    Uint16 word18;
    Uint16 word1A;
    Uint16 word1C;
    Uint16 word1E;
    __byte gap20[12];
    Uint32 dword2C;
    __byte gap30[21];
    __byte byte45;
    char textureFilename[130];
};

struct struct_fixFileObject
{
    __byte gap0[8];
    struct_fileHandle* openedFileHandle;
};

struct EngineStructure
{
    LEVEL_STATE engineMode;
    char field_1;
    char field_2;
    char field_3;
    int field_4;
    int field_8;
    int field_C;
    int field_10;
    int field_14;
    int field_18;
    int levelName;
    int field_20;
    int field_23;
    int field_27;
    int field_2B;
    int field_2F;
    int field_33;
    int field_37;
    int field_3B;
    int field_3F;
    int field_43;
    int field_47;
    int field_4B;
    int field_4F;
    int field_53;
    int field_57;
    int field_5B;
    int field_5F;
    int field_63;
    int field_67;
    int ago_timer;
    int field_6F;
    int field_73;
    int field_77;
    int field_7B;
    int field_7F;
    int field_83;
    int field_87;
    int field_8B;
    int field_8F;
    int field_93;
    int field_97;
    int field_9B;
    int field_9F;
    int field_A3;
    int field_A7;
    int field_AB;
    int field_AF;
    int field_B3;
    int field_B7;
    int field_BB;
    int field_BF;
    int field_C3;
    int field_C7;
    int field_CB;
    int field_CF;
    int field_D3;
    int field_D7;
    int field_DB;
    int field_DF;
    int field_E3;
    int field_E7;
    int field_EB;
    int field_EF;
    int field_F3;
    int field_F7;
    int field_FB;
    int field_FF;
    int field_103;
};

struct Entity1
{
    int field_0;
    int field_4;
    int field_8;
    int field_C;
    int field_10;
    int field_14;
    int field_18;
    int field_1C;
    int field_20;
    int field_24;
    int field_28;
    int field_2C;
    int field_30;
    int field_34;
    int field_38;
    int field_3C;
    int field_40;
    int field_44;
    int field_48;
    int field_4C;
    int field_50;
    int field_54;
    int field_58;
    int field_5C;
    int field_60;
    int field_64;
    int field_68;
    int field_6C;
    int field_70;
    int field_74;
    int field_78;
    int field_7C;
    int field_80;
    int field_84;
    int field_88;
    int field_8C;
    int allocatedIfZero;
    int field_94;
    int field_98;
    int field_9C;
    int field_A0;
    int field_A4;
    int field_A8;
    int field_AC;
    int field_B0;
    int field_B4;
    int field_B8;
    int field_BC;
    int field_C0;
    int field_C4;
    int field_C8;
    int field_CC;
    int field_D0;
    int field_D4;
    int field_D8;
    int field_DC;
    int desinit;
    int field_E4;
    int field_E8;
    int field_EC;
    int field_F0;
    int field_F4;
    int field_F8;
    int field_FC;
    int field_100;
    int field_104;
    int field_108;
    int field_10C;
    int field_110;
    int field_114;
    int field_118;
    int field_11C;
    int field_120;
    int field_124;
    int field_128;
    int field_12C;
    int field_130;
    int field_134;
    int field_138;
    int field_13C;
    int field_140;
    int field_144;
    int field_148;
    int field_14C;
};

struct Entity2
{
    int someSuperObject;
    int field_4;
    int field_8;
    int field_C;
    int field_10;
    int field_14;
    int field_18;
    int field_1C;
    int field_20;
    int field_24;
    int field_28;
    int field_2C;
    int field_30;
    int field_34;
    int field_38;
    int field_3C;
    int field_40;
    int field_44;
    int field_48;
    int field_4C;
    int field_50;
    int field_54;
};

struct tdstDynam_
{
    __byte gap0[336];
    Uint32 dword150;
    int field_154;
    int field_158;
    int field_15C;
    int field_160;
    int field_164;
    int field_168;
    int field_16C;
    int field_170;
    int field_174;
    int field_178;
    int field_17C;
    int field_180;
    int field_184;
    int field_188;
    int field_18C;
    int field_190;
    int field_194;
    int field_198;
    int field_19C;
    int field_1A0;
    int field_1A4;
    int field_1A8;
    int field_1AC;
    int field_1B0;
    int field_1B4;
    int field_1B8;
    int field_1BC;
    int field_1C0;
    int field_1C4;
    int field_1C8;
    int field_1CC;
    int field_1D0;
    int field_1D4;
    int field_1D8;
    int field_1DC;
    int field_1E0;
    int field_1E4;
    int field_1E8;
    int field_1EC;
    int field_1F0;
    int field_1F4;
    int field_1F8;
    int field_1FC;
};

struct tdstAnim3d_
{
    __int16 maxFrame;
    char field_2;
    char field_3;
    char field_4;
    char field_5;
    char field_6;
    char field_7;
    int field_8;
    int field_C;
    int field_10;
    int dword14;
    __int16 offset;
    __int16 field_1A;
    int field_1C;
    int field_20;
    int field_24;
    int field_28;
    int field_2C;
    int field_30;
    int field_34;
    int field_38;
    int field_3C;
    int field_40;
    int field_44;
    int field_48;
    int field_4C;
    int field_50;
    int field_54;
    int field_58;
    int field_5C;
    int field_60;
    int field_64;
};

struct BoundingVolume
{
    float field_0;
    float field_4;
    float field_8;
    float field_C;
    float field_10;
    float field_14;
    float field_18;
    float field_1C;
};

struct HIE_tdstSuperObject
{
    SuperObjectType type;
    tdstEngineObject* engineObject;
    HIE_tdstSuperObject* firstChild;
    HIE_tdstSuperObject* nextChild;
    int childCounter;
    HIE_tdstSuperObject* nextBrother;
    HIE_tdstSuperObject* prevBrother;
    HIE_tdstSuperObject* father;
    Matrix* mainMatrix;
    Matrix* otherMatrix;
    int field_28;
    int someRenderField;
    int renderBits;
    BoundingVolume* boundingVolume;
    Uint32 field_38;
    int field_3C;
    int field_40;
    int field_44;
    Uint32 field_48;
    Uint32 field_4C;
    Uint32 field_50;
    Uint32 field_54;
    Uint32 field_58;
};

struct tdst3dData_
{
    HIE_tdstSuperObject* someSuperObject;
    tdstState_* animState;
    tdstState_* anotherState;
    int field_C;
    Uint32 dword10;
    int dword14;
    int field_18;
    int field_1C;
    int field_20;
    int field_24;
    int field_28;
    int field_2C;
    int field_30;
    int field_34;
    int field_38;
    int field_3C;
    int field_40;
    int field_44;
    int makesInvisible;
    int field_4C;
    int field_50;
    int field_54;
    int field_58;
    int field_5C;
    int field_60;
    int field_64;
    int field_68;
    int field_6C;
    int field_70;
    Uint16 currentFrame;
    __byte somethingSound1;
    char somethingSound2;
    Uint32 dword78;
    __byte gap7C[12];
    tdstState_* newAnimState;
    Uint16 word8C;
    __byte byte8E;
    char field_8F;
    stVaporAnimData** animObjectsDataArray;
    int allocateSize;
    HIE_tdstSuperObject* bananaSector;
    tdstFrame3d** monkeyFrame;
    int field_A0;
    int field_A4;
    int field_A8;
    int field_AC;
    int field_B0;
    int field_B4;
    int field_B8;
    Uint32 dwordBC;
    Uint32 dwordC0;
    Uint32 dwordC4;
    Uint16 wordC8;
    __byte byteCA;
    __byte gapCB[21];
    __byte framerate;
    __byte byteE1;
    int field_E2;
    int field_E6;
    int field_EA;
    int field_EE;
    int field_F2;
    int field_F6;
    int field_FA;
    int canNotComputeBrain;
    int field_102;
    int field_106;
    int field_10A;
    int field_10E;
    int field_112;
    int field_116;
    int field_11A;
};

struct tdstIntelligence_
{
    int field_0;
    tdst3dData_* renderInfo;
    tdstComport_* comport;
    int oldComport;
    struct_entryStruct* ruleStruct;
    tdstGetSetParam_* newComport;
    int field_18;
    int field_1C;
    int field_20;
    int field_24;
    int field_28;
    int field_2C_comparisonType;
    int field_30;
};

struct AI_tdstMind_
{
    __byte gap0[4];
    tdstIntelligence_* comport_intelligence;
    tdstIntelligence_* intelligence_reflex;
};

struct SOStandardGameStruct
{
    int field_0;
    int field_4;
    int personalType;
    HIE_tdstSuperObject* superObject;
    int field_10;
    int field_14;
    int field_18;
    int field_1C;
    int field_20;
    int customBits;
    int moreCustomBits;
    int field_2C;
    int field_30;
    int field_34;
    int field_38;
    int field_3C;
    int field_40;
    int field_44;
    int field_48;
    int field_4C;
    int field_50;
    int field_54;
    int field_58;
};

struct tdstEngineObject
{
    tdst3dData_* p3dData;
    SOStandardGameStruct* standardGameStruct;
    tdstSectInfo_* dynam;
    AI_tdstMind_* mind;
    int isCamera;
    struct_CollSet* collset;
    int field_18;
    int lightData;
    HIE_tdstSuperObject* activeSector;
    int field_24;
    int field_28;
    int field_2C;
    int field_30;
    int field_34;
    int field_38;
    int field_3C;
    int field_40;
    int field_44;
    int field_48;
    int field_4C;
    int field_50;
    int field_54;
    int field_58;
    int field_5C;
};

struct tdstState_
{
    tdst3dData_* some3dData;
    tdstAnim3d_* anim3d;
    int field_8;
    int field_C;
    int field_10;
    int field_14;
    int field_18;
    int field_1C;
    tdstState_* nextState;
    int MechanicsIdCard;
    char field_28;
    __byte stateSpeed;
    char field_2A;
    char field_2B;
    int field_2C;
    int field_30;
    int field_34;
    int field_38;
    int field_3C;
    int field_40;
};

struct stSubVape
{
    HIE_tdstSuperObject* superObject;
    int gap4;
    int field_8;
    int field_C;
    int byte10;
    int field_14;
};

struct stVaporAnimData
{
    stSubVape* subVape;
    int field_4;
    int field_8;
    int field_C;
    int field_10;
    int field_14;
    int field_18;
    int field_1C;
    int field_20;
    int field_24;
    int field_28;
    int field_2C;
    int field_30;
};

struct stHierarchy
{
    int mask;
    int var1;
    int var2;
};

struct __declspec(align(1)) tdstFrame3d
{
    tdstAnim3d_* probablyFramePtr;
    Matrix* matrix;
    Vector3* movementSpeed;
    Uint32 dwordC;
    stHierarchy* hierarchy;
    tdstAnim3d_* anim3d;
    Uint16 frameNumber;
    __byte importantFlag;
};

struct tdstNodeInterpret_
{
    int tableIndex;
    char field_4;
    char field_5;
    char param;
    char functionType;
};

struct tdstGetSetParam_
{
    int field1;
    tdstNodeInterpret_* field2;
    int field3;
    Uint32 field4_DataType;
    int field5;
    int field6;
    int field7;
    int field8_paramTypes;
};

struct tdstComport_
{
    int a1;
    tdstEngineObject* engineObject;
    int field_8;
    int field_C;
};

struct struct_entryStruct
{
    struct_entryStruct* entryStruct;
    char maxIndex;
    __byte usedActions;
    char field_6;
    char field_7;
    int field_8;
    int field_C;
    int field_10;
    int field_14;
    int field_18;
    int field_1C;
    int field_20;
    int field_24;
    int field_28;
    int field_2C;
    int field_30;
    int field_34;
    int field_38;
    int field_3C;
    int field_40;
    int field_44;
    int field_48;
    int field_4C;
    int field_50;
    int field_54;
    int field_58;
    int field_5C;
    int field_60;
    char field_64;
    char ruleAddress;
    char defaultActionReturn;
    char newActionReturn;
    int field_68;
    int field_6C;
    int field_70;
    int field_74;
};

struct struct_CollSet
{
    int field_0;
    int field_4;
    int field_8;
    int field_C;
    int field_10;
    int field_14;
    int field_18;
    int field_1C;
    int field_20;
    int field_24;
    int field_28;
    int field_2C;
    int field_30;
    int field_34;
    int field_38;
    int field_3C;
    int isAPlatform;
    int field_44;
    int field_48;
    int field_4C;
    int field_50;
};

struct tdstSectInfo_
{
    HIE_tdstSuperObject* currentSector;
    Entity2* radiosityOrEntity;
    void* lightType;
    char unknown[84];
    int minPointInBorder;
    char unknown2[8];
    int maxPointInBorder;
};

struct Sector
{
    DWORD type;
    tdstSectInfo_* info0;
    Sector* firstChild;
    BYTE unknown2[8];
    Sector* nextTwin;
    char unknown3[20];
    int someShit;
};

struct struct_DnmReportEntry
{
    DWORD field_0;
    int field_4;
    int field_8;
    int field_C;
    int field_10;
    int field_14;
    int field_18;
    int field_1C;
    int field_20;
    int field_24;
};

struct struct_DnmReport
{
    int flags_0;
    int flags_1;
    struct_DnmReportEntry entry_08_default;
    struct_DnmReportEntry entry_30_floor;
    struct_DnmReportEntry entry_58_wall;
    struct_DnmReportEntry entry_80_platform;
    struct_DnmReportEntry entry_A8_swim;
    struct_DnmReportEntry entry_D0_gi;
    int field_F8;
    int field_FC;
    int field_100;
    int field_104;
    int field_108;
    int field_10C;
    int field_110;
    int field_114;
    int field_118;
    int field_11C;
    int field_120;
    int field_124;
    int field_128;
    int field_12C;
    int field_130;
    int field_134;
    int field_138;
    int field_13C;
    int field_140;
    int field_144;
    int field_148;
    int field_14C;
    int field_150;
    int field_154;
    int field_158;
    int field_15C;
    int field_160;
    int field_164;
    int field_168;
};

struct DNMHangingSettings
{
    int hangstuffstruct;
    int field_4;
    int field_8;
    int field_C;
    int field_10;
    int field_14;
    int field_18;
    int field_1C;
    int field_20;
    int field_24;
    int field_28;
    int field_2C;
    int field_30;
    int field_34;
    int field_38;
};

struct __declspec(align(8)) DNM_stDynamics
{
    __int64 f0_counter;
    int stateFlags1;
    int stateFlags2;
    int gravity;
    int field_14;
    int field_18;
    float maxrebound;
    float slideWhenStateBit7IsSet;
    int field_24;
    int field_28;
    int field_2C;
    int field_30;
    int field_34;
    int field_38;
    float float3C;
    float float40;
    float* pfloat44;
    float scaleX;
    float scaleY;
    float scaleZ;
    float speedVector;
    float float58;
    float float5C;
    int gap60;
    int field_64;
    int field_68;
    float float6C;
    float float70;
    float float74;
    Vector3* startMatrixA;
    Vector3 position_7C;
    int field_88;
    int field_8C;
    int field_90;
    int field_94;
    int field_98;
    int field_9C;
    int field_A0;
    int field_A4;
    int field_A8;
    int field_AC;
    int field_B0;
    int field_B4;
    int field_B8;
    int field_BC;
    int field_C0;
    int field_C4;
    int field_C8;
    int field_CC;
    Matrix* startMatrixB;
    Vector3 position_D4;
    int field_E0;
    int field_E4;
    int field_E8;
    int field_EC;
    int field_F0;
    int field_F4;
    int field_F8;
    int field_FC;
    int field_100;
    int field_104;
    int field_108;
    int field_10C;
    int field_110;
    int field_114;
    int field_118;
    int field_11C;
    int field_120;
    int field_124;
    Uint32 dword128;
    Uint32 dword12C;
    Uint32 dword130;
    Uint32 dword134;
    Uint32 dword138;
    Uint32 dword13C;
    Uint32 dword140;
    Uint32 dword144;
    Uint32 dword148;
    int field_14C;
    struct_DnmReport* report;
    int inertX;
    int inertY;
    int inertZ;
    float streamPriority;
    int streamFactor;
    int field_168;
    int field_16C;
    int field_170;
    int field_174;
    int field_178_inertiamax;
    int field_17C_inertiamax;
    int field_180_intertiamax;
    int field_184;
    int field_188;
    int field_18C;
    int field_190;
    int field_194;
    int field_198;
    int field_19C;
    int field_1A0;
    int field_1A4;
    float posX;
    Uint32 posY;
    Uint32 posZ;
    int gap1B4;
    int field_1B8;
    int field_1BC;
    int field_1C0;
    int field_1C4;
    int field_1C8;
    int field_1CC;
    int field_1D0;
    int field_1D4;
    char computeFrequency;
    char field_1D9;
    char field_1DA;
    char field_1DB;
    int tiltIntensity;
    int tiltInertia;
    int tiltOrigin;
    int field_1E8;
    int field_1EC;
    int field_1F0;
    int field_1F4;
    int field_1F8;
    int field_1FC;
    int field_200;
    int field_204;
    int field_208;
    int field_20C;
    int field_210;
    int field_214;
    int field_218;
    int field_21C;
    int field_220;
    int field_224;
    int field_228;
    int field_22C;
    int field_230;
    int field_234;
    int field_238;
    int field_23C;
    int field_240;
    int field_244;
    int field_248;
    int field_24C;
    int field_250;
    int field_254;
    int field_258;
    int field_25C;
    int field_260;
    int field_264;
    int field_268;
    int field_26C;
    int field_270;
    int field_274;
    int field_278;
    int field_27C;
    int field_280;
    DNMHangingSettings defaultSettings;
    int field_2C0;
    int field_2C4;
    int field_2C8;
    int field_2CC;
    int field_2D0;
    int field_2D4;
    int field_2D8;
    int field_2DC;
    int field_2E0;
    int field_2E4;
    int field_2E8;
    int field_2EC;
    int field_2F0;
    int field_2F4;
    int field_2F8;
    int field_2FC;
    int field_300;
    int field_304;
    int field_308;
    int field_30C;
    int field_310;
    int field_314;
    int field_318;
    int field_31C;
    int field_320;
    int field_324;
    int field_328;
    int field_32C;
    int field_330;
    int field_334;
    int field_338;
    int field_33C;
    int field_340;
    int field_344;
    int field_348;
    int field_34C;
    int field_350;
    int field_354;
    int field_358;
    int field_35C;
    int field_360;
    int field_364;
    int field_368;
    int field_36C;
    int field_370;
    int field_374;
    int field_378;
    int field_37C;
    int field_380;
    int field_384;
    int field_388;
    int field_38C;
    int field_390;
    int field_394;
    int field_398;
    int field_39C;
    int field_3A0;
    int field_3A4;
    int field_3A8;
    int field_3AC;
    int field_3B0;
    int field_3B4;
    int field_3B8;
    int field_3BC;
    int field_3C0;
    int field_3C4;
    int field_3C8;
    int field_3CC;
    int field_3D0;
    int field_3D4;
    int field_3D8;
    int field_3DC;
    int field_3E0;
    int field_3E4;
    int field_3E8;
    int field_3EC;
    int field_3F0;
    int field_3F4;
    int field_3F8;
    int field_3FC;
    int field_400;
    int field_404;
    int field_408;
    int field_40C;
    int field_410;
    int field_414;
    int field_418;
    int field_41C;
    int field_420;
    int field_424;
    int field_428;
    int field_42C;
    int field_430;
    int field_434;
    int field_438;
    int field_43C;
    int field_440;
    int field_444;
    int field_448;
    int field_44C;
    int field_450;
    int field_454;
    int field_458;
    int field_45C;
    int field_460;
    int field_464;
    int field_468;
    int field_46C;
    int field_470;
    int field_474;
    int field_478;
    int field_47C;
    int field_480;
    int field_484;
    int field_488;
    int field_48C;
    int field_490;
    int field_494;
    int field_498;
    int field_49C;
    int field_4A0;
    int field_4A4;
    int field_4A8;
    int field_4AC;
    int field_4B0;
    int field_4B4;
    int field_4B8;
    int field_4BC;
    int field_4C0;
    int field_4C4;
    int field_4C8;
    int field_4CC;
    int field_4D0;
    int field_4D4;
    int field_4D8;
    int field_4DC;
    int field_4E0;
    int field_4E4;
    int field_4E8;
    int field_4EC;
    int field_4F0;
    int field_4F4;
    int field_4F8;
    int field_4FC;
    __byte gap500[112];
    char String1[4];
    int field_574;
    int field_578;
    int field_57C;
    int field_580;
    int field_584;
    int field_588;
    int field_58C;
    int field_590;
    int field_594;
    int field_598;
    int field_59C;
    int field_5A0;
    char String2[4];
    int field_5A8;
    int field_5AC;
    int field_5B0;
    int field_5B4;
    int field_5B8;
    int field_5BC;
    int field_5C0;
    int field_5C4;
    int field_5C8;
    char String3[4];
    int field_5D0;
};

struct StandardGame
{
    
};

struct SuperObjectInfo
{
    int lightInfo;
    StandardGame* standardGame;
    int sectorInfo;
    int AIPointer;
    int isCamera;
};

struct SuperObject
{
    int type;
    SuperObjectInfo* info;
    SuperObject* firstChild;
    SuperObject* nextChild;
    int something;
    SuperObject* nextBrother;
    SuperObject* prevBrother;
    SuperObject* father;
    Matrix* matrix;
    Matrix* matrix2;
};

typedef struct 
{
    float x;
    float y;
    float z;
    int field_C;
    __int16 field_10;
    float radius;
    char isDynamic;
    char field_17;
} WP_tdstWayPoint_;

struct WP_tdstGraph_
{
    WP_tdstGraphNode_* firstGraphNode;
    int field_4;
    int nodeCount;
    int field_C;
};

struct struct_Arc
{
    int test;
    Uint32 dword4;
    Uint32 dword8;
    Uint32 graphNode;
    Uint32 nodeFrom;
    Uint32 nodeTo;
    Uint32 dword18;
    Uint32 dword1C;
};

struct WP_tdstGraphNode_
{
    WP_tdstGraphNode_* nextGraphNode;
    WP_tdstGraphNode_* previousGraphNode;
    WP_tdstGraph_* graph;
    WP_tdstWayPoint_* waypoint;
    int field_10;
    int field_14;
    struct_Arc* arcList;
    int field_1C;
    int field_20;
    int field_24;
    int field_28;
};

struct WP_tdstListOfArc_
{
    WP_tdstGraphNode_* firstNode;
    Uint32 dword4;
    Uint32 dword8;
};

struct __declspec(align(2)) tdstKeyFrame_
{
    int gap0;
    int field_4;
    int field_8;
    float floatC;
    __int16 gap10;
    __byte bitmask;
    int field_13;
    char field_17;
    Uint16 word18;
    Uint16 word1A;
    Uint16 word1C;
    Uint16 word1E;
    __int16 field_20;
    __int16 field_22;
    int field_24;
    int field_28;
    int field_2C;
    int field_30;
    __int16 field_34;
    __int16 field_36;
    int field_38;
    int field_3C;
    int field_40;
};

struct tdstChannel_
{
    __int16 gap0;
    __int16 subObjectIndex;
    Uint16 word4;
    __int16 field_6;
    int field_8;
    int field_C;
};

struct st_A3dGENERAL
{
    int gap0;
    int field_4;
    int field_8;
    Uint16 wordC;
    __int16 gapE;
    __int16 field_10;
    int field_12;
    __int16 field_16;
    Uint16 onlyFrameOffset_B;
    int gap1A;
    int field_1E;
    int field_22;
    int field_26;
    int field_2A;
    Uint16 onlyFrameOffset_A;
    __int16 channelIndex;
    __int16 field_32;
    int field_34;
};

struct stOnlyFrame
{
    Uint16 quaternionOffset;
    Uint16 vectorOffset;
    Uint16 word4;
    __int16 hierarchyOffset;
    __int16 finalField;
};

struct tdstEngineObject_Sector
{
    HIE_tdstSuperObject* superObjectList;
    SOStandardGameStruct* standardGameStruct;
    tdstSectInfo_* sectorInfo;
    int aiPointer;
    int isCamera;
    struct_CollSet* platformInfo;
    int field_18;
    int lightData;
    HIE_tdstSuperObject* activeSector;
    int field_24;
    int field_28;
    int field_2C;
    int field_30;
    int field_34;
    int field_38;
    int field_3C;
    int field_40;
    int field_44;
    int field_48;
    int field_4C;
    int field_50;
    int field_54;
    int field_58;
    int field_5C;
    int field_60;
    int field_64;
    int field_68;
    int field_6C;
    int field_70;
    int field_74;
    int field_78;
    int field_7C;
};

struct HIE_tdstSuperObject_Sector
{
    SuperObjectType type;
    tdstEngineObject_Sector* sectorEngineObject;
    HIE_tdstSuperObject* firstChild;
    HIE_tdstSuperObject* nextChild;
    int field_10;
    HIE_tdstSuperObject* nextBrother;
    HIE_tdstSuperObject* prevBrother;
    HIE_tdstSuperObject* father;
    Matrix* mainMatrix;
    Matrix* otherMatrix;
    int field_28;
    int someRenderField;
    int renderBits;
    int field_34;
    int field_38;
    int field_3C;
    int field_40;
    int field_44;
    int field_48;
    int field_4C;
    int field_50;
    int field_54;
    int field_58;
};

struct __declspec(align(2)) EngineObjectWrapper
{
    Uint32 dword0;
    tdstEngineObject* engineObject;
    __byte gap8[4];
    Uint16 wordC;
};

struct __declspec(align(2)) tdst3dData_Sector
{
    HIE_tdstSuperObject* someSuperObject;
    tdstState_* animState;
    tdstState_* anotherState;
    int field_C;
    Uint32 dword10;
    int gap14;
    int field_18;
    int field_1C;
    int field_20;
    int field_24;
    int field_28;
    int field_2C;
    int field_30;
    int field_34;
    int field_38;
    int field_3C;
    int field_40;
    int field_44;
    int makesInvisible;
    int field_4C;
    int field_50;
    int field_54;
    int field_58;
    int field_5C;
    int field_60;
    int field_64;
    int field_68;
    int field_6C;
    int field_70;
    Uint16 currentFrame;
    __byte somethingSound1;
    char somethingSound2;
    Uint32 dword78;
    __byte gap7C[12];
    tdstState_* newAnimState;
    Uint16 word8C;
    __byte byte8E;
    __byte gap8F[13];
    int dword9C;
    int field_A0;
    int field_A4;
    int field_A8;
    int field_AC;
    int field_B0;
    int field_B4;
    int field_B8;
    Uint32 dwordBC;
    Uint32 dwordC0;
    Uint32 dwordC4;
    Uint16 wordC8;
    __byte byteCA;
    __byte gapCB[21];
    __byte framerate;
    __byte byteE1;
    int field_E2;
    int field_E6;
    int field_EA;
    int field_EE;
    int field_F2;
    int field_F6;
    int field_FA;
    int canNotComputeBrain;
    int field_102;
    int field_106;
    int field_10A;
    int field_10E;
    int field_112;
    int field_116;
    int field_11A;
};

struct __declspec(align(16)) COL_tdstCollideObject_
{
    Uint32 dword0;
    int field_4;
    int field_8;
    int field_C;
    Uint32 dword10;
    int faces;
    int field_18;
    int field_1C;
    int field_20;
    int field_24;
    int field_28;
    int amountOfFaces;
    int field_30;
    int field_34;
    int field_38;
    int field_3C;
    int field_40;
    int field_44;
    int field_48;
    int field_4C;
    int field_50;
    int field_54;
    int field_58;
    int field_5C;
    int field_60;
    int field_64;
    int field_68;
    int field_6C;
    int field_70;
    int field_74;
    int field_78;
    int field_7C;
    int field_80;
    int field_84;
    int field_88;
    int field_8C;
    int field_90;
    int field_94;
};

struct collideObjectData
{
    int field_0;
    __int16 field_4;
    __declspec(align(4)) int field_8;
    __byte gapC[4];
    int field_16;
};

struct GMT_tdstGameMaterial_
{
    __byte gap0[12];
    Uint32 material;
};

struct __declspec(align(4)) struct_faceData
{
    GMT_tdstGameMaterial_* gameMaterial;
    Uint16 subFaceCount;
    __declspec(align(4)) Uint32 dword8;
    __byte gapC[4];
    Uint32 normals;
};

struct Model_0_3
{
    void* vertices;
    int unknownPointer2;
    int unknownPointer3;
    int unknown;
    int unknownPointer4;
    int model_0_4;
    char unknown2[22];
    __int16 subModelCount;
};

struct cameraParameters
{
    int field_0;
    __byte gap4[8];
    int field_12;
    __byte gap10[136];
    int field_152;
    int field_156;
    int field_160;
    __byte gapA4[4];
    int field_168;
    int field_172;
    int field_176;
    __byte gapB4[4];
    int field_184;
    int field_188;
    int field_192;
    __byte gapC4[4];
    int field_200;
    int field_204;
    int field_208;
};

struct GLI_BIG_GLOBALS
{
    void* perhapsEngineStruct;
    Model_0_3* mdl;
    int unknown0;
    int someFlag;
    int unknown1[46262];
    void* matrix;
};

struct tdstStandardGame_
{
    __byte gap0[12];
    HIE_tdstSuperObject* superObject_maybe;
    int field_10;
    HIE_tdstSuperObject* superObject;
};

struct OLDtdstEngineObject
{
    int mustBeTrue;
    tdstStandardGame_* standardGame;
};

struct __declspec(align(4)) struct_mechanicsIdCard
{
    int field0;
    __byte flags;
    __declspec(align(4)) int gravity;
    int maxRebound;
    int int10;
    int int14;
    int inertiaX;
    int inertiaY;
    int inertiaZ;
    int tiltIntensity;
    int tiltInertia;
    int tiltOrigin;
    Uint32 inertiaMaxX;
    Uint32 inertiaMaxY;
    Uint32 inertiaMaxZ;
};

struct struct_rendercontext
{
    __byte gap0[8];
    Uint32 dword8;
    Uint32 dwordC;
};

struct IPT_tdstEntryElement
{
    int gap0;
    int field_4;
    IPT_tdstEntryElement* nextEntry;
    Uint32 validCount;
    int field_10;
    int field_14;
};

struct struct_a1_3
{
    __byte f0[8];
    char str1[256];
    char str2[256];
    Uint32 dword8;
};

struct struct_a1_9
{
    __byte gap0[8];
    Uint32 word8;
};

struct struct_MecObstacle_Field28
{
    int field_0;
    int field_4;
    int field_8;
    int field_C;
    int field_10;
    int field_14;
    int field_18;
    int field_1C;
    int field_20;
};

struct DNM_stMecObstacle
{
    float radius;
    int field_4;
    int field_8;
    int field_C;
    int field_10;
    int field_14;
    int field_18;
    int field_1C;
    GMT_tdstGameMaterial_* gameMaterial;
    HIE_tdstSuperObject* superObject;
    struct_MecObstacle_Field28 field_28;
    int field_4C;
    int field_50;
    int field_54;
    float field_58;
    float slide;
    int field_60;
    int field_64;
    int field_68;
    int field_6C;
    int field_70;
    int field_74;
    int field_78;
    int field_7C;
    int field_80;
};

struct __declspec(align(1)) COL_tdstGVForCollision_
{
    int field_0;
    __byte gap4[572];
    int field_576;
    int field_580;
    int field_584;
    __byte gap24C[12];
    int field_600;
    int field_604;
    int field_608;
    int field_612;
    int field_616;
    int field_620;
    __byte gap270[68];
    int field_692;
    int field_696;
    char field_700;
};

struct __declspec(align(2)) struct_SAIlist
{
    __byte gap0[4];
    void* dest;
    const void* source;
    Uint32 num;
    Uint16 mode;
};

struct __declspec(align(2)) struct_g_p_stNextPtrRelocInfo
{
    Uint32 dword0;
    __byte byte4;
    __byte byte5;
};

#pragma pack(pop)
#endif