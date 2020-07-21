float unpackUintFromDoubleFloat4(float4 oneSecond, float4 twoSecond){
    // 8bitの値 oneSecond = 0bxxxxxxxx と twoSecond = 0byyyyyyyy を合わせて 16bit goal = 0bxyxyxyxyxyxyxyxy にする
    uint4 oS = uint4(oneSecond * 255.0 + 0.5);
    uint4 tS = uint4(twoSecond * 255.0 + 0.5);

    uint firstGoal = (oS.x & 1) == 1 ? 2 : 0;
    firstGoal = (oS.x & 2) == 2 ? firstGoal | 8 : firstGoal;
    firstGoal = (oS.x & 4) == 4 ? firstGoal | 32 : firstGoal;
    firstGoal = (oS.x & 8) == 8 ? firstGoal | 128 : firstGoal;
    firstGoal = (oS.x & 16) == 16 ? firstGoal | 512 : firstGoal;
    firstGoal = (oS.x & 32) == 32 ? firstGoal | 2048 : firstGoal;
    firstGoal = (oS.x & 64) == 64 ? firstGoal | 8192 : firstGoal;
    firstGoal = (oS.x & 128) == 128 ? firstGoal | 32768 : firstGoal;

    uint secondGoal = (tS.x & 1) == 1 ? 1 : 0;
    secondGoal = (tS.x & 2) == 2 ? secondGoal | 4 : secondGoal;
    secondGoal = (tS.x & 4) == 4 ? secondGoal | 16 : secondGoal;
    secondGoal = (tS.x & 8) == 8 ? secondGoal | 64 : secondGoal;
    secondGoal = (tS.x & 16) == 16 ? secondGoal | 256 : secondGoal;
    secondGoal = (tS.x & 32) == 32 ? secondGoal | 1024 : secondGoal;
    secondGoal = (tS.x & 64) == 64 ? secondGoal | 4096 : secondGoal;
    secondGoal = (tS.x & 128) == 128 ? secondGoal | 16384 : secondGoal;

    uint goal = firstGoal | secondGoal;
    float value = goal;
    return value;
}
