namespace Saccubus

open System
open System.Drawing
open System.Windows.Forms

type public MainForm() as form =
    inherit Form()
    
    // TODO define your controls
    let t1 = new TabPage()
    let t2 = new TabPage()
    let formLabel = new Label()
    let formLabel2 = new Label()
    let panel = new System.Windows.Forms.TabControl()
    
    // TODO initialize your controls
    let initControls() = 
        t1.Controls.Add(formLabel)
        t1.Text<-"test1"
        t2.Text<-"test2"
        t2.Controls.Add(formLabel2)
        formLabel.Text <- "Main form data" 
        formLabel.DoubleClick.AddHandler(new EventHandler 
            (fun sender e -> form.eventLabel_DoubleClick(sender, e)))   
        formLabel2.Text <- "Main form data!!" 
        panel.Controls.Add(t1)
        panel.Controls.Add(t2)
        ()

    do
        form.SuspendLayout();
        initControls()

        // TODO add controls to the form
        form.Controls.Add(panel)

        // TODO define form properties
        form.ClientSize <- new Size(600, 600)
        form.Text <- "さきゅばす"

        // TODO define any required for events
        form.Load.AddHandler(new System.EventHandler 
            (fun sender e -> form.eventForm_Loading(sender, e)))

        // render the form
        form.ResumeLayout(false)
        form.PerformLayout()

    // TODO define your event handlers
    member form.eventForm_Loading(sender:obj, e:EventArgs) = 
        ()

    member form.eventLabel_DoubleClick(sender:obj, e:EventArgs) = 
        ()