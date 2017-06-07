using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace autoLocker
{
    public class CheckLocking : IDisposable
    {
        private SessionSwitchEventHandler sseh;
        public void SysEventsCheck(object sender, SessionSwitchEventArgs e)
        {
            switch (e.Reason)
            {
                case SessionSwitchReason.SessionLock:
                    Console.WriteLine("Lock Encountered");
                    break;
                case SessionSwitchReason.SessionUnlock:
                    Console.WriteLine("UnLock Encountered");
                    break;
            }
        }

        public void Run()
        {
            sseh = new SessionSwitchEventHandler(SysEventsCheck);
            SystemEvents.SessionSwitch += sseh;
        }

        public void Run(SessionSwitchEventHandler handler)
        {
            SystemEvents.SessionSwitch += handler;
        }


        #region IDisposable Members

        public void Dispose()
        {
            SystemEvents.SessionSwitch -= sseh;
        }

        #endregion
    }
}
