using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.Net.Sockets;
using ChatLibrary;

namespace ChatUI
{
    class Program
    {

        /// <summary>
        /// Main method that connects the server or client then allows them to listen for a message or send one
        /// </summary>
        /// <param name="args"></param>
        static void Main(string[] args)
        {

            try
            {

                Messenger messenger = null;
                string msg;

                if (args.Length == 1)
                {
                    if (args[0] == "-server")
                    {
                        messenger = new Server();
                        Console.Write("Waiting for a connection... ");
                        messenger.connect();
                        Console.WriteLine("Connected!");
                    }

                }
                else
                {
                    messenger = new Client();
                    messenger.connect();

                }

                while (true)
                {
                    //checks if theres a message that was sent
                    if (messenger.MessageAvailable == true)
                    {
                        msg = messenger.receiveMsg();

                        if (msg == "quit")
                        {
                            messenger.quit();
                            System.Environment.Exit(0);
                        }
                        else
                        {
                            Console.WriteLine(msg);
                        }
                    }
                    else
                    {
                        if (Console.KeyAvailable)
                        {
                            ConsoleKeyInfo keyInfo = Console.ReadKey(true);

                            //checks if i was pressed and puts the console into input mode
                            if (keyInfo.Key == ConsoleKey.I)
                            {

                                Console.Write(">>");
                                string message = Console.ReadLine();
                                if (message == "quit")
                                {
                                    messenger.sendMsg(message);
                                    messenger.quit();
                                    System.Environment.Exit(0);
                                }
                                else
                                {
                                    msg = messenger.sendMsg(message);
                                    Console.WriteLine(msg);
                                }
                            }
                        }
                    }

                }
            }
            catch (ArgumentNullException ae)
            {
                Console.WriteLine("Argument exception " + ae);
                throw;
            }
            catch (SocketException se)
            {
                Console.WriteLine("Socket exception " + se);

            }
            catch (Exception e)
            {
                Console.WriteLine("Exception " + e);
                throw;
            }
        }

    }
}