[maxvertexcount(3)]
void geom(triangle appdata IN[3], inout TriangleStream<g2f> triStream)
{
    // このポリゴンを省くか？のフラグ
    bool isBug = false;

        // 今見ている三角ポリゴンの各辺の長さを取得します
    float sideLength0to1 = length(IN[0].vertex - IN[1].vertex);
    float sideLength1to2 = length(IN[1].vertex - IN[2].vertex);
    float sideLength2to0 = length(IN[2].vertex - IN[0].vertex);

    float rateThreshold = 5.0;
    // フィルター：辺の比がおかしかったら消す
    isBug =
        sideLength0to1 > sideLength1to2 * rateThreshold ||
        sideLength1to2 > sideLength2to0 * rateThreshold ||
        sideLength2to0 > sideLength0to1 * rateThreshold
        ? true : isBug;

    // フィルター：ある頂点間の距離がx[m]以上あったら
    float threshold = 0.4;
    isBug =
        sideLength0to1 > threshold ||
        sideLength1to2 > threshold ||
        sideLength2to0 > threshold
        ? true : isBug;

    // フィルター：頂点が範囲外なら
    for (int i = 0; i < 3; i++)
    {
        appdata v = IN[i];
        isBug = 
        v.vertex.x > 1.0 ||
        v.vertex.y > 2.0 ||
        v.vertex.z > 1.0 ||
        v.vertex.x < -1.0 ||
        v.vertex.y < -1.0 ||
        v.vertex.z < -1.0
        ? true : isBug;

    }

    [unroll]
    for (int i = 0; i < 3; i++)
    {
        // 頂点シェーダからもらった3頂点それぞれを射影変換して通常のレンダリングと同様にポリゴン位置を決める
        appdata v = IN[i];
            g2f o;
                // isBugフラグがあれば頂点位置を原点に飛ばす（discardでよさそう）
        o.vertex = isBug ? float4(0,0,0,0) : UnityObjectToClipPos(v.vertex);
        o.uv = v.uv;
        o.normal = UnityObjectToWorldNormal(normal);
        triStream.Append(o);
    }
}
