using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;
using System.IO;

namespace ApplicationActivatorTester
{
    /// <summary>
    /// App.xaml の相互作用ロジック
    /// </summary>
    public partial class App : Application
    {
        public string ProgramName { get; set; }
        private ApplicationActivator.ApplicationActivator Activator { get; set; }

        private void Application_Startup(object sender, StartupEventArgs e)
        {
            var fn = Path.GetFileName(Environment.GetCommandLineArgs()[0]);
            var an = Path.ChangeExtension(fn, null);
            an = Path.ChangeExtension(an, null);
            var avr = new ApplicationActivator.ApplicationActivator();
            this.Activator = avr;
            this.ProgramName = an;
            if (avr != null)
            {
                if (!avr.Activate())
                {
                    MainWindow mw = new MainWindow();
                    mw.Title = an;
                    mw.Show();
                }
                else
                {
                    avr.Dispose();
                    this.Shutdown();
                }
            }
        }

        private void Application_Exit(object sender, ExitEventArgs e)
        {
            var avr = this.Activator;
            if (avr != null)
            {
                avr.Dispose();
            }
        }
    }
}
