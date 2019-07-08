  static void Main(string[] args)
        {
            StartTcpListener();
        }

        static void StartTcpListener()
        {
           string url =  ConfigurationSettings.AppSettings.Get("ListenUrl");
            if (string.IsNullOrEmpty(url))
            {
                return;
            }

            HttpListener listener = new HttpListener();
            listener.AuthenticationSchemes = AuthenticationSchemes.Anonymous;
            listener.Prefixes.Add(url);
            listener.Start(); 
            new Thread(new ThreadStart(delegate
            {
                while (true)
                {
                    HttpListenerContext httpListenerContext = listener.GetContext();
                    httpListenerContext.Response.StatusCode = 200;
                    using (StreamReader sr = new StreamReader(httpListenerContext.Request.InputStream))
                    {
                        string str = sr.ReadToEnd();
                        Console.WriteLine(str);
                    }
                    using (StreamWriter writer = new StreamWriter(httpListenerContext.Response.OutputStream))
                    {
                        writer.Write("success");
                    }
                    Thread.Sleep(100);
                }
            })).Start();
        }