namespace Saccubus

open System

module Options =
    module Description =
        open System

        type Flag            = { title:string; description:Option<string>; argument:string; defaultValue:bool }
        type Directory       = { title:string; description:Option<string>; argument:string; defaultValue:System.IO.DirectoryInfo}
        type File            = { title:string; description:Option<string>; argument:string; defaultValue:System.IO.FileInfo}
        type FileInDirectory = { title:string; description:Option<string>; argument:string; dir:System.IO.DirectoryInfo; defaultFilename:string }
        type Value<'a>       = { title:string; description:Option<string>; argument:string; defaultValue:'a}
        type EnumValue       = { title:string; description:Option<string>; argument:string; options: (string*string) list; defaultValue:string }
        type EnumFlag        = { title:string; description:Option<string>; (* argument:string; *) options: (string*string) list; defaultValue:string }

        type ArgumentItem =
            | Flag of Flag
            | Directory of Directory
            | File of File
            | FileInDirectory of FileInDirectory
            | IntValue of Value<int>
            | StringValue of Value<string>
            | EnumValue of EnumValue
            | EnumFlag of EnumFlag


        type Argument =
            | Argv of (ArgumentItem)
            | FrontEnd of (ArgumentItem)

        type Section =
            | Node of Section list
            | Leaf of string*string*Argument list


        let downloadSection =
            Leaf("ダウンローダ", "ダウンロードする時の設定",
              [Argv(
                EnumValue(
                    {title = "ログイン方法";
                     description = Some("ニコニコ動画へのログイン方法を指定します");
                     argument="--resolve-cookie";
                     options=
                        [("ユーザーID+パスワード","own")
                        ;("Firefox","firefox")
                        ;("Chrome", "chrome")
                        ;("InternetExplorer", "ie")];
                     defaultValue = "own"}));
               Argv(
                StringValue(
                    {title = "ログインID";
                     description = Some("上でブラウザを選択した場合は入力しなくて大丈夫です。");
                     argument="--resolve-user";
                     defaultValue = "udon@example.com"}));
               Argv(
                StringValue(
                 {title = "パスワード";
                  description = Some("上でブラウザを選択した場合は入力しなくて大丈夫です。");
                  argument="--resolve-user";
                  defaultValue = "udon@example.com"}));
               Argv(
                Directory(
                    {title="保存先";
                     description=Some("動画ファイルの保存先");
                     argument="--resolve-resource-path";
                     defaultValue = new System.IO.DirectoryInfo("./__download__")}));])

        let convertSection:Section =
            Leaf("変換時設定","ffmpegで変換するときに使う設定です",
                [FrontEnd(
                  File(
                   {title="FFmpegパス";
                    description=Some("FFmpegの場所を指定します。");
                    argument="ffmpeg-path";
                    defaultValue=System.IO.FileInfo("ext/ffmpeg/bin/ffmpeg")
                    }))
                 FrontEnd(
                    File(
                      {title="FFmpegフィルタパス";
                       description=Some("FFmpegフィルタの場所を指定します。");
                       argument="ffmpeg-dynamic";
                       defaultValue = new System.IO.FileInfo("ext/Saccubus/Saccubus");}));
                 FrontEnd(
                    FileInDirectory(
                        {title="変換レシピ";
                         description=Some("変換に使うFFmpegオプションのレシピを指定します")
                         argument="recipe-path"
                         dir=new System.IO.DirectoryInfo("./recipe");
                         defaultFilename=("PC_default.py");}));
                  Argv(
                    EnumFlag(
                       {title="ログレベル";
                        description=Some("出力ログのログレベルを設定します")
                        options=[("トレース","--trace")
                                ;("詳細","--verbose")
                                ;("デバッグ","--debug")
                                ;("情報","--info")
                                ;("エラー","--error")];
                        defaultValue = "--info";}));]);

        let videoSection:Section =
         Leaf("動画設定","変換される動画についての設定",
           [FrontEnd(
                IntValue(
                    {title="同時変換数"
                     description=Some("同時に変換する数")
                     argument="num-conv"
                     defaultValue=2;}));
            FrontEnd(
                IntValue(
                    {title="横幅";
                     description=Some("この横幅に短辺を合わせて拡大されます。");
                     argument="width";
                     defaultValue=640;}));
            FrontEnd(
                IntValue(
                    {title="縦";
                     description=Some("この縦幅に短辺を合わせて拡大されます。");
                     argument="width";
                     defaultValue=480;}));
            FrontEnd(
                IntValue(
                    {title="最低FPS";
                     description=Some("このFPS以上になるように出力されます。\nコメントがかくかくする場合などにお試し下さい。");
                     argument="minfps";
                     defaultValue=25;}));
            Argv(
                Flag(
                   {title="TASモード";
                    description=Some("TASのように変換中に１フレームずつ操作できます。\nスペースキーで次のフレームです。");
                    argument="--enable-tas";
                    defaultValue=true}));
        ])

        let commentSection=
         Leaf("コメント", "コメントを描画するときの設定",
            [Argv(
                IntValue(
                   {title="コメント取得数";
                    description=Some("コメント取得件数を指定します。");
                    argument = "--resolve-comment-back";
                    defaultValue = 500;}));
             Argv(
                FileInDirectory(
                   {title="NGスクリプトファイル";
                    description=Some("変換しないコメントを決定するスクリプトを指定します。");
                    argument="--ng-script";
                    dir=new System.IO.DirectoryInfo("./ng-script");
                    defaultFilename=null }));
             Argv(
                EnumValue(
                   {title="コメント描画プラグイン";
                    description=Some("コメント描画プラグインを選択します");
                    argument = "--plugin-font";
                    options=[("シンプル", "simple")];
                    defaultValue="simple" }));
             Argv(
                EnumValue(
                   {title="コメント配置プラグイン";
                    description=Some("コメント描画プラグインを選択します");
                    argument = "--plugin-deploy";
                    options=[("シンプル", "simple")];
                    defaultValue="simple"})); ])

        let sections =
          Node(
            [downloadSection
            ;convertSection
            ;videoSection
            ;commentSection]);
    let wrapDialog(c:System.Windows.Forms.Control, title:string, description:Option<string>) =
        let fr = new System.Windows.Forms.FlowLayoutPanel()
        fr.BorderStyle <- System.Windows.Forms.BorderStyle.FixedSingle;
        fr.Margin <- new Windows.Forms.Padding(10)
        fr.Padding <- new Windows.Forms.Padding(10)
        //
        let titleLabel = new System.Windows.Forms.Label();
        titleLabel.Text <- title
        fr.Controls.Add( titleLabel )
        //
        match description with
          | Some(x) ->
            let descLabel = new System.Windows.Forms.Label();
            descLabel.Text <- x
            fr.Controls.Add( descLabel )
          | None -> ()
        //
        fr.Controls.Add(c)
        fr
    let itemToPanel (item:Description.ArgumentItem) =
        match item with
            | Description.ArgumentItem.Flag x -> true
            | Description.ArgumentItem.Directory x -> true
            | Description.ArgumentItem.File x -> true
            | Description.ArgumentItem.FileInDirectory x -> true
            | Description.ArgumentItem.IntValue x -> true
            | Description.ArgumentItem.StringValue x -> true
            | Description.ArgumentItem.EnumValue x -> true
            | Description.ArgumentItem.EnumFlag x -> true
    let rec createControlFromSection<'a> (f:Description.Argument -> System.Windows.Forms.Control ) (x:Description.Section) : System.Windows.Forms.Control =
        match x with
            | Description.Section.Node lst ->
                let tab = new System.Windows.Forms.TabControl()
                for it in lst do
                    let page = new System.Windows.Forms.TabPage();
                    page.Controls.Add (createControlFromSection f it)
                    tab.Controls.Add( page )
                tab :> System.Windows.Forms.Control
            | Description.Section.Leaf (title,desc,lst) ->
                let fr = new System.Windows.Forms.FlowLayoutPanel()
                for it in lst do
                    let c = f it
                    c.AutoSize <- true
                    fr.Controls.Add(c)
                fr :> System.Windows.Forms.Control
