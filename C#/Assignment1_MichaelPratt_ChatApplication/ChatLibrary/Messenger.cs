using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace ChatLibrary
{
    abstract public class Messenger
    {

        private IPAddress ipAddress = Dns.Resolve("localhost").AddressList[0];
        private int portNum = 13000;
        private TcpClient client = null;
        private NetworkStream stream;

        public Messenger()
        {

        }

        /// <summary>
        /// Checks if there is a message available
        /// </summary>
        public bool MessageAvailable
        {
            get
            {
                return stream.DataAvailable;
            }
        }
        /// <summary>
        /// Virtual connect method that is overloaded by the server and client
        /// </summary>
        public virtual void connect()
        {

        }

        /// <summary>
        /// Method used to send message used by both client and server
        /// </summary>
        /// <param name="data">The message being sent</param>
        /// <returns>the message with Sent:  in front of it</returns>
        public string sendMsg(string data)
        {

            byte[] msg = System.Text.Encoding.ASCII.GetBytes(data);
            // Send back a response.
            stream.Write(msg, 0, msg.Length);
            return ("Sent: " + data);

        }

        /// <summary>
        /// Used by the client and server to recieve messages
        /// </summary>
        /// <returns>Either quit to exit or the message with Received:  in front of it</returns>
        public string receiveMsg()
        {
            Byte[] bytes = new Byte[256];
            string data;
            int i;

            //Loop to receive all the data sent by the client. 
            while ((i = stream.Read(bytes, 0, bytes.Length)) != 0)
            {
                //Translate data bytes to a ASCII string.
                data = System.Text.Encoding.ASCII.GetString(bytes, 0, i);
                if (data == "quit")
                {
                    return data;
                }
                else
                {
                    return ("Received: " + data);
                }

            }
            return "";
        }

        /// <summary>
        /// Used to close the client and stream
        /// </summary>
        public virtual void quit()
        {
            stream.Close();
            client.Close();
        }

        /// <summary>
        /// Getter for IP address
        /// </summary>
        /// <returns>The IP address</returns>
        public IPAddress getIpAddress()
        {
            return ipAddress;
        }

        /// <summary>
        /// Getter for port number
        /// </summary>
        /// <returns>The port number</returns>
        public int getPortNum()
        {
            return portNum;
        }

        /// <summary>
        /// Setter for the TcpClient 
        /// </summary>
        /// <param name="client"></param>
        public void setClient(TcpClient client)
        {
            this.client = client;
        }

        /// <summary>
        /// Getter for NetworkStream
        /// </summary>
        /// <returns>The NetworkStream</returns>
        public NetworkStream getStream()
        {
            return stream;
        }

        /// <summary>
        /// Setter for NetworkStream
        /// </summary>
        /// <param name="stream"></param>
        public void setStream(NetworkStream stream)
        {
            this.stream = stream;
        }
    }
}