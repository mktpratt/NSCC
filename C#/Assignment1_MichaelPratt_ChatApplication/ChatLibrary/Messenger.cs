using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.Net.Sockets;

namespace ChatLibrary
{
    public class Messenger
    {
        // I have no idea why, but this IP and Port are the only ones that allow this to work for me
        // Port number found from https://msdn.microsoft.com/en-us/library/vstudio/ms178109(v=vs.100).aspx
        // IP Address found from http://stackoverflow.com/questions/23403912/c-sharp-web-localhostport-works-127-0-0-1port-doesnt-work
        private IPAddress ipAddress = IPAddress.Parse("127.0.0.1");
        private int portNum = 31544;
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
        /// connect method to be overloaded
        /// </summary>
        public virtual void connect()
        {

        }

        /// <summary>
        /// Method used to send message used by both client and server
        /// </summary>
        /// <param name="data">The message being sent</param>
        /// <returns>the message with "You: " in front of it</returns>
        public string sendMsg(string data)
        {

            byte[] msg = System.Text.Encoding.ASCII.GetBytes(data);
            // Print the message
            stream.Write(msg, 0, msg.Length);
            return ("You: " + data);

        }

        /// <summary>
        /// Used by the client and server to receive messages
        /// </summary>
        public string receiveMsg()
        {
            Byte[] bytes = new Byte[256];
            string data;
            int i;

            // Loop while there is still data to recieve 
            while ((i = stream.Read(bytes, 0, bytes.Length)) != 0)
            {
                // Translate data bytes to a ASCII string
                data = System.Text.Encoding.ASCII.GetString(bytes, 0, i);
                if (data == "quit")
                {
                    quit();
                }
                else
                {
                    return (data);
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
        /// <returns> The IP address </returns>
        public IPAddress getIpAddress()
        {
            return ipAddress;
        }

        /// <summary>
        /// Getter for port number
        /// </summary>
        /// <returns> The port number </returns>
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
        /// <returns> The NetworkStream </returns>
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
