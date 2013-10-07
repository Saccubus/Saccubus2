namespace Saccubus

open System
open System.Drawing
open System.Windows.Forms

type public MainForm() as form =
    inherit Form()
    let x = [("",""); ("",""); ("","")];

    // TODO define your controls
    let formLabel = new Label()
    
    // TODO initialize your controls
    let initControls() = 
        formLabel.Text <- "Main form data" 
        formLabel.DoubleClick.AddHandler(new EventHandler 
            (fun sender e -> form.eventLabel_DoubleClick(sender, e)))   

    do
        form.SuspendLayout();
        initControls()

        // TODO add controls to the form
        form.Controls.Add(formLabel)

        // TODO define form properties
        form.ClientSize <- new Size(600, 600)
        form.Text <- "Main Form"

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