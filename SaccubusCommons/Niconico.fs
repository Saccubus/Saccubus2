namespace SaccubusCommons
open SaccubusCommons.Functional;
open SaccubusCommons.Network;

module Niconico =
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
    type MetaInfo = {
        title : string
    }

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
                        return (fn (Left (new System.Net.WebException("動画が見つかりません") :> exn)))
                    else
                        let title = elm.GetElementsByTagName("title").ItemOf(0).InnerText
                        return (fn (Right {title = title}))
                } |> ignore
            else
                return (fn (Left (new System.Net.WebException("ネットワークエラーです：" + resp.StatusCode.ToString()) :> exn)))
        }

        