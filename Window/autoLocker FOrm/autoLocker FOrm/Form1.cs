using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace autoLocker_FOrm
{
    public partial class Form1 : Form
    {
        private static bool isLock = false;
        [DllImport("user32")]
        public static extern void LockWorkStation();

        [DllImport("user32.dll")]
        static extern void keybd_event(byte bVk, byte bScan, uint dwFlags, UIntPtr dwExtraInfo);
        public Form1()
        {
            InitializeComponent();
            CheckLocking workLock = new CheckLocking();

            workLock.Run(new SessionSwitchEventHandler(SysEventsCheck));
        }

        public static void SysEventsCheck(object sender, SessionSwitchEventArgs e)
        {
            switch (e.Reason)
            {
                case SessionSwitchReason.SessionLock:
                    {
                        isLock = true;
                        Console.WriteLine("Lock Encountered");
                        System.Threading.Thread.Sleep(1000);
                        SendKeys.Send("{LEFT}0214{ENTER}");
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
