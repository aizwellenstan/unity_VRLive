float texelSizeX = (1.0 / 1920.0);
    float texelSizeY = (1.0 / 1080.0);

    float4 color = float4(1,1,1,1);

    // value1 rowとcolumnで指定された8*8正方形の1ブロックを読む
    // 中心6*6を読んでとりあえず合計する
    for(uint x = 0; x < 6; x++){
        for(uint y = 0; y < 6; y++){
            float2 address = float2(
            // 8pxで1ブロックなのでrow*8, ブロック内の外周は捨てる方が精度が高いと思われる
                ( (_row) * 8 + 1 + x ) * texelSizeX,
                ( (_column) * 8 + 1 + y ) * texelSizeY );
            color += tex2Dlod(_valueTex, float4(address.x, address.y, 0, 0));
        }
    }

    // 合計を36で割って平均化する
    color = color / 36.0;
