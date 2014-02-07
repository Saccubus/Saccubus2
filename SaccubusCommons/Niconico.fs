namespace SaccubusCommons
open SaccubusCommons.Functional;
open SaccubusCommons.Network;

module Niconico =
    (* 共通：ログイン *)
    let COOKIE_DOMAIN=".nicovideo.jp"
    let COOKIE_URI = new System.Uri("http://www.nicovideo.jp/")
    let COOKIE_NAME = "user_session"
    let LOGIN_URL="https://secure.nicovideo.jp/secure/login?site=niconico";
    type Login =
        | Own of (string * string)
        | Chrome
        | Firefox
        | InternetExplorer
    type LoginContext = {
        cookie : System.Net.CookieContainer
    };

    let internal loginOwn user pass fn =
        let nvc = dict [
                    "mail", user;
                    "password", pass];
        let chand = new System.Net.Http.HttpClientHandler();
        let cl = new System.Net.Http.HttpClient(chand);
        let content = new System.Net.Http.FormUrlEncodedContent(nvc)
        async {
            try
                let! resp = Async.AwaitTask (cl.PostAsync(LOGIN_URL,content))
                if not resp.IsSuccessStatusCode then
                    return (fn (Left(new System.Net.WebException("サーバが応答しません　ステータスコード："+resp.StatusCode.ToString()) :> exn)))
                let se = seq { for c in chand.CookieContainer.GetCookies(COOKIE_URI) -> c }
                if se |> Seq.exists (fun (x : System.Net.Cookie) -> x.Name = COOKIE_NAME) then
                    return fn (Right {cookie = chand.CookieContainer})
                else
                    return fn (Left (new System.Net.WebException("ログインに失敗しました") :> exn))
            with
                | err -> return (fn (Left err))
        }
    let internal loginChrome fn =
        async {
            fn (Left (new System.Net.WebException("ログインに失敗しました") :> exn))
        }
    let internal loginFirefox fn =
        async {
            fn (Left (new System.Net.WebException("ログインに失敗しました") :> exn))
        }
    let internal loginInternetExplorer fn =
        async {
            fn (Left (new System.Net.WebException("ログインに失敗しました") :> exn))
        }
    let login login_ fn =
        match login_ with
            | Own (user,pass) -> (loginOwn user pass fn)
            | Chrome -> loginChrome fn
            | Firefox -> loginFirefox fn
            | InternetExplorer -> loginInternetExplorer fn
    (* ニコニコ動画 *)
    module Video =
        type MetaInfo = {
            videoId : string;
            title : string
        }
        type PlayInfo = {
            videoId : string;
            threadId : string;
            videoUrl : string;
            userId : string;
            filter : seq<(string*string)>;
            messageServer : string;
            needsKey : bool
        }
        let fetchMetaInfo videoId (fn:Either<exn, MetaInfo> -> unit) =
            let META_INFO_API="http://ext.nicovideo.jp/api/getthumbinfo/";
            let chand = new System.Net.Http.HttpClientHandler();
            let cl = new System.Net.Http.HttpClient(chand);
            async {
                let! resp = Async.AwaitTask (cl.GetAsync(META_INFO_API+videoId))
                if resp.IsSuccessStatusCode then
                    let! dat = Async.AwaitTask (resp.Content.ReadAsStringAsync())
                    either {
                        let! elm = Xml.parse dat
                        if not (elm.Name = "nicovideo_thumb_response") || not (elm.GetAttribute("status") = "ok") then
                            let code = elm.GetElementsByTagName("code").ItemOf(0).InnerText
                            let description = elm.GetElementsByTagName("description").ItemOf(0).InnerText
                            return (fn (Left (new System.Net.WebException("APIエラー : "+code+" / "+description) :> exn)))
                        else
                            let title = elm.GetElementsByTagName("title").ItemOf(0).InnerText
                            return (fn (Right {
                                    videoId = videoId;
                                    title = title;
                                }))
                    } |> ignore
                else
                    return (fn (Left (new System.Net.WebException("ネットワークエラーです：" + resp.StatusCode.ToString()) :> exn)))
            }
        let fetchPlayInfo (loginContext:LoginContext) (videoId:string) (fn : Either<exn, PlayInfo> -> unit) =
            let PLAY_INFO_URL="http://flapi.nicovideo.jp/api/getflv/{0}?watch_harmful=1&as3=1";
            let url = System.String.Format(PLAY_INFO_URL, videoId);
            let chand = new System.Net.Http.HttpClientHandler();
            let cl = new System.Net.Http.HttpClient(chand);
            chand.CookieContainer <- loginContext.cookie
            async {
                let! resp = Async.AwaitTask (cl.GetAsync(url))
                if resp.IsSuccessStatusCode then
                    let! dat = Async.AwaitTask (resp.Content.ReadAsStringAsync())
                    let info = System.Web.HttpUtility.ParseQueryString(dat);
                    let filter = seq {
                        let ng_up = info.Get("ng_up");
                        let col = System.Web.HttpUtility.ParseQueryString(if ng_up = null then "" else ng_up);
                        for k in col.AllKeys -> (k, col.Get(k))
                    }
                    raise (new System.Exception(info.ToString()));
                    let playInfo = {
                        videoId = videoId;
                        threadId = info.Get("thread_id");
                        videoUrl = info.Get("url");
                        userId = info.Get("user_id");
                        filter = filter;
                        messageServer = info.Get("ms");
                        needsKey = info.Get("needs_key") = "1"
                    }
                    return (fn (Right playInfo))
                else
                    return (fn (Left (new System.Net.WebException("ネットワークエラーです：" + resp.StatusCode.ToString()) :> exn)))
            }
        type CommentOption = {
            comment_back : int
        };
        let fetchThreadKey (contex:LoginContext) (threadId:string) : Map<string, string> =
            let lst = new System.Collections.Generic.Dictionary<string, string>()
            Map.ofSeq (Seq.zip lst.Keys lst.Values)
        let constructThreadCommand
          (loginContext:LoginContext)
          (playInfo:PlayInfo)
          (commentOpt : CommentOption) =
            let doc = new System.Xml.XmlDocument()
            doc.AppendChild(doc.CreateXmlDeclaration( "1.0", "UTF-8", null )) |> ignore
            let packet = doc.CreateElement("packet")
            doc.AppendChild(packet) |> ignore
            (* デフォルトコメント *)
            let th = doc.CreateElement("thread")
            th.SetAttribute("thread", playInfo.threadId)
            th.SetAttribute("version", "20090904")
            th.SetAttribute("user_id", playInfo.userId)
            th.SetAttribute("scores", "1")
            packet.AppendChild(th) |> ignore
            let leave = doc.CreateElement("thread_leaves")
            leave.SetAttribute("thread", playInfo.threadId)
            leave.SetAttribute("user_id", playInfo.userId)
            leave.SetAttribute("scores", "1")
            let txt = System.String.Format("0-{0}:100,{1}", commentOpt.comment_back, (playInfo.length+59) / 60);
            leave.AppendChild(doc.CreateTextNode(txt)) |> ignore
            packet.AppendChild(leave) |> ignore
            (* 投稿者コメント *)
            let fth = doc.CreateElement("thread")
            fth.SetAttribute("thread", playInfo.threadId)
            fth.SetAttribute("version", "20061206")
            fth.SetAttribute("res_from", "-1000")
            fth.SetAttribute("fork", "1")
            fth.SetAttribute("user_id", playInfo.userId)
            fth.SetAttribute("scores", "1")
            fth.SetAttribute("click_revision", "-1")
            packet.AppendChild(fth) |> ignore
            (* スレッドキーが必要な場合は取得 *)
            if playInfo.needsKey then
                let dic = fetchThreadKey loginContext playInfo.threadId
                for (k,v) in Map.toSeq dic do
                    th.SetAttribute(k, v)
                    fth.SetAttribute(k, v)
                    leave.SetAttribute(k, v)
            doc
        let fetchComment
          (loginContext:LoginContext)
          (playInfo:PlayInfo)
          (commentOpt : CommentOption)
          (fn : Either<exn, System.Net.Http.HttpContent> -> unit) =
            ()

