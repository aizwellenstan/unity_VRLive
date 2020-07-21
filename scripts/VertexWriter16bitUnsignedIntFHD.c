// csから渡される値
RWTexture2D<float4> OutPosition;
StructuredBuffer<float3> Pos;
int VertCount;
int ColumnOffset;

[numthreads(1,1,1)]
void CSMainFHD (uint3 id : SV_DispatchThreadID)
{
    // 
    // id.xはそのまま頂点ID
    // row = id.x % (TEX_WIDTH / 4) // 4はcolumnあたりのx方向の画素数
    // column = id.x / (TEX_WIDTH / 4)

    uint index = id.x;
    float3 pos = Pos[index];

    int TEX_WIDTH = 1920;
    uint row = index % (TEX_WIDTH / 4);
    uint column = index / (TEX_WIDTH/ 4) + ColumnOffset;

    uint posXMillimeter = (pos.x + 3.2767f) * 10000.0f;
    uint posYMillimeter = (pos.y + 3.2767f) * 10000.0f;
    uint posZMillimeter = (pos.z + 3.2767f) * 10000.0f;

    //pos.x1
    OutPosition[uint2(row * 4 + 0, column * 6 + 0)] = oddBitOfUintTo8bitBrightness(posXMillimeter);
    OutPosition[uint2(row * 4 + 0, column * 6 + 1)] = oddBitOfUintTo8bitBrightness(posXMillimeter);
    OutPosition[uint2(row * 4 + 1, column * 6 + 0)] = oddBitOfUintTo8bitBrightness(posXMillimeter);
    OutPosition[uint2(row * 4 + 1, column * 6 + 1)] = oddBitOfUintTo8bitBrightness(posXMillimeter);

    //pos.x2
    OutPosition[uint2(row * 4 + 2, column * 6 + 0)] = evenBitOfUintTo8bitBrightness(posXMillimeter);
    OutPosition[uint2(row * 4 + 2, column * 6 + 1)] = evenBitOfUintTo8bitBrightness(posXMillimeter);
    OutPosition[uint2(row * 4 + 3, column * 6 + 0)] = evenBitOfUintTo8bitBrightness(posXMillimeter);
    OutPosition[uint2(row * 4 + 3, column * 6 + 1)] = evenBitOfUintTo8bitBrightness(posXMillimeter);

    //pos.y1
    //省略
    //pos.y2
    //省略
    //pos.z1
    //省略
    //pos.z2
    //省略    
}
