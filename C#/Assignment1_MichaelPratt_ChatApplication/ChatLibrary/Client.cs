using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace ChatLibrary
{
    public class Client : Messenger
    {

        public Client()
        {

        }

        /// <summary>
        /// Overloaded connect method used to connect the client to the server
        /// </summary>
        public override void connect()
        {
            try
            {

                String serverIP = getIpAddress().ToString();
                Int32 port = 13000;
                TcpClient client = new TcpClient(serverIP, port);

                setClient(client);
                setStream(client.GetStream());

            }

            catch (SocketException se)
            {
                throw se;
            }
            catch (Exception e)
            {
                throw e;
            }

        }

    }
}