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
        let cl = new System.Net.WebClient();
        try
            Right (cl.DownloadData(url))
        with
            | err -> Left err

    let getString (url:string) (enc:string) : Either<Exception, string> = 
        let enc = System.Text.Encoding.GetEncoding(enc)
        let cl = new System.Net.WebClient();
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
    let getAsyncBytes (url:string) (enc:string) (cont:Either<Exception, byte[]> -> 'a) =
        ThreadPool.QueueUserWorkItem (
            fun (state) ->
                let _ = cont (getBytes url)
                ()
                );
    let postBytes (url:string) (hash:Hashtable) = 
        null
