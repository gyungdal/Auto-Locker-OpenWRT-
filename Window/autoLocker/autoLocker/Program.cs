using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
using System.Management;
using Microsoft.Win32;
using System.IO.Pipes;

namespace autoLocker
{
    class Program
    {
        private static bool isLock = false;
        [DllImport("user32")]
        public static extern void LockWorkStation();

        [DllImport("user32.dll")]
        static extern void keybd_event(byte bVk, byte bScan, uint dwFlags, UIntPtr dwExtraInfo);

        private const byte VK_SPACE = 0x20;
        private const byte VK_NUMPAD0 = 0x60;
        private const byte VK_NUMPAD1 = 0x61;
        private const byte VK_NUMPAD2 = 0x62;
        private const byte VK_NUMPAD3 = 0x63;
        private const byte VK_NUMPAD4 = 0x64;
        private const byte VK_NUMPAD5 = 0x65;
        private const byte VK_NUMPAD6 = 0x66;
        private const byte VK_NUMPAD7 = 0x67;
        private const byte VK_NUMPAD8 = 0x68;
        private const byte VK_NUMPAD9 = 0x69;
        private const byte VK_RETURN = 0x0D;

        private const int KEYEVENTF_EXTENDEDKEY = 0x0001; //Key down flag
        private const int KEYEVENTF_KEYUP = 0x0002; //Key up flag
        private const int VK_LCONTROL = 0xA2; //Left Control key code
        private const int VK_MENU = 0x12; //Alt key code
        private const int VK_UP = 0x26; //Up cursor key code
        static void Main(string[] args)
        {
            CheckLocking workLock = new CheckLocking();

            workLock.Run(new SessionSwitchEventHandler(SysEventsCheck));

            Console.WriteLine("Press ESC to exit...");
            while (true)
            {
                ConsoleKeyInfo key = Console.ReadKey(true);
                if (key.Key == ConsoleKey.Escape)
                    break;

            };
        }

        private static void keyBoardInput(byte[] pins)
        {
            System.Threading.Thread.Sleep(5000);
            keybd_event(VK_SPACE, 0, 0, new System.UIntPtr(0)); // KEY_DOWN
            System.Threading.Thread.Sleep(10);
            keybd_event(VK_SPACE, 0, KEYEVENTF_KEYUP, new System.UIntPtr(0)); // KEY_UP
            
            System.Threading.Thread.Sleep(1000);
            foreach (byte pin in pins)
            {
                Console.WriteLine(pin);
                System.Threading.Thread.Sleep(100);
                keybd_event(pin, 0, 0, new System.UIntPtr(0)); // KEY_DOWN
                System.Threading.Thread.Sleep(10);
                keybd_event(pin, 0, KEYEVENTF_KEYUP, new System.UIntPtr(0)); // KEY_UP
            }

            System.Threading.Thread.Sleep(10);
            keybd_event(VK_RETURN, 0, 0, new System.UIntPtr(0)); // KEY_DOWN
            System.Threading.Thread.Sleep(10);
            keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, new System.UIntPtr(0)); // KEY_UP
        }
        //C:\Program Files\Microsoft SDKs\Windows\v7.1\Samples
        public static void SysEventsCheck(object sender, SessionSwitchEventArgs e)
        {   
            switch (e.Reason)
            {
                case SessionSwitchReason.SessionLock:
                    {
                        isLock = true;
                        Console.WriteLine("Lock Encountered");  
                        byte[] pins = new byte[4];
                        pins[0] = VK_NUMPAD0;
                        pins[1] = VK_NUMPAD2;
                        pins[2] = VK_NUMPAD1;
                        pins[3] = VK_NUMPAD4;
                        keyBoardInput(pins);
                        break;
                    }
                case SessionSwitchReason.SessionUnlock:
                    isLock = false;
                    Console.WriteLine("UnLock Encountered");
                    break;
            }
        }
        
    }
}
