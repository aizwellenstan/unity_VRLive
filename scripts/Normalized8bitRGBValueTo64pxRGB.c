// csから渡される値
RWTexture2D<float4> OutPosition;
int row,column;
float normalizedRed, normalizedGreen, normalizedBlue;

[numthreads(1,1,1)]
void CSMain (uint3 id : SV_DispatchThreadID)
{   
    for(uint x=0; x < 8; x++){
        for(uint y=0; y < 8; y++){
            OutPosition[uint2((row) * 8 + x, (column) * 8 + y)] 
            = float4(normalizedRed, normalizedBlue, normalizedGreen, 1.0);
        }
    }
}
