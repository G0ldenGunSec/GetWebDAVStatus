using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Threading.Tasks;

namespace GetWebDAVStatus
{
    class Program
    {
        [DllImport("kernel32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        static extern bool WaitNamedPipeA(string lpNamedPipeName, uint nTimeOut);

        static void Main(string[] args)
        {
            int threadCount = 5;
            int targetIndex;
            List<string> targetHosts;

            if (args.Length == 0)
            {
                Console.WriteLine("[X] Error: Provide target host(s) on the command line. If providing multiple targets, include as a comma seperated list");
                return;
            }

            try
            {
                int tcIndex = Array.FindIndex(args, x => x.Equals("--tc", StringComparison.OrdinalIgnoreCase));
                if (tcIndex >= 0)
                {
                    threadCount = Int32.Parse(args[tcIndex + 1]);
                    tcIndex = tcIndex * 2;
                }
                targetIndex = ((args.Length - 1) * args.Length / 2) - tcIndex - 1;
                targetHosts = args[targetIndex].Split(',').ToList();
            }
            catch (Exception e)
            {
                Console.WriteLine("[X] Error parsing arguments, please check command line and try again");
                Console.WriteLine(e.Message);
                return;
            }

            Parallel.ForEach(targetHosts, new ParallelOptions { MaxDegreeOfParallelism = threadCount }, singleTarget =>
            {
                string pipename = @"\\" + singleTarget + @"\pipe\DAV RPC SERVICE";
                //timeout is a somewhat arbitrary value, as if named pipe does not exist the function returns immediately.
                bool davActive = WaitNamedPipeA(pipename, 3000);
                if (davActive)
                {
                    Console.WriteLine("[+] WebClient service is active on " + singleTarget);
                }
                else
                {
                    Console.WriteLine("[x] Unable to reach DAV pipe on {0}, system is either unreachable or does not have WebClient service running", singleTarget);
                }
            });
            return;
        }
    }
}
