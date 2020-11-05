using System;
using System.Collections.Generic;
using System.IO;
using System.Runtime.InteropServices;
using System.Threading.Tasks;
using UnityEngine;
using UnityEngine.UI;

public class TestDDS : MonoBehaviour
{
    [SerializeField] RawImage image;

    // Start is called before the first frame update
    async void Start()
    {

        await Task.Delay(1000);
        var testPath = Path.Combine(Application.streamingAssetsPath, "main_background.DDS");

        var texture = await NativeDDSLoader.LoadDDSAsync(testPath);

        image.texture = texture;

        //UnityEngine.Object.DestroyImmediate(texture);

        //FreeTexture(texture);
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
