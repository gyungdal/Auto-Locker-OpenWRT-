using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace autoLocker
{
    class Server
    {
        private Socket socket;
        public Server()
        {
            socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            IPEndPoint ip = new IPEndPoint(IPAddress.Any, 8000);
            socket.Bind(ip);
            socket.Listen(1);
            while (true)
            {
                Socket client = socket.Accept();
                client.ReceiveTimeout = 1000;
                client.SendTimeout = 1000;
                byte[] receive = new byte[1024];
                while (client.Receive(receive, 1024, SocketFlags.None) > 0)
                {
                    //NONE
                }
                string str = System.Text.Encoding.UTF8.GetString(receive);
                if (str.IndexOf("UNLOCK") >= 0)
                {
                    Console.WriteLine("UNLOCK COMMAND CONFIRM!");
                    //LockManager.getInstance().open();
                    //잠금해제
                }
                else if (str.IndexOf("LOCK") >= 0)
                {
                    Console.WriteLine("LOCK COMMAND CONFIRM!");
                    // LockManager.getInstance().close();
                    //잠금
                }
                client.Close();
            }
        }
        
    }
}
