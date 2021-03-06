﻿using UnityEngine;
using uOSC;

public class OSCVolumeAndPitchVisualizer : MonoBehaviour
{
    /// 0~1のfloat値を0~255のモノクロ値でピクセルに書き込むコンピュートシェーダ
    public ComputeShader NormalizedRGBValueTo64pxRGBBrightness;
    /// 書き込むピクセル位置
    public int row, column;
    /// 書き込むテクスチャ
    [SerializeField]
    private RenderTexture output;
    /// OSCの受信サーバー
    [SerializeField] uOscServer server;
    /// 受け取るOSCアドレス
    [SerializeField] string address;
    /// volume: 0~1
    /// pitch: 0=A（ラ）で0~11の整数
    [SerializeField] float volume = 0, pitch = -2;
    /// hsv（色）値: 0=1
    [SerializeField] float h, s = 1.0f, v;

    void Start()
    {
        server.onDataReceived.AddListener(OnDataReceived);
    }

    void OnDataReceived(Message message)
    {
        if (message.address == (address + "/volume"))
        {
            float.TryParse(message.values[0].GetString(), out volume);
        }
        else if (message.address == (address + "/pitch"))
        {
            // 0 = A, 1 = A# で0~11まで　検出できなかった場合-1が返ってくる
            float.TryParse(message.values[0].GetString(), out pitch);
        }
    }

    private void Update()
    {
        var dt = Time.deltaTime;

        /// 音量をそのまま明度に
        v = volume;
        /// ピッチを色相に（実際にはカクカク変わらないようにLerpAngleで補完処理をかけました）
        h = pitch / 12.0f;

        /// HSVカラーをRGBに変換
        var rgb = Color.HSVToRGB(h, s, v * v);

        SetBlockRGB(row, column, rgb);
    }

    /// <summary>
    /// 指定したブロック（8px × 8px）を指定した色で塗る
    /// </summary>
    /// <param name="rowInMethod">ブロックの行</param>
    /// <param name="columnInMethod">ブロックの列</param>
    /// <param name="rgbInMethod">色</param>
    private void SetBlockRGB(int rowInMethod, int columnInMethod, Color rgbInMethod)
    {
        // 呼びたいカーネル（処理）を決める
        var kernel = NormalizedRGBValueTo64pxRGBBrightness.FindKernel("CSMain");

        // 必要なデータやら参照やらを渡す
        NormalizedRGBValueTo64pxRGBBrightness.SetInt("row", rowInMethod);
        NormalizedRGBValueTo64pxRGBBrightness.SetInt("column", columnInMethod);
        NormalizedRGBValueTo64pxRGBBrightness.SetFloat("normalizedRed", rgbInMethod.r);
        NormalizedRGBValueTo64pxRGBBrightness.SetFloat("normalizedGreen", rgbInMethod.g);
        NormalizedRGBValueTo64pxRGBBrightness.SetFloat("normalizedBlue", rgbInMethod.b);
        NormalizedRGBValueTo64pxRGBBrightness.SetTexture(kernel, "OutPosition", output);

        // コンピュートシェーダを実行する
        NormalizedRGBValueTo64pxRGBBrightness.Dispatch(kernel, 1, 1, 1);
    }
}
