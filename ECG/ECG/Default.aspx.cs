using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
//using Microsoft.Win32;
using System.IO;

namespace ECG
{
    public partial class _Default : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {/*
            using (RegistryKey v = Registry.LocalMachine.OpenSubKey("Software\\ECG", true))
            {
                try
                {
                    v.SetValue("DT", DateTime.Now.ToString("ddd, d MMM yyyy,  HH:mm:ss"));
                    v.SetValue("T", Request.QueryString["t"]);
                    v.SetValue("V", Request.QueryString["V"]);
                    L.Text = "Saved!";
                }
                catch
                {
                    L.Text = "Wrong parameter set!";
                }
            }*/
            try
            {
                //string A = DateTime.Now.ToString("ddd, d MMM yyyy,  HH:mm:ss");
                string B = Request.QueryString["t"];
                string C = Request.QueryString["V"];
                using (StreamWriter F = new StreamWriter("C:\\ASPNET\\ECG\\A.csv", true))
                {
                    F.WriteLine(B + ", " + C);
                }
                L.Text = "Saved!";
            }
            catch
            {
                L.Text = "Wrong parameter set!";
            }
        }
    }
}
