using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace ChatLibrary
{
    public class Server : Messenger
    {

        TcpListener server;

        public Server()
        {

        }

        /// <summary>
        /// Overloaded connect method used to start the server and start listening for a client
        /// </summary>
        public override void connect()
        {

            server = null;
            try
            {
                server = new TcpListener(getIpAddress(), getPortNum());
                server.Start();
                TcpClient client = server.AcceptTcpClient();
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
            finally
            {
                // Stop listening for new clients.
                server.Stop();
            }

        }
    }
}