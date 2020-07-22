float4 quatenionAxQuaternionB(float4 qa, float4 qb)
{
    return float4(
        qa.w * qb.x + qa.x * qb.w + qa.y * qb.z - qa.z * qb.y,
        qa.w * qb.y - qa.x * qb.z + qa.y * qb.w + qa.z * qb.x,
        qa.w * qb.z + qa.x * qb.y - qa.y * qb.x + qa.z * qb.w,
        qa.w * qb.w - qa.x * qb.x - qa.y * qb.y - qa.z * qb.z
    );
}

v2f vert (appdata v, uint vid : SV_VertexID)
{
        // -----------省略-------------

    float4 quaternion = float4(qx,qy,qz, qw);
    float4 conjugateQ = float4(-qx, -qy, -qz, qw); // 共役
    float4 vertAsQ = float4(v.vertex.x, v.vertex.y, v.vertex.z, 0);

    float4 rotatedPos = quatenionAxQuaternionB(quatenionAxQuaternionB(quaternion, vertAsQ), conjugateQ);

    v2f o;
    o.vertex = UnityObjectToClipPos(rotatedPos);
    o.uv = v.uv;
    return o;
}
