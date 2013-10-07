namespace Saccubus

open System
open System.Drawing
open System.Windows.Forms

module Main =

    [<STAThread>]
    [<EntryPoint>]
    do
        Application.EnableVisualStyles()
        Application.SetCompatibleTextRenderingDefault(false)
        Application.Run(new MainForm() :> Form) 
