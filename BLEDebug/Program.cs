using System;
using System.IO;
using System.Windows.Forms;

namespace BLEDebug {
    static class Program {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main() {
            string EXEPathToLaunch = Environment.CurrentDirectory;
            if (!File.Exists("BLEDevice.dll")) {
                Console.WriteLine("DLL does not exist! Cannot launch!"); // You can replace this with a Message Box if the launcher is also Windows Forms.
                MessageBox.Show("BLEDevice.dll not found. Terminating...");
            } else {
                Application.EnableVisualStyles();
                if (Environment.OSVersion.Version.Major >= 6) SetProcessDPIAware();
                Application.SetCompatibleTextRenderingDefault(false);
                Application.Run(new BLEDebug());
            }        
        }
        [System.Runtime.InteropServices.DllImport("user32.dll")]
        private static extern bool SetProcessDPIAware();

    }
}
