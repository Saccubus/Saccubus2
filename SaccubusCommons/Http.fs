namespace SaccubusCommons.Network

open System
open System.IO;
open System.Net;
open System.Web;
open System.Text;
open System.Threading;
open System.Collections;
open SaccubusCommons.Functional;

module Http =
    let getBytes (url:string) : Either<Exception, byte[]> = 
        try
            let req:HttpWebRequest = HttpWebRequest.Create(url) :?> HttpWebRequest;
            req.Method <- "GET"
            let resp = req.GetResponse();
            let size = resp.ContentLength;
            let stream = resp.GetResponseStream();
            let data : byte array = Array.zeroCreate (int size);
            let mutable left = size
            while (left > (int64 0)) do
                let read = stream.Read(data, (int (size-left)), (int left));
                left <- left - (int64 read);
            Right ( data )
        with
            | err -> Left err

    let getString (url:string) (enc:string) : Either<Exception, string> = 
        let enc = System.Text.Encoding.GetEncoding(enc)
        let cl = new WebClient()
        let st = cl.OpenRead(url)
        let sr = new System.IO.StreamReader(st, enc)
        try
            try
                Right ( sr.ReadToEnd() )
            finally
                sr.Close()
                st.Close()
        with
            | err -> Left err

    let getAsyncString (url:string) (enc:string) (cont:Either<Exception, string> -> 'a) =
        ThreadPool.QueueUserWorkItem (
            fun (state) ->
                let _ = cont (getString url enc)
                ()
                );
    let getAsyncBytes (url:string) (cont:Either<Exception, byte[]> -> 'a) =
        ThreadPool.QueueUserWorkItem (
            fun (state) ->
                let _ = cont (getBytes url)
                ()
                );
    let postBytes (url:string) (hash:System.Collections.Specialized.NameValueCollection) =
        let wc = new WebClient();
        try
            try
                let data = wc.UploadValues(url, hash)
                Right data
            with
                | err -> Left err
        finally
            wc.Dispose()
    let postString (url:string) (enc_:string) (hash) =
        try
            let enc = System.Text.Encoding.GetEncoding(enc_)
            either {
                let! data = postBytes url hash;
                return enc.GetString(data)
            }
        with
            | err -> Left err
    let postAsyncString (url:string) (enc:string) (hash) (cont:Either<Exception, string> -> 'a) =
        ThreadPool.QueueUserWorkItem (
            fun (state) ->
                let _ = cont (postString url enc hash)
                ()
                );
    let postAsyncBytes (url:string) (enc:string) (hash) (cont:Either<Exception, byte[]> -> 'a) =
        ThreadPool.QueueUserWorkItem (
            fun (state) ->
                let _ = cont (postBytes url hash)
                ()
                );
