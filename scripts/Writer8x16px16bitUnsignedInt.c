// csから渡される値
RWTexture2D<float4> OutPosition;
float val;
int row;
int column;

float4 oddBitOfUintTo8bitBrightness(uint posMillimeter){
    // 0bo-p-q-r-s-t-u-v- -> 0b00000000opqrstuv にする
    uint goal = 0;
    goal = (posMillimeter &     2) ==     2 ? 1 : goal;
    goal = (posMillimeter &     8) ==     8 ? goal | 2 : goal;
    goal = (posMillimeter &    32) ==    32 ? goal | 4 : goal;
    goal = (posMillimeter &   128) ==   128 ? goal | 8 : goal;
    goal = (posMillimeter &   512) ==   512 ? goal | 16 : goal;
    goal = (posMillimeter &  2048) ==  2048 ? goal | 32 : goal;
    goal = (posMillimeter &  8192) ==  8192 ? goal | 64 : goal;
    goal = (posMillimeter & 32768) == 32768 ? goal | 128 : goal;

    return  float4(
        goal & 0xff,
        goal & 0xff,
        goal & 0xff,
        0) / 255.0;
}

float4 evenBitOfUintTo8bitBrightness(uint posMillimeter){
    // 0b-o-p-q-r-s-t-u-v -> 0b00000000opqrstuv にする
    uint goal = 0;
    goal = (posMillimeter &     1) ==     1 ? 1 : goal;
    goal = (posMillimeter &     4) ==     4 ? goal | 2 : goal;
    goal = (posMillimeter &    16) ==    16 ? goal | 4 : goal;
    goal = (posMillimeter &    64) ==    64 ? goal | 8 : goal;
    goal = (posMillimeter &   256) ==   256 ? goal | 16 : goal;
    goal = (posMillimeter &  1024) ==  1024 ? goal | 32 : goal;
    goal = (posMillimeter &  4096) ==  4096 ? goal | 64 : goal;
    goal = (posMillimeter & 16384) == 16384 ? goal | 128 : goal;

    return  float4(
        goal & 0xff,
        goal & 0xff,
        goal & 0xff,
        0) / 255.0;
}

[numthreads(1,1,1)]
void CSMainFHD (uint3 id : SV_DispatchThreadID)
{
    uint uintValue = val * 65535.0f;

    for(uint x=0; x < 8; x++){
        for(uint y=0; y < 8; y++){
            OutPosition[uint2((row) * 8 + x, (column) * 8 + y)] =  oddBitOfUintTo8bitBrightness(uintValue);
            OutPosition[uint2((row + 1) * 8 + x, (column) * 8 + y)] = evenBitOfUintTo8bitBrightness(uintValue);
        }
    }
}
