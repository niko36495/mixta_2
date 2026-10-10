using UnityEngine;
using System.IO.Ports;

public class ControlCarroUnity : MonoBehaviour
{
    [Header("Serial Setup")]
    public string comPort = "COM4";
    public int baudRate = 9600;

    [Header("Telemetry")]
    public float distance = 999f;

    private SerialPort port;

    void Start()
    {
        try
        {
            port = new SerialPort(comPort, baudRate);
            port.ReadTimeout = 20;
            port.WriteTimeout = 20;
            port.Open();
            Debug.Log("Connected to Arduino on " + comPort);
            SendCommand('X');
        }
        catch (System.Exception e)
        {
            Debug.LogError("Serial connection error: " + e.Message);
        }
    }

    void Update()
    {
        ReadArduino();

        // Control de teclado WASD
        char commandToSend = 'X'; 

        if (Input.GetKey(KeyCode.W))
        {
            commandToSend = 'F'; 
        }
        else if (Input.GetKey(KeyCode.S))
        {
            commandToSend = 'B'; 
        }
        else if (Input.GetKey(KeyCode.A))
        {
            commandToSend = 'L'; 
        }
        else if (Input.GetKey(KeyCode.D))
        {
            commandToSend = 'R'; 
        }

        SendCommand(commandToSend);
    }

    void ReadArduino()
    {
        if (port == null || !port.IsOpen) return;

        try
        {
            while (port.BytesToRead > 0)
            {
                string message = port.ReadLine().Trim();
                if (message.StartsWith("D:"))
                {
                    float dist;
                    if (float.TryParse(message.Substring(2), System.Globalization.NumberStyles.Float, System.Globalization.CultureInfo.InvariantCulture, out dist))
                    {
                        distance = dist;
                    }
                }
            }
        }
        catch { }
    }

    void SendCommand(char command)
    {
        if (port != null && port.IsOpen)
        {
            try
            {
                port.Write(command.ToString());
            }
            catch { }
        }
    }

    void OnApplicationQuit()
    {
        if (port != null && port.IsOpen)
        {
            try
            {
                port.Write("X");
                port.Close();
            }
            catch { }
        }
    }
}